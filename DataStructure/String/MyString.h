#ifdef MyString_H
#define MyString_H

#include <iostream>
#include <cstring>
using namespace std;

class String{
public:
	String(char *s = NULL) {
		if (s != NULL) {
			string = new char(strlen(s) + 1);
			if (string) {
				string = strcpy(string, s);
			}
		}
	};
	
	size_t length();
	String operator+(String str);
	String operator+(char *str);
	String operator=(String str);
	char operator[](int index);
	bool isempty();
	friend ostream& operator <<(ostream &out,const String &str);
	char* insert(size_t index,const char* str);
	char* insert(size_t index,const String str);
	
private:
	char* string;
	
};

char String::operator[](int index) {
	return this -> string[index];
}

ostream& operator <<(ostream &out,String &str) {
	for (int i = 0; i < str.length(); i++) {
		out << str[i];
	}
	return out;
}

String String::operator=(String str) {
	String S(this -> string = str.string);
	return S;
}

bool String::isempty() {
	if (this -> string) {
		return false;
	} else {
		return true;
	}
}

size_t String::length() {
	return strlen(this -> string);
}

String String::operator+(String str) {
	String S(strcat(this -> string, str.string));
	return S;
}

String String::operator+(char *str) {
	String S(strcat(this -> string, str));
	return S;
}

char* String::insert(size_t index,const char *str) {
	char *s = new char(strlen(string) + 100);
	strncpy(s, this -> string, index);
	strcpy(s + index, str);
	strcpy(s + index + strlen(str),this -> string + index);
	return s;
}

char* String::insert(size_t index, String str) {
	char *s = new char(strlen(this -> string) + 100);
	strncpy(s, this -> string, index);
	strcpy(s + index, str.string);
	strcpy(s + index + strlen(str.string), this -> string + index);
	return s;
}

#endif