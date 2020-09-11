#pragma once
#include<vector>
#include<string>

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

	/*
	因为哈希函数的常用方法如直接定地、除留余数、平方取中等方法需要用的key值为整型，而大部分时候我们的key都是string，
	或者某些自定义类型，这个时候就可以提供一个仿函数的接口给外部，让他自己处理如何将key转换成我们需要的整型
	*/
	template<class K>
	struct _Hash
	{
		const K& operator()(const K& key)
		{
			return key;
		}
	};

	template<>
	struct _Hash<std::string>
	{
		const size_t & operator()(const std::string& key)
		{
			//BKDR字符串哈希函数
			size_t hash = 0;

			for (size_t i = 0; i < key.size(); i++)
			{
				hash *= 131;
				hash += key[i];
			}

			return hash;
		}
	};

	template<class K>
	struct SetKeyOfT
	{
		const K& operator()(const K& key)
		{
			return key;
		}
	};

	template<class T>
	struct HashNode
	{

		HashNode(const T& data = T())
			: _data(data)
			, _next(nullptr)
		{}

		T _data;
		HashNode<T>* _next;
	};

	template<class K, class T, class KeyofT, class Hash>
	class HashBucket;

	template<class K, class T, class KeyOfT, class Hash>
	struct __HashTableIterator
	{
		typedef HashNode<T> Node;
		typedef HashBucket<K, T, KeyOfT, Hash> HB;
		typedef __HashTableIterator<K, T, KeyOfT, Hash> Self;

		__HashTableIterator(Node* node, HB* hb) 
			: _node(node)
			, _phb(hb)
		{}

		T& operator*()
		{
			return _node->_data;
		}

		T* operator->()
		{
			return &_node->_data;
		}

		Self& operator++()
		{
			//如果下一个节点不为空，直接返回下一个
			if (_node->_next)
			{
				_node = _node->_next;
			}
			//如果下一个为空，则走到下一个表中
			else
			{
				//通过获取当前数据的key来判断下一个数据的位置
				KeyOfT koft;
				size_t pos = _phb->HashFunc(koft(_node->_data));
				++pos;

				for (; pos < _phb->_table.size(); pos++)
				{
					Node* cur = _phb->_table[pos];
					//如果下一个桶的数据不为空，则返回桶的第一个节点
					if (cur != nullptr)
					{
						_node = cur;
						return *this;
					}

				}
				//剩下的桶都没有数据
				_node = nullptr;
			}
			return *this;
		}

		Self operator++(int)
		{
			Self temp = *this;

			++this;

			return temp;
		}

		bool operator != (const Self& s)
		{
			return _node != s._node;
		}

		bool operator == (const Self& s)
		{
			return _node == s._node;
		}

		Node* _node;
		HB* _phb;
	};

	template<class K, class T, class KeyofT = SetKeyOfT<T>, class Hash = _Hash<K>>
	class HashBucket
	{
	public:
		typedef __HashTableIterator<K, T, KeyofT, Hash> iterator;
		typedef HashNode<T> Node;
		friend struct iterator;


		HashBucket(size_t capacity = 10)
			: _table(capacity)
			, _size(0)
		{}

		~HashBucket()
		{
			Clear();
		}

		iterator begin()
		{
			//找到第一个节点
			for (size_t i = 0; i < _table.size(); i++)
			{
				//如果节点不为空则返回
				if (_table[i])
				{
					return iterator(_table[i], this);
				}
			}

			return iterator(nullptr, this);
		}

		//因为在STL中哈希桶的底层是单链表的结构，所以不支持--操作，end就直接给一个空即可
		iterator end()
		{
			return iterator(nullptr, this);
		}

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

		size_t HashFunc(const K& key)
		{
			Hash hash;

			return hash(key) % _table.size();
		}

		std::pair<iterator, bool> Insert(const T& data)
		{
			KeyofT koft;

			/*
				因为哈希桶是开散列的链式结构，发生了哈希冲突是直接在对应位置位置进行头插，而桶的个数是固定的，而插入的数据会不断增多，
				随着数据的增多，就可能会导致某一个桶过重，使得效率过低。
				所以最理想的情况，就是每个桶都有一个数据。这种情况下，如果往任何一个地方插入，都会产生哈希冲突，所以当数据个数与桶的个数相同时，也就是负载因子为1时就需要进行扩容。
			*/
			if (_size == _table.size())
			{
				//按照素数表来增容
				size_t newSize = getNextPrime(_table.size());
				size_t oldSize = _table.size();

				std::vector<Node*> newTable(newSize);
				_table.resize(newSize);

				//接着将数据重新映射过去
				for (size_t i = 0; i < oldSize; i++)
				{
					Node* cur = _table[i];
					while (cur)
					{
						//重新计算映射的位置
						size_t pos = HashFunc(koft(cur->_data));

						//找到位置后头插进对应位置
						Node* next = cur->_next;

						cur->_next = newTable[pos];
						newTable[pos] = cur;

						cur = next;
					}
					//原数据置空
					_table[i] = nullptr;
				}
				//直接和新表交换，交换过去的旧表会和函数栈帧一块销毁。
				_table.swap(newTable);
			}

			size_t pos = HashFunc(koft(data));
			Node* cur = _table[pos];
			
			//因为哈希桶key值唯一，如果已经在桶中则返回false
			while (cur)
			{
				
				if (koft(cur->_data) == koft(data))
				{
					return std::make_pair(iterator(cur, this), false);
				}
				else
				{
					cur = cur->_next;
				}
			}

			//检查完成，此时开始插入，这里选择的是头插，这样就可以减少数据遍历的次数。
			Node* newNode = new Node(data);
			
			newNode->_next = _table[pos];
			_table[pos] = newNode;

			++_size;

			return std::make_pair(iterator(newNode, this), true);
		}

		iterator Erase(const K& key)
		{
			KeyofT koft;

			size_t pos = HashFunc(key);
			Node* cur = _table[pos];
			Node* prev = nullptr;

			while (cur)
			{
				if (koft(cur->_data) == key)
				{
					iterator ret(cur, this);
					++ret;

					//如果要删除的是第一个节点，就让下一个节点成为新的头节点，否则直接删除。
					if (prev == nullptr)
					{
						_table[pos] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}
					delete cur;
					--_size;

					return ret;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}
			}

			return end();
		}

		iterator Find(const K& key)
		{
			KeyofT koft;

			size_t pos = HashFunc(key);
			Node* cur = _table[pos];

			while (cur)
			{
				if (koft(cur->_data) == key)
				{
					return iterator(cur, this);
				}
				else
				{
					cur = cur->_next;
				}
			}

			return end();
		}

		void Clear()
		{
			//删除所有节点
			for (size_t i = 0; i < _table.size(); i++)
			{
				Node* cur = _table[i];

				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}

				_table[i] = nullptr;
			}
		}

	private:
		std::vector<Node*> _table;
		size_t _size;
	};
};
