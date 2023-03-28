#ifndef STRING_H
#define STRING_H

#include <string>
#include <memory>

using namespace std;
class String{
friend istream &operator>>(istream&, String&);
friend ostream &operator<<(ostream&, const String&);
friend String operator+=(const String&, const String&);
friend bool operator==(const String&, const String&);
friend bool operator!=(const String&, const String&);
friend bool operator<(const String&, const String&);
public:
    String():
        elements(nullptr), first_free(nullptr), cap(nullptr) {}
    String(const String&);
    String(const char*);
    String &operator=(const String&);
    ~String();
    void push_back(const char&);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    char *begin() const { return elements; }
    char *end() const { return first_free; }
private:
    allocator<char> alloc;
    void chk_n_alloc()
        { if(size() == capacity()) reallocate(); }
    pair<char*, char*> alloc_n_copy(const char*, const char*);
    void free();
    void reallocate();
    char *elements;
    char *first_free;
    char *cap;
};
#endif