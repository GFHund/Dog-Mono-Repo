#ifndef __WINDOW__
#define __WINDOW__

#include <windows.h>
#include <windowsx.h>

namespace DogGE{
    namespace Window{
        class DogWindow{
            private:
            HDC deviceContext;
            HWND mWindow;
            bool running;

            static LRESULT CALLBACK wndProc(HWND handle,UINT msg,WPARAM wParam,LPARAM lParam);//eventuell static
            LRESULT setEvents(UINT msg,WPARAM wParam,LPARAM lParam);
            const char* ClassName();
            public:
            void init();
            void run();
            void finish();
            bool isClosed();
            void error(DWORD dw,int aufrufe);
        };
    }
}

#endif