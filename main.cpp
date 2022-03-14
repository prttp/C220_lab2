#include "UVec.h"
#include "MyQueue.h"
#include <string>
#include "MyUniquePTR.h"
#include <vector>
#include <list>
#include "myString.h"

int main()
{
	{UVector<int> v = { {1,1,2,2,3,3} };
	v.add({ 1,3,5 });
	printUVec(v);
	v.erase({ 2,5,4 });
	UVector<int> v2 = { {3,4,5,5,3,3} };
	v = v2;

	 }
	{
  		MyQueue<std::string>  q1{ std::string("AAA"), std::string("qwerty")};

		//использование MyQueue в диапазонном for:
		for (const auto& el : q1) { std::cout << el << ' '; }
		std::cout << std::endl;
		std::string s("abc");
		q1.push(s);
		q1.push(std::string("123"));
		std::string s1 = q1.pop();
		q1.push(std::string("qqq"));
		for (const auto& el : q1) { std::cout << el << ' '; }
		std::cout << std::endl;
		MyQueue < std::string >  q2 = q1;
		MyQueue < std::string >  q22 = std::move(q1);

		MyQueue < std::string >  q3{ 10, std::string("!")}; //очередь должна содержать 10 элементов со строкой «!» 
		q3.pop();
		q1 = q3;
		for (const auto& el : q1) { std::cout << el << ' '; }
		std::cout << std::endl;
		q2 = MyQueue < std::string >(5, std::string("?"));
		q1 = { std::string("bbb"), std::string("ssss")};
		for (const auto& el : q1) { std::cout << el << ' '; }
		std::cout << std::endl;
	}
	{
		MyUniquePTR<MyString> p1(new MyString("abc"));
		std::cout << p1->GetString();
		p1->SetNewString("qwerty");
		MyString s2 = *p1;
		//MyUniquePTR< MyString > p2=p1; //здесь компилятор должен выдавать ошибку => 
		
		if (p1) { std::cout << "No object!"; } //а это должно работать
		MyUniquePTR< MyString > p3(new MyString("vvv"));
		//p3 = p2; //и здесь компилятор должен выдавать ошибку
		std::vector< MyUniquePTR< MyString >> v; //как проинициализировать???
		v.push_back(std::move(p1));
		v.push_back(std::move(p3));
		std::list< MyUniquePTR< MyString >> l;
		//как скопировать из v в l ???
		for (int i = 0; i < v.size(); ++i)
			l.push_back(std::move(v[i]));

	}
	return 0;
}