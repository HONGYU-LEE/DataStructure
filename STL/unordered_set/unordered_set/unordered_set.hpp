#include"HashBucket.hpp"

namespace lee
{
	template<class K, class Hash = lee::_Hash<K>>
	class unordered_set
	{
	public:
		struct SetKeyOfValue
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};

		typedef typename HashBucket<K, K, SetKeyOfValue, Hash>::iterator iterator;

		iterator begin()
		{
			return _hb.begin();
		}

		iterator end()
		{
			return _hb.end();
		}

		iterator find(const K& key)
		{
			return _hb.Find(key);
		}

		iterator erase(const K& key)
		{
			return _hb.Erase(key);
		}

		std::pair<iterator, bool> insert(const K& key)
		{
			return _hb.Insert(key);
		}

	private:
		HashBucket<K, K, SetKeyOfValue, Hash> _hb;
	};

};