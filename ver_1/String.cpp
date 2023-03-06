#include <cstring>
using std::strlen;

#include <algorithm>
using std::copy; 

#include <cstddef>
using std::size_t; 

#include <iostream>
using std::ostream; 
using std::istream;

#include <utility>
using std::swap;

#include <initializer_list>
using std::initializer_list;

#include <memory>
using std::uninitialized_copy;

#include "String.h"

std::allocator<char> String::a;

String & String::operator=(const String &rhs)
{
    auto newp = a.allocate(rhs.sz); // выделяем память 
	uninitialized_copy(rhs.p, rhs.p + rhs.sz, newp);

	if (p)
		a.deallocate(p, sz);  
	p = newp;    
	sz = rhs.sz; 

    return *this;     
}

//оператор move
String & String::operator=(String &&rhs) noexcept
{
	if (this != &rhs) {
		if (p)
			a.deallocate(p, sz);  
		p = rhs.p;    
		sz = rhs.sz;
		rhs.p = 0;    
		rhs.sz = 0;
	}
    return *this; 
}

String& String::operator=(const char *cp)
{
	if (p) a.deallocate(p, sz);
	p = a.allocate(sz = strlen(cp));
	uninitialized_copy(cp, cp + sz, p);
	return *this;
}

String& String::operator=(char c)
{
	if(p) a.deallocate(p, sz);
	p = a.allocate(sz = 1);
	*p = c;
	return *this;
}

String& String::operator=(initializer_list<char> il)
{
	// no need to check for self-assignment
	if (p)
		a.deallocate(p, sz);        // do the work of the destructor
	p = a.allocate(sz = il.size()); // do the work of the copy constructor
	uninitialized_copy(il.begin(), il.end(), p);
	return *this;
}
	
ostream &operator<<(ostream &os, const String &s) {
	
	for (auto c : s)
		os << c;
	return os;
}

String operator+(const String &lhs, const String &rhs) {

	String res; //новый объект
	res.sz = rhs.size() + lhs.size();   // общей размер строки 
	res.p = String::a.allocate(res.sz); // выделяем новое место в куче 
	uninitialized_copy(lhs.begin(), lhs.end(), res.p);  
	uninitialized_copy(rhs.begin(), rhs.end(), res.p + lhs.sz);
	return res;  // возвращаем новую строку 
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