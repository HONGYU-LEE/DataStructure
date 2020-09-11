#include"BloomFilter.hpp"
#include<iostream>
using namespace std;

int main()
{
	lee::BloomFilter<std::string> bf(100);
	bf.set("abcd");
	bf.set("aadd");
	bf.set("bcad");

	cout << bf.test("abcd") << endl;
	cout << bf.test("aadd") << endl;
	cout << bf.test("bcad") << endl;
	cout << bf.test("cbad") << endl;
	return 0;
}