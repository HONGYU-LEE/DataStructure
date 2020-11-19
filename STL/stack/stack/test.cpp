#include<iostream>
#include"stack.hpp"

using namespace std;

int main()
{
	lee::stack<int> s1;
	s1.push(1);
	s1.push(2);
	s1.push(3);
	s1.push(4);
	s1.push(5);
	cout << s1.size() << s1.empty() << endl;
	while (!s1.empty())
	{
		cout << s1.top();
		s1.pop();
	}
	cout << endl;

	cout << s1.size() << s1.empty() << endl;
	return 0;
}