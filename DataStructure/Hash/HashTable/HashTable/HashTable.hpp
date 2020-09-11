#pragma once
#include<vector>

namespace lee
{
	//算法科学家总结出的一个增容质数表，按照这样增容的效率更高
	const int PRIMECOUNT = 28;
	const size_t primeList[PRIMECOUNT] = 
	{
	 53ul, 97ul, 193ul, 389ul, 769ul,
	 1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
	 49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
	 1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
	 50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
	 1610612741ul, 3221225473ul, 4294967291ul
	};

	enum State
	{
		EMPTY,
		EXITS,
		DELETE,
	};


	template<class T>
	struct HashData
	{
		HashData(const T& data = T(), const State& state = EMPTY)
			: _data(data)
			, _state(state)
		{}

		T _data;
		State _state;
	};

	template<class K, class T, class KeyOfT>
	class HashTable
	{
	public:
		typedef HashData<T> HashData;

		HashTable(size_t capacity = 10)
			: _table(capacity)
			, _size(0)
		{}

		size_t getNextPrime(size_t num)
		{
			size_t i = 0;

			for (i = 0; i < PRIMECOUNT; i++)
			{
				//返回比那个数大的下一个质数 
				if (primeList[i] > num)
				{
					return primeList[i];
				}
			}

			//如果比所有都大，还是返回最后一个，因为最后一个已经是32位最大容量
			return primeList[PRIMECOUNT - 1];
		}

		//除留余数法
		size_t HashFunc(const K& key)
		{
			return key % _table.size();
		}

		bool Insert(const T& data)
		{
			KeyOfT koft;
			//判断此时是否需要增容
			//当装填因子大于0.7时增容
			if (_size * 10 / _table.size() >= 7)
			{
				//增容的大小按照别人算好的近似两倍的素数来增，这样效率更高，也可以直接2倍或者1.5倍。
				std::vector<HashData> newTable(getNextPrime(_size));

				for (size_t i = 0; i < _table.size(); i++)
				{
					//将旧表中的数据全部重新映射到新表中
					if (_table[i]._state == EXITS)
					{
						//如果产生冲突，则找到一个合适的位置
						size_t index = HashFunc(koft(_table[i]._data));

						while (newTable[i]._state == EXITS)
						{
							i++;

							if (i == _table.size())
							{
								i = 0;
							}
						}

						newTable[i] = _table[i];
					}
				}

				//最后直接将数据进行交换即可，原来的数据会随着函数栈帧一起销毁
				_table.swap(newTable);
			}
			
			//用哈希函数计算出映射的位置
			size_t index = HashFunc(koft(data));

			//从那个位置开始探测, 如果该位置已经存在时，有两种情况，一种是已经存在，一种是冲突，这里使用的是线性探测
			while (_table[index]._state == EXITS)
			{
				//如果已经存在了，则说明不用插入
				if (koft(_table[index]._data) == koft(data))
				{
					return false;
				}
				else
				{
					index++;
					index = HashFunc(index);
				}
			}

			//如果走到这里，说明这个位置是空的或者已经被删除的位置，可以在这里插入
			_table[index]._data = data;
			_table[index]._state = EXITS;
			_size++;

			return true;
		}

		HashData* Find(const K& key)
		{
			KeyOfT koft;
			size_t index = HashFunc(key);

			//遍历，如果查找的位置为空，则说明查找失败
			while (_table[index]._state != EMPTY)
			{
				//此时判断这个位置的数据是否相同，如果不同则说明出现哈希冲突，继续往后查找
				if (koft(_table[index]._data) == key)
				{
					//此时有两个状态，一种是数据已经被删除，一种是数据存在。
					if (_table[index]._state == EXITS)
					{
						return &_table[index];
					}
					else if (_table[index]._state == DELETE)
					{
						return nullptr;
					}
				}

				index++;

				//如果index越界，则归零
				if (index == _table.size())
				{
					index = 0;
				}
			}

			return nullptr;
		}

		bool Erase(const K& key)
		{
			HashData* del = Find(key);

			//如果找不到则说明已经被删除
			if (del == nullptr)
			{
				return false;
			}
			else
			{
				//找到了则直接更改状态即可
				del->_state = DELETE;
				_size--;
				return true;
			}
		}

	private:
		std::vector<HashData> _table;
		size_t _size;
	};
};