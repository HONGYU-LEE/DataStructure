#include"HashBucket.hpp"
#include"iostream"
using namespace std;

//template<class K, class V>
//struct KeyofT
//{
//	const K& operator()(const pair<K, V> pv)
//	{
//		return pv.first;
//	}
//};



int main()
{
	lee::HashBucket<int, int> ht;
	ht.Insert(4);
	ht.Insert(14);
	ht.Insert(24);
	ht.Insert(5);
	ht.Insert(15);
	ht.Insert(25);
	ht.Insert(6);
	ht.Insert(16);
	ht.Insert(26);
	ht.Insert(36);
	ht.Insert(33);
	ht.Insert(44);

	auto it = ht.Insert(44);
	cout << *it.first << endl;

	//auto it = ht.Find(24);

	//cout << it->_data;
	//cout << endl;
	//for (auto i : ht)
	//{
	//	cout << i << endl;
	//}

	return 0;
}

struct _Hash<std::string>
{
	const size_t& operator()(const std::string& key)
	{
		//BKDR×Ö·û´®¹þÏ£º¯Êý
		size_t hash = 0;

		for (size_t i = 0; i < key.size(); i++)
		{
			hash *= 131;
			hash += key[i];
		}

		return hash;
	}
};