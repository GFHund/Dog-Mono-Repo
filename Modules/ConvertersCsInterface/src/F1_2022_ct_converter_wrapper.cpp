#include <F1_2022_ct_converter_wrapper.h>

DogGE::Converters::ConverterCTFormat* CreateF1_2022CtConverter()
{
    return new DogGE::Converters::ConverterCTFormat();
}

void DisposeClassName(DogGE::Converters::ConverterCTFormat* a_pObject)
{
    if(a_pObject!= NULL)
    {
        delete a_pObject;
        a_pObject= NULL;
    }
}

int canConvert(DogGE::Converters::ConverterCTFormat* a_pObject,const char* inputFile)
{
    if(a_pObject!= NULL)
    {
        bool bRet = a_pObject->canConvert(std::string(inputFile));
        return (bRet)?1:0;
    }
    return 0;
}
void convert(DogGE::Converters::ConverterCTFormat* a_pObject,const char* input,const char* output)
{
    if(a_pObject!= NULL)
    {
        a_pObject->convert(std::string(input),std::string(output));
    }
}