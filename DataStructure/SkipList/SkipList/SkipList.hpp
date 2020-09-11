#pragma once

#include<cstdlib>     
#include<ctime>       
#include<iostream>
#include<limits>
#include<random>

namespace lee
{
	template<class T>
	struct less
	{
		bool operator()(const T& x, const T& y)
		{
			return x < y;
		}
	};

	template<class T>
	struct greater
	{
		bool operator()(const T& x, const T& y)
		{
			return x > y;
		}
	};

	//跳表节点
	template<class T>
	struct SkipListNode
	{
		SkipListNode(T data = INT_MAX)
			: _data(data)
			, _up(nullptr)
			, _down(nullptr)
			, _left(nullptr)
			, _right(nullptr)
		{}

		T _data;
		SkipListNode<T>* _up;
		SkipListNode<T>* _down;
		SkipListNode<T>* _left;
		SkipListNode<T>* _right;
	};

	template<class T ,class Compare = less<T>>
	class SkipList
	{
		typedef SkipListNode<T> Node;
	private: 
		Node* _head;	//头节点
		Node* _tail;	//尾节点
		double _promoteRate;	//晋升概率
		int _maxLevel;	//最高层数

	public:
		SkipList()
			: _head(new Node)
			, _tail(new Node)
			, _promoteRate(0.5)
			, _maxLevel(0)
		{
			_head->_right = _tail;
			_tail->_left = _head;
		}

		~SkipList()
		{
			clear();

			delete _head;
			delete _tail;
		}

		//懒得写拷贝构造，就直接防拷贝了
		/*
		SkipList(const SkipList&) = delete;
		SkipList& operator=(const SkipList&) = delete;
		*/

		//插入元素
		bool insert(const T& data)
		{
			//找到前驱节点的位置
			Node* prev = findPrev(data);
			if (prev->_data == data)
			{
				//如果相同，则说明已经插入，直接返回即可
				return false;
			}

			//将节点追加到前驱节点后面
			Node* cur = new Node(data);
			appendNode(prev, cur);

			//判断是否需要晋升
			int curLevel = 0;
			std::default_random_engine eg;	//随机数生成引擎
			std::uniform_real_distribution<double> random(0, 1); //随机数分布对象

			//如果抛到正面则一直晋升
			while (random(eg) < _promoteRate)
			{
				//判断当前是否为最高层，如果是最高层则需要增加层数
				if (curLevel == _maxLevel)
				{
					addLever();
				}

				//找到上一层的前驱节点
				while (prev->_up == nullptr)
				{
					prev = prev->_left;
				}
				prev = prev->_up;
				
				//构造cur节点的上层索引节点,插入到上层的前驱节点后
				Node* upCur = new Node(data);
				appendNode(prev, upCur);

				upCur->_down = cur;
				cur->_up = upCur;
				cur = upCur;	//继续往上晋升

				++curLevel;
			}

			return true;
		}

		//删除元素
		bool erase(const T& data)
		{
			Node* cur = find(data);
			if (cur == nullptr)
			{
				//如果为空则说明该节点不存在，不需要删除
				return false;
			}

			//自底向上将该节点及它的索引删除
			int curLevel = 0;
			while (cur != nullptr)
			{
				cur->_right->_left = cur->_left;
				cur->_left->_right = cur->_right;
				
				//如果当前为层只有该节点，则删除这一层
				if (curLevel != 0 && cur->_right->_data == INT_MAX && cur->_left->_data == INT_MAX)
				{
					earseLevel(cur->_left);
				}
				else
				{
					++curLevel;
				}

				//删除该层的节点后继续往上删除索引
				Node* upCur = cur->_up;
				delete cur;
				cur = upCur;
			}
			return true;
		}

		//删除全部节点
		void clear()
		{
			//从最底层开始遍历，一个一个顺着往上删除
			Node* cur = _head;
			while (cur->_down != nullptr)
			{
				cur = cur->_down;
			}

			if (cur->_right->_data == INT_MAX)
			{
				return;
			}

			//删除所有节点
			cur = cur->_right;
			while (cur->_data != INT_MAX)
			{
				Node* next = cur->_right;
				erase(cur->_data);
				cur = next;
			}
		}

		//查找元素
		Node* find(const T& data)
		{
			Node* ret = findPrev(data);

			//如果找到了则返回节点，没找到则返回空指针
			if (ret->_data == data)
			{
				return ret;
			}
			
			return nullptr;
		}

		void printAll()
		{
			Node* cur = _head;
			while (cur->_down != nullptr)
			{
				cur = cur->_down;
			}

			cur = cur->_right;
			while (cur->_data != INT_MAX)
			{
				std::cout << cur->_data << std::ends;
				cur = cur->_right;
			}
		}
	private:
		//查找前驱节点
		Node* findPrev(const T& data)
		{
			Node* cur = _head;
			while (1)
			{
				//找到该层最接近目标的索引
				while (cur->_right->_data != INT_MAX && Compare()(cur->_right->_data, data))
				{
					cur = cur->_right;
				}

				//如果当前已经到了最底层，则说明当前位置就是前驱节点,否则继续往下
				if (cur->_down == nullptr)
				{
					break;
				}
				else
				{
					cur = cur->_down;
				}
			}
			return cur;
		}

		//在前驱节点后面插入节点
		void appendNode(Node* prev, Node* cur)
		{
			cur->_left = prev;
			cur->_right = prev->_right;

			prev->_right->_left = cur;
			prev->_right = cur;
		}

		//增加一层
		void addLever()
		{
			Node* upHead = new Node();
			Node* upTail = new Node();

			//修改相互关系
			upHead->_right = upTail;
			upTail->_left = upHead;

			upHead->_down = _head;
			_head->_up = upHead;

			upTail->_down = _tail;
			_tail->_up = upTail;

			//因为查询是自顶向下的，所以将新的头尾节点作为当前的头尾节点
			_head = upHead;
			_tail = upTail;

			++_maxLevel;	//层数加一
		}

		//删除一层
		void earseLevel(const Node* upHead)
		{
			Node* upTail = upHead->_right;
			//如果当前为最高层,则可以直接删除
			if (upTail->_up == nullptr)
			{
				upHead->_down->_up = nullptr;
				upTail->_down->_up = nullptr;

				//更换新的首尾
				_head = upHead->_down;
				_tail = upTail->_down;
			}
			else
			{
				upHead->_up->_down = upHead->_down;
				upHead->_down->_up = upHead->_up;
				upTail->_up->_down = upTail->_down;
				upTail->_down->_up = upTail->_up;
			}
			
			delete upHead;
			delete upTail;

			--_maxLevel;
		}
	};
};