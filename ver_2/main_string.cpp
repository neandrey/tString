#include <iostream>
#include <set>
#include "String.h"

using namespace std;

int main(int argc, char const *argv[])
{

    set<String> my_set;
    for(String temp; cin >> temp; ){
        my_set.insert(temp);
        temp="";
    }

    for(auto s : my_set){
        cout << s << " ";
    }
    cout << endl;
    
    return 0;
}
