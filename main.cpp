#include <iostream>
#include "json/json.hpp"
#include <fstream>
#include <chrono>

using namespace std;
using namespace json;

void doProcess(const string& fileName,double &avgParseTime);

int main(){
    double avgParseTime = 0;
    std::string fileName;
    cin >> fileName;
    cout << endl << endl;
    int times = 8;
    for(int i = 0;i < times;++i)
        doProcess(fileName,avgParseTime);
    cout << endl << endl << avgParseTime/times << "ms";
    return 0;
}

void doProcess(const string& fileName,double &avgParseTime){
    double total = 0;
    auto start = chrono::high_resolution_clock::now();
    ifstream jsonFile{fileName};

    string json,temp;

    while(getline(jsonFile,temp)){
        json += temp;
    }
    temp.clear();


    auto diff = chrono::high_resolution_clock::now() - start;
    total += chrono::duration<double, milli>(diff).count();
    cout << "Reading " << fileName << ":\t" << chrono::duration<double, milli>(diff).count() << "ms\n";
    start = chrono::high_resolution_clock::now();
    //JSONObject jsonObject{json};
    JSONArray jsonArray{json};
    diff = chrono::high_resolution_clock::now() - start;
    avgParseTime += chrono::duration<double, milli>(diff).count();
    total += chrono::duration<double, milli>(diff).count();
    cout << "Parsing:\t\t\t\t\t" << chrono::duration<double, milli>(diff).count() << "ms\n";
    cout << "Total:\t\t\t\t\t\t" << total << "ms\n\n\n";
}
