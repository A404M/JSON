#include <iostream>
#include "JSON/JSON.h"
#include "JSON/functions.h"

using namespace std;

int main() {
/*    JSONArray jsonArray{
R"([
    "this is an, \"string",
    false,
    null,
    true,
    2344.000000,
    -122.000000,
    [
        123,
        61887
    ]
])"};*/
    //cout << jsonArray.toString() << endl << jsonArray.getStringAt(0);

    JSONObject jsonObject{R"(
{
"string \"name":"string",
"array name":
[
    12345,
    "haflehf"
],
"object name":
{
"obj name string":"stringgggg",
"obj name number":12454
},
"number name":213
})"};

    cout << jsonObject.toString();
    return 0;
}
