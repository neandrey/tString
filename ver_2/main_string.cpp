#include <iostream>
#include <set>
#include "String.h"
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    
//    set<String> s;

    // for (String temp; cin >> temp; )
    //     s.insert(temp);


    String s;
    cin >> s;
    cin >> s;

    
    for (auto c : s)
        cout << c << " ";
    cout << endl;
    

    return 0;
}
