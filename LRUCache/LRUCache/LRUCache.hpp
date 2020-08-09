#include<unordered_map>
#include<list>

using namespace std;

class LRUCache
{
public:
	LRUCache(size_t capacity)
		: _capacity(capacity)
	{}

	int get(int key) 
	{
		auto ret = _hashmap.find(key);

		//查找成功
		if (ret != _hashmap.end())
		{
			//获取数据的位置
			list<pair<int, int>>::iterator pos = ret->second;
			pair<int, int> kv = *pos;

			//将数据移动到队首
			_lrulist.erase(pos);
			_lrulist.push_front(kv);

			ret->second = _lrulist.begin();

			return kv.second;
		}
		//查找失败返回-1
		else
		{
			return -1;
		}
	}

	void put(int key, int value) 
	{
		//首先判断数据是否存在，来判定是插入还是更新
		auto ret = _hashmap.find(key);

		//如果数据存在，则是更新
		if (ret != _hashmap.end())
		{
			list<pair<int, int>>::iterator pos = ret->second;
			_lrulist.erase(pos);

			_lrulist.push_front(make_pair(key, value));
			ret->second = _lrulist.begin();
		}
		//不存在则是删除
		else
		{
			//数据已满
			if (_lrulist.size() == _capacity)
			{
				//删除最久未使用的数据
				pair<int, int> back = _lrulist.back();
				_lrulist.pop_back();
				_hashmap.erase(back.first);
			}
			//插入数据
			_lrulist.push_front(make_pair(key, value));
			_hashmap.insert(make_pair (key, _lrulist.begin()));
		}
	}

private:
	//利用哈希表来存储数据以及迭代器，来实现o(1)的get和put
	unordered_map<int, list<pair<int, int>>::iterator> _hashmap;
	//利用双向链表来保存缓存使用情况，并保证o(1)的插入删除
	list<pair<int, int>> _lrulist;
	size_t _capacity;
};