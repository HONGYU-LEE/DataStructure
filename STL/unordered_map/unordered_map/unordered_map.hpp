#include"HashBucket.hpp"

namespace lee
{
	template<class K, class V, class Hash = _Hash<K>>
	class unordered_map
	{
	public:
		struct MapKeyOfValue
		{
			const K& operator()(const std::pair<K, V>& kv)
			{
				return kv.first;
			}
		};
		
		typedef typename HashBucket<K, std::pair<K, V>, MapKeyOfValue, Hash>::iterator iterator;

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

		std::pair<iterator, bool> insert(const std::pair<K, V>& data)
		{
			return _hb.Insert(data);
		}

		V& operator[](const K& key)
		{
			std::pair<iterator, bool> ret = _hb.Insert(make_pair(key, V()));

			return ret.first->second;
		}

	private:
		HashBucket<K, std::pair<K, V>, MapKeyOfValue, Hash> _hb;
	};
};