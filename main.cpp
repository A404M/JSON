#include <iostream>
#include "json/json.hpp"
#include <fstream>
#include <chrono>

using namespace std;
using namespace json;

void doProcess(const string& fileName);

int main(){
    std::string fileName;
    cin >> fileName;
    cout << endl << endl;
    for(int i = 0;i < 5;++i)
        doProcess(fileName);
    return 0;
}

void doProcess(const string& fileName){
    long double total = 0;
    auto start = chrono::high_resolution_clock::now();
    ifstream jsonFile{fileName};

    string json,temp;

    while(getline(jsonFile,temp)){
        json += temp;
    }
    temp.clear();


    auto diff = chrono::high_resolution_clock::now() - start;
    total += chrono::duration<long double, milli>(diff).count();
    cout << "Reading " << fileName << ":\t" << chrono::duration<long double, milli>(diff).count() << "ms\n";
    start = chrono::high_resolution_clock::now();
    //JSONObject jsonObject{json};
    JSONArray jsonArray{json};
    diff = chrono::high_resolution_clock::now() - start;
    total += chrono::duration<long double, milli>(diff).count();
    cout << "Parsing:\t\t\t\t\t" << chrono::duration<long double, milli>(diff).count() << "ms\n";
    cout << "Total:\t\t\t\t\t\t" << total << "ms\n\n\n";
}
