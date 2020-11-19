#pragma once
#include"RBTree.hpp"

namespace lee
{
	template<class K, class V>
	class map
	{
	public:
		struct MapKeyOfValue
		{
			const K& operator()(const std::pair<K, V>& kv)
			{
				return kv.first;
			}
		};

		//模板要在调用时才会初始化，所以这里要加上typename表明为类型名
		typedef typename RBTree<K, std::pair<K, V>, MapKeyOfValue>::iterator iterator;
		typedef typename RBTree<K, std::pair<K, V>, MapKeyOfValue>::const_iterator const_iterator;

		iterator begin()
		{
			return _tree.begin();
		}

		iterator end()
		{
			return _tree.end();
		}

		iterator find(const K& key)
		{
			return _tree.Find(std::make_pair(key, V()));
		}

		std::pair<iterator, bool> insert(const std::pair<K, V>& kv)
		{
			return _tree.Insert(kv);
		}

		V& operator[](const K& key)
		{
			std::pair<iterator, bool> ret = _tree.Insert(std::make_pair(key, V()));

			return ret.first->second;
		}

	private:
		RBTree<K, std::pair<K, V>, MapKeyOfValue> _tree;
	};
};