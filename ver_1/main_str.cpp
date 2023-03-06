#include <iostream>
#include <set>
#include "String.h"

using namespace std;

int main(int argc, char const *argv[])
{

    set<String> s;

    s.insert("hello");
    s.insert("good");
    s.insert("triangle");
    s.insert("one");
    s.insert("ant");

    for (auto c : s)
        cout << c << " ";
    cout << endl;
    
    return 0;
}
