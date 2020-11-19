#include<iostream>
#include"queue.hpp"

using namespace std;

int main()
{
	lee::queue<int> q1;
	q1.push(1);
	q1.push(2);
	q1.push(3);
	q1.push(4);
	q1.push(5);


	cout << "size : " << q1.size() << " empty : " << q1.empty() << endl;

	cout << q1.front() << q1.back();


	while (!q1.empty())
	{
		cout << q1.front() << ends;
		q1.pop();
	}
	cout << "size : " << q1.size() << "empty:" << q1.empty() << endl;
	return 0;
}