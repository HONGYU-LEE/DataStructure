#pragma once
#include"bitset.hpp"
#include<string>
namespace lee
{
	struct _BKDRHash
	{
		//BKDRHash
		size_t operator()(const std::string& key)
		{		
			size_t hash = 0;

			for (size_t i = 0; i < key.size(); i++)
			{
				hash *= 131;
				hash += key[i];
			}
			return hash;
		}
	};

	struct _SDBMHash
	{
		//SDBMHash
		size_t operator()(const std::string& key)
		{
			size_t hash = 0;

			for (size_t i = 0; i < key.size(); i++)
			{
				hash *= 65599;
				hash += key[i];
			}
			return hash;
		}
	};

	struct _RSHash
	{
		//RSHash
		size_t operator()(const std::string& key)
		{
			size_t hash = 0;
			size_t magic = 63689;

			for (size_t i = 0; i < key.size(); i++)
			{
				hash *= magic;
				hash += key[i];

				magic *= 378551;
			}
			return hash;
		}
	};

	template<class K = std::string, class Hash1 = _BKDRHash, class Hash2 = _SDBMHash, class Hash3 = _RSHash>
	class BloomFilter
	{
	public:
		BloomFilter(size_t num)
			: _bs(num)
			, _capacity(num)
			, _size(0)
		{}

		void set(const K& key)
		{
			//为了减少错误率，用多个哈希函数将同一个数据映射到多个位置
			size_t pos1 = Hash1()(key) % _capacity;
			size_t pos2 = Hash2()(key) % _capacity;
			size_t pos3 = Hash3()(key) % _capacity;

			_bs.set(pos1);
			_bs.set(pos2);
			_bs.set(pos3);

			++_size;
		}

		bool test(const K& key)
		{
			size_t pos1 = Hash1()(key) % _capacity;
			size_t pos2 = Hash2()(key) % _capacity;
			size_t pos3 = Hash3()(key) % _capacity;

			if (!_bs.test(pos1) || !_bs.test(pos2) || !_bs.test(pos3))
			{
				return false;
			}

			return true;
		}

		size_t size() const
		{
			return _size;
		}

	private:
		lee::bitset _bs;
		size_t _size;
		size_t _capacity;
	};
};