#include"bitset.hpp"
#include<iostream>
using namespace std;

int main()
{
	lee::bitset bs(50);
	bs.set(45);
	bs.set(48);
	bs.set(9);
	bs.set(34);
	bs.reset(48);

	for (size_t i = 0; i < 50; ++i)
	{
		printf("[%d]:%d\n", i, bs.test(i));
	}

	//bitset bs(-1);
	////bitset bs(pow());
	////bitset bs(0xffffffff);
	return 0;
}

