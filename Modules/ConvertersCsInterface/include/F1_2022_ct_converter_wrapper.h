//https://docs.microsoft.com/de-de/cpp/dotnet/how-to-wrap-native-class-for-use-by-csharp?view=msvc-170
/*
#include <windows.h>
#include <vcclr.h>
#include <F1_2022_ct_converter.h>
#using <System.dll>

public ref class F1_2022_CT_Converter_Wrapper{
    public:
    F1_2022_CT_Converter_Wrapper(): m_Impl(new ConverterCTFormat()){}
    ~F1_2022_CT_Converter_Wrapper(){
        delete m_Impl;
    }
    protected:
    !F1_2022_CT_Converter_Wrapper(){
        delete m_Impl;
    }
    public:
    //property Str
    bool canConvert( String ^ inputFile ) {
      pin_ptr<const WCHAR> str = PtrToStringChars(theString);
      m_Impl->canConvert(str);
   }
   void convert( String ^ input, String ^ output ) {
      pin_ptr<const WCHAR> str = PtrToStringChars(theString);
      m_Impl->convert(str);
   }

    private:
    ConverterCTFormat* m_Impl;
}
*/

#include <F1_2022_ct_converter.h>

#ifdef __cplusplus
extern "C" {
#endif

extern __declspec(dllexport) DogGE::Converters::ConverterCTFormat* CreateF1_2022CtConverter();

extern __declspec(dllexport) void DisposeClassName(DogGE::Converters::ConverterCTFormat* a_pObject);

extern __declspec(dllexport) int canConvert(DogGE::Converters::ConverterCTFormat* a_pObject,const char* inputFile);
extern __declspec(dllexport) void convert(DogGE::Converters::ConverterCTFormat* a_pObject,const char* input,const char* output);



#ifdef __cplusplus
}
#endif
