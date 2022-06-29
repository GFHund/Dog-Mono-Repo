/**
 * @file ExceptionTemplate.cpp
 * @author Philipp Holzmann (Philipp1990@web.de)
 * @brief 
 * @version 1.0
 * @date 2022-05-14
 * 
 * @copyright Copyright (c) 2022
 * 
 * This file ist generated by the f1GameParserGenerator Program. Any changes will be overriden.
 * 
 */

#include <{{&EXCEPTION_HEADER}}>

namespace DogGE{
    namespace {{&NAMESPACE_NAME}}{
        {{&CLASS_NAME}}::{{&CLASS_NAME}}({{&CONSTRUCTOR_ARGS}}){
            {{&CONSTRUCTOR_FUNCTION}}
        }
        {{&GETTER_FUNCTION}}
        const char* {{&CLASS_NAME}}::what() const throw(){
            return {{&RETURN_STRING}};
        }
    }
}