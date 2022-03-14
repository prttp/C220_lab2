#pragma once
#include <algorithm>
#include <iostream>
class MyString
{
    char* m_pStr;	//строка-член класса
public:
	MyString(const char* text);
	MyString();
	~MyString();
	const char* GetString() const;
	MyString(const MyString& source);
	MyString( MyString&& source);
	void SetNewString(const char* text);
	friend MyString Unite(const char* text, ...);
	MyString& operator=(const MyString& other);
	MyString& operator=(const char* text);
	MyString& operator=(MyString&& other);
	friend std::ostream& operator<<(std::ostream& os, const MyString& text);
	MyString operator+(const MyString& other) const;
	MyString& operator+=(const MyString& other);
};
MyString Unite(const char* text, ...);
std::ostream& operator<<(std::ostream& os, const MyString& text);