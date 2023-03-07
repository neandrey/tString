#include "String.h"
#include <cstring>
#include <iostream>

void String::push_back(const char &s) {

    chk_n_alloc(); 
    alloc.construct(first_free++, s);
}

pair<char*, char*>
String::alloc_n_copy(const char *b, const char *e) {

    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)};
}

void String::free() {

    if (elements) {
        for (auto p = first_free; p != elements; )
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

String::String(const char *s){

    auto newdata = alloc_n_copy(s, s + strlen(s));
    elements = newdata.first;
    first_free = cap = newdata.second;
}

String::String(const String &s) {
    
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

String::~String() { free(); }

String &String::operator=(const String &rhs) {

    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void String::reallocate() {

    auto newcapacity = size() ? 2 * size() : 1;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;

    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

istream& operator>>(istream &is, String &s) {
    
    for (char c; (c = is.get()) != '\n'; ) {
        if(c == EOF)
            break;
        s.push_back(c);
    }
    return is;
}

ostream& operator<<(ostream &os, const String &s) {

	for (auto c : s)
		os << c;
	return os;
}

bool operator==(const String &lhs, const String &rhs) {

	return (lhs.size() == rhs.size() &&
			std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

bool operator!=(const String &lhs, const String &rhs) {

	return !(lhs == rhs);	
}

bool operator<(const String &lhs, const String &rhs) {

	return std::lexicographical_compare(lhs.begin(), lhs.end(), 
										rhs.begin(), rhs.end());
}