//
// Created by a404m on 2/5/21.
//

#ifndef JSON_FUNCTIONS_H
#define JSON_FUNCTIONS_H

#include <string>

void deleteSpaces(std::string& string){
    char kindStr = '\0';
    for(unsigned long long i = 0;i < string.size();i++){
        const char& current = string[i];

        if(isspace(current) && (kindStr == '\0')){//space and not in string
            string.erase(i,1);//erase the space
            i--;//go one back different size
        }else if(current == '\'' || current == '\"'){
            if(kindStr == current && string[i-1] != '\\'){//in string
                kindStr = '\0';//out of string
            }else{//not in string
                kindStr = current;//go in string
            }
        }
    }
}


#endif //JSON_FUNCTIONS_H
