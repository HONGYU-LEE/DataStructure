#include<iostream>
#include"vector.hpp"

using namespace lee;

int main()
{
	//int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	//vector<int> s1(std::begin(arr), std::end(arr));
	//vector<int> s2(10, 2);
	//vector<int> s3(s1);

	//std::cout << s3.capacity() << '-' << s3.size() << std::endl;
	//s3.push_back(90);
	//std::cout << s3.capacity() << '-' << s3.size() << std::endl;


	//vector<std::string> s4;
	//s4.push_back("1111");
	//s4.push_back("2222");
	//s4.push_back("3333");
	//s4.push_back("4444");
	//std::cout << s4.empty() << std::ends;
	//s4.clear();
	//std::cout << s4.empty() << std::ends;

	//std::cout << s4.size()<< std::endl;


	//for (auto i : s4)
	//{
	//	std::cout << i << std::ends;
	//}

	int arr[10];

	memset(arr, 1, sizeof(int) * 10);

	for (int i = 0; i < 10; i++)
		std::cout << arr[i] << std::endl;

}