#pragma once
#include"RBTree.hpp"

namespace lee
{
	template<class K>
	class set
	{
	public:
		struct SetKeyOfValue
		{
			const K & operator()(const K & key)
			{
				return key;
			}
		};

		typedef typename RBTree<K, K, SetKeyOfValue>::iterator iterator;
		typedef typename RBTree<K, K, SetKeyOfValue>::const_iterator const_iterator;

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
			return _tree.Find(key);
		}

		std::pair<iterator, bool> insert(const K& key)
		{
			return _tree.Insert(key);
		}

	private:
		RBTree<K, K, SetKeyOfValue> _tree;
	
	};
};