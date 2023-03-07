#include <iostream>
#include <set>
#include "String.h"

using namespace std;

int main(int argc, char const *argv[])
{
    
    set<String> s;

    for (String temp; cin >> temp; )
        s.insert(temp);

    
    for (auto c : s)
        cout << c << " ";
    cout << endl;
    

    return 0;
}
