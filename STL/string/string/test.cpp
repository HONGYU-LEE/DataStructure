#include<iostream>
#include"string.hpp"

using namespace std;

int main()
{
	lee::string s1("hello");
	lee::string s2(move(s1));
}