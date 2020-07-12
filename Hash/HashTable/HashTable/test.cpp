#include<iostream>
#include"HashTable.hpp"

using namespace std;

template<class K>
struct SetKeyOfT
{
	const K& operator()(const K& key)
	{
		return key;
	}
};

int main()
{
	lee::HashTable<int, int, SetKeyOfT<int>> ht;
	ht.Insert(4);
	ht.Insert(14);
	ht.Insert(24);
	ht.Insert(5);
	ht.Insert(15);
	ht.Insert(25);
	ht.Insert(6);

	ht.Erase(15);
	ht.Erase(19);

	cout << endl;
	return 0;
}