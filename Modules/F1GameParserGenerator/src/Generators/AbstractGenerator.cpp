#include <Generators/AbstractGenerator.h>
#include <Exceptions/FileNotFoundException.h>
#include <fstream>

namespace DogGE{
    namespace F1GameParserGenerator{
        void AbstractGenerator::renderFile(std::string inputFile,std::string outputFile,kainjow::mustache::data data){
            std::string inputFileContent = this->readFile(inputFile);
            //std::cout << "input: " << inputFileContent << std::endl;
            kainjow::mustache::mustache mustacheObj(inputFileContent);
            std::string outputContent = mustacheObj.render(data);
            //std::cout << "output: "<< outputContent << std::endl;
            this->writeFile(outputFile,outputContent);
        }
        void AbstractGenerator::writeFile(std::string path,std::string content){
            std::cout << path << std::endl;
            std::ofstream ofs(path.c_str());
            ofs << content;
            ofs.close();
        }
        std::string AbstractGenerator::readFile(std::string path){
            std::cout << "read " << path << std::endl;
            std::ifstream ifs(path.c_str());
            if(!ifs.is_open()){
                throw FileNotFoundException(path);
            }
            ifs.seekg(0,ifs.end);
            int length = ifs.tellg();
            ifs.seekg(0,ifs.beg);
            char* buffer = new char[length+1];
            for(int i=0;i<length+1;i++){
                buffer[i] = ' ';
            }
            std::cout << "read " << length << " bytes"<<std::endl;
            ifs.read(buffer,length);
            ifs.close();
            buffer[length] = '\0';
            //std::cout << buffer << std::endl;
            //std::cout.write(buffer,length);
            std::string file = std::string(buffer,length);
            //std::cout << file << std::endl;
            delete[] buffer;
            return file;
        }
    }
}
