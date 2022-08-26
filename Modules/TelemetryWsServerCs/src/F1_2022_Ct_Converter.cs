using System;
using System.Runtime.InteropServices;

namespace TelemetryWsServerCs{
    class F1_2022_Ct_Converter{
        private IntPtr mObject;

        public F1_2022_Ct_Converter(){
            mObject = CreateF1_2022CtConverter();
        }
        public bool canConvert(string inputFile){
            return CallCanConvert(this.mObject,inputFile);
        } 
        public void convert(string input,string output){
            CallConvert(this.mObject,input,output);
        }

        [DllImport("ConvertersCsInterface.dll")]
        private static extern IntPtr CreateF1_2022CtConverter();

        [DllImport("ConvertersCsInterface.dll")]
        private static extern void DisposeClassName(IntPtr pClassNameObject);

        [DllImport("ConvertersCsInterface.dll")]
        private static extern bool CallCanConvert(IntPtr pClassNameObject,string inputFile);

        [DllImport("ConvertersCsInterface.dll")]
        private static extern void CallConvert(IntPtr pClassNameObject,string input,string output);

    }
}