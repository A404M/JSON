#include <iostream>
#include "json/json.hpp"
//#include "testing_lib/simdjson.h"
#include <fstream>
#include <chrono>
#include <queue>

using namespace std;
using namespace json;
//using namespace simdjson;

void doProcess(const string& fileName);

int c = 0;//extern

int main(){
    std::string fileName;
    cin >> fileName;
    cout << endl << endl;
    for(int i = 0;i < 10;++i)
        doProcess(fileName);
    
    cout << c;
    return 0;
}

void doProcess(const string& fileName){
    long double total = 0;
    auto start = chrono::high_resolution_clock::now();
    ifstream jsonFile{fileName};

    //getting file content
    //string json((istreambuf_iterator<char>(jsonFile)),(istreambuf_iterator<char>())); //slow
    string json,temp;

    while(getline(jsonFile,temp)){
        json += temp;
    }
    temp.clear();


    auto diff = chrono::high_resolution_clock::now() - start;
    total += chrono::duration<long double, milli>(diff).count();
    cout << "Reading " << fileName << ":\t" << chrono::duration<long double, milli>(diff).count() << "ms\n";
    start = chrono::high_resolution_clock::now();
    JSONObject jsonObject{json};
    //JSONArray jsonArray{json};
    diff = chrono::high_resolution_clock::now() - start;
    total += chrono::duration<long double, milli>(diff).count();
    cout << "Parsing:\t\t\t\t\t" << chrono::duration<long double, milli>(diff).count() << "ms\n";
    cout << "Total:\t\t\t\t\t\t" << total << "ms\n\n\n";
}
//5929
/*void doProcess(const string &fileName){
    auto start = chrono::high_resolution_clock::now();
    ondemand::parser parser;
    padded_string json = padded_string::load(fileName);
    ondemand::document tweets = parser.iterate(json);
    std::cout << uint64_t(tweets["k1"]["5929"]["num"]) << std::endl;
    //std::cout << uint64_t(tweets["search_metadata"]["count"]) << " results." << std::endl;

    auto diff = chrono::high_resolution_clock::now() - start;
    cout << "Parsing:\t\t\t\t" << chrono::duration<long double, milli>(diff).count() << "ms\n";
}*/
