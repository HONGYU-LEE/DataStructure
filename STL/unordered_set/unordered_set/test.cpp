#include"unordered_set.hpp"
#include<iostream>
using namespace std;


int main()
{
	lee::unordered_set<int> s;
	s.insert(1);
	s.insert(5);
	s.insert(4);
	s.insert(2);
	s.erase(4);
	lee::unordered_set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}

	cout << endl;
}
