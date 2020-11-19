#include<iostream>
#include"list.hpp"


using namespace lee;
int main()
{
	//list<int> l1;
	//l1.push_back(1);
	//l1.push_back(2);
	//l1.push_back(3);
	//l1.push_back(4);
	//l1.push_back(5);
	//l1.push_front(0);
	//list<int> l2 = l1;
	int a = 3;
	int b = 4;
	list<int*> l3;
	l3.push_back(&a);
	l3.push_back(&b);


	//std::cout << l1.size() << std::endl;


	//l1.push_back(111);

	//l2 = l1;

	//for (auto it : l1)
	//{
	//	std::cout << it << std::ends;
	//}

	//std::cout << std::endl;

	//for (auto it : l2)
	//{
	//	std::cout << it << std::ends;
	//}
	return 0;
}