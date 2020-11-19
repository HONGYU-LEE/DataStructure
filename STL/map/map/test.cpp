#include<iostream>
#include"map.hpp"
#include<string>
using namespace std;

template<class K, class V>
struct MapKeyOfValue
{
	const K& operator()(const std::pair<K, V>& kv)
	{
		return kv.first;
	}
};
int main()
{
	lee::map<int, string> map;

	map.insert(make_pair(3, "hello"));
	map.insert(make_pair(4, "word"));
	map.insert(make_pair(9, "sky"));
	map.insert(make_pair(5, "walk"));
	map.insert(make_pair(1, "olive"));
	map.insert(make_pair(546, "barry"));
	string strs[] = { "西瓜", "樱桃", "西瓜", "苹果", "西瓜", "西瓜", "西瓜", "苹果" };
	lee::map<string, int> countMap;
	for (auto& str : strs)
	{
		// 1、如果水果不在map中，则operator[]会插入pair<str, 0>, 返回映射对象(次数)的引用进行了++。
		// 2、如果水边在map中，则operator[]返回水果对应的映射对象(次数)的引用，对它++。
		countMap[str]++;
	}

	for (auto kv : countMap)
	{
		cout << kv.first << ":" << kv.second << endl;
	}


}