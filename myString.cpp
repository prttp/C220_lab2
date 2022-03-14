#include <string>
#include "myString.h"

using namespace std;

// Определение конструктора.
MyString::MyString(const char* text) {
	

		m_pStr = new char[strlen(text) + 1];
		strcpy(m_pStr, text);
	
}
MyString::MyString() {


	m_pStr = nullptr;
	

}

// Определение деструктора.
MyString::~MyString() {
	delete[] m_pStr;
}
const char* MyString::GetString() const {
	if (m_pStr == nullptr) { return "Error"; }
		return m_pStr;
}
MyString::MyString(const MyString& source) {
	if (source.m_pStr == nullptr) { m_pStr = nullptr; }
	else {
		m_pStr = new char[strlen(source.m_pStr) + 1];
		strcpy(m_pStr, source.m_pStr);
	};
}
MyString::MyString(MyString&& source)
{
	m_pStr = source.m_pStr;
	source.m_pStr = nullptr;
}
void MyString::SetNewString(const char* text) {
	delete[] m_pStr;
	m_pStr = new char[strlen(text) + 1];
	strcpy(m_pStr, text);
}
MyString Unite(const char* text, ...) {
	int count = 0;
	const char** p1 = &text;
	
	do {
		count += (strlen(*p1));
		++p1;
		
	} while (strcmp(*p1, "end") != 0);
	char* ans = new char[count+1];
	p1 = &text;
	ans[0] = 0;
	
	do {
		strcpy(&ans[strlen(ans)], *p1);
		++p1;
	} while (strcmp(*p1, "end") != 0);
	
	/*char* ans = new char[strlen(text) + 1];
	strcpy(ans, text);
	const char** p = &text;
	do {
		text= *(++p);
		if (strcmp(text, "end") == 0) { break; };
		char* tmp = new char[strlen(ans) + 1];
		strcpy(tmp, ans);
		delete[] ans;
		ans = new char[strlen(tmp) + strlen(text) + 1];
		strcpy(ans, tmp);
		int j = 0;
		do {
			
			ans[strlen(tmp) + j] = text[j];
			j++;
		} while (text[j-1] != '\0');
		
		delete[] tmp;
		tmp = nullptr;
		
	} while (1);*/
	MyString Answer(ans);
	delete[] ans;
	
	return Answer;
}
MyString& MyString::operator=(const MyString& other) {
	if (other.m_pStr == nullptr) { m_pStr = nullptr; }
	if (m_pStr != other.m_pStr) {
		delete[] m_pStr;
		m_pStr = new char[strlen(other.m_pStr) + 1];
		strcpy(m_pStr, other.m_pStr);
	}
	return *this;
};
MyString& MyString::operator=(const char* text) {
	if (m_pStr != nullptr) { delete[] m_pStr; }
	m_pStr = new char[strlen(text) + 1];
	strcpy(m_pStr, text);
	return *this;
};
MyString& MyString::operator=(MyString&& other) {
	m_pStr = other.m_pStr;
	other.m_pStr = nullptr;
	return *this;
	  };
std::ostream& operator<<(std::ostream& os, const MyString& text) {
	//os << "contains: " << '"' << text.m_pStr << '"';
	os << text.m_pStr;
	return os;
}
MyString MyString::operator+(const MyString& other) const {
	if (other.m_pStr == nullptr) { return *this; }
	return Unite(m_pStr, other.m_pStr, "end");
}
MyString& MyString::operator+=(const MyString& other) {
	//MyString temp = Unite(m_pStr, other.m_pStr, "end");
	//*this = std::move(temp);
	*this = Unite(m_pStr, other.m_pStr, "end");
	
	return *this;
}