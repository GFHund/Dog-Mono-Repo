#include <DogWindow.h>
#include <stdio.h>
#include <Logger.h>
#include <Exceptions/WindowCreateException.h>


namespace DogGE{
	namespace Window{
		void DogWindow::init(){
			HMODULE inst;
			HWND window;
			
			DWORD winStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
			bool fullscreen = false;
			int width = 1024;
			int height = 768;
			inst = GetModuleHandle(NULL);
			if(inst == NULL){
				DWORD code = GetLastError();
				Logger::Logger::getInstance()->log(Logger::Logger::LOGGER_ERROR,"Fehler GetModuleHandle");
				error(code,0);
				return;
			}
			
			const wchar_t className[] = L"Test dies ist ein Test";
			
			WNDCLASS wndclass = {0};
			wndclass.lpfnWndProc = DogWindow::wndProc;
			wndclass.hInstance = inst;
			wndclass.lpszClassName = ClassName();
			if(!RegisterClass(&wndclass))
			{
				DWORD code = GetLastError();
				Logger::Logger::getInstance()->log(Logger::Logger::LOGGER_ERROR,"Fehler Registerclass");
				error(code,0);
			}
			
			if(!fullscreen)
			{
				RECT rect = {0,0,width,height};
				AdjustWindowRect(&rect,winStyle,false);
			}
			mWindow = CreateWindowEx(0 ,ClassName(),"bla bla",winStyle,0,0,width,height,0,0,inst,this);
			if(mWindow == NULL)
			{
				DWORD code = GetLastError();
				Logger::Logger::getInstance()->log(Logger::Logger::LOGGER_ERROR,"Fehler CreateWindow");
				error(code,0);
			}
			deviceContext = GetDC(mWindow);
			if(deviceContext==NULL)
			{
				DWORD code = GetLastError();
				Logger::Logger::getInstance()->log(Logger::Logger::LOGGER_ERROR,"Fehler GetDC");
				error(code,0);
			}

			//finde den besten Pixelformat
			PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),	//gr��e des Feldes
			1,								//Versions nummer
			PFD_DRAW_TO_WINDOW|				//support window
			PFD_SUPPORT_OPENGL|				//support opengl
			PFD_DOUBLEBUFFER,				//double buffered
			PFD_TYPE_RGBA,					//RGBA type
			24,								//24-bit color depth
			0,0,0,0,0,0,					//color bits ignored
			0,								//kein alpha buffer
			0,								//shift bit ignorieren
			0,								//no accumulation buffer
			0,0,0,0,						//accum bits ignored
			32,								//32-bit z-buffer
			0,								//no stencil buffer
			0,								//no auxiliary buffer
			PFD_MAIN_PLANE,					//main layer
			0,								//reserved
			0,0,0							//layer masks ignored
			};

			int iPixelFormat;
			iPixelFormat = ChoosePixelFormat(deviceContext,&pfd);
			if(iPixelFormat == 0)
			{
				DWORD code = GetLastError();
				Logger::Logger::getInstance()->log(Logger::Logger::LOGGER_ERROR,"Fehler ChoosePixelFormat");
				error(code,0);
			}
			if(!SetPixelFormat(deviceContext,iPixelFormat,&pfd))
			{
				DWORD code = GetLastError();
				Logger::Logger::getInstance()->log(Logger::Logger::LOGGER_ERROR,"Fehler setPixelFormat");
				error(code,0);
			}

			HGLRC glContext = wglCreateContext(deviceContext);
			if(glContext==NULL)
			{
				Logger::Logger::getInstance()->log(Logger::Logger::LOGGER_ERROR,"Fehler wglCreateContext");
				return;
			}

			HGLRC currentContext = wglGetCurrentContext();
			if(currentContext)
				wglShareLists(currentContext,glContext);

			if(deviceContext && glContext && (wglGetCurrentContext()!=glContext)){
				wglMakeCurrent(deviceContext,glContext);
			}
			this->running = true;
		}
		const char* DogWindow::ClassName(){
			return "SampleWindowClass";
		}
		void DogWindow::run(){
			MSG msg = {};
			SwapBuffers(deviceContext);
			GetMessage(&msg,NULL,0,0);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			
		}
		void DogWindow::finish(){

		}
		bool DogWindow::isClosed(){
			return !this->running;
		}
		void DogWindow::error(DWORD dw,int aufrufe)
		{
			const DWORD size=100+1;
			TCHAR buffer[size];
			DWORD code = FormatMessage(//FORMAT_MESSAGE_ALLOCATE_BUFFER |
						FORMAT_MESSAGE_FROM_SYSTEM|
						FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL,
						dw,
						MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
						buffer,
						size,NULL);
			if(code == 0 && aufrufe < 2)
			{
				DWORD dw1 = GetLastError();
				error(dw1,aufrufe++);
			}
			else
			{
				throw WindowCreateException(std::string(buffer));
			}
		}

		LRESULT CALLBACK DogWindow::wndProc(HWND handle,UINT msg,WPARAM wParam,LPARAM lParam)
		{
			DogWindow* pThis = NULL;
			if(msg == WM_NCCREATE)
			{
				CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
				pThis = (DogWindow*)pCreate->lpCreateParams;
				SetWindowLongPtr(handle,GWLP_USERDATA,(LONG_PTR)pThis);
				pThis->mWindow = handle;
			} else {
				pThis = (DogWindow*)GetWindowLongPtr(handle,GWLP_USERDATA);
			}

			if(pThis){
				return pThis->setEvents(msg,wParam,lParam);
			} else {
				return DefWindowProc(handle,msg,wParam,lParam);
			}
			
		}
		LRESULT DogWindow::setEvents(UINT msg,WPARAM wParam,LPARAM lParam)
		{
			switch(msg)
			{
				case WM_CLOSE:
				{
					//printf("close Window");
					this->running = false;
					return 0;
				}
				case WM_DESTROY:
				{
					this->running = false;
					PostQuitMessage(0);
					return 0;
				}
				case WM_PAINT:
				{
					PAINTSTRUCT ps;
					HDC hdc = BeginPaint(mWindow,&ps);
					FillRect(hdc,&ps.rcPaint,(HBRUSH)(COLOR_WINDOW+1));
					EndPaint(mWindow,&ps);
					return 0;
				}
				default:
					return DefWindowProc(mWindow,msg,wParam,lParam);
			}
			return TRUE;
		}
	}
}