#pragma once
#include<cassert>

namespace lee
{
	//节点
	template<class T>
	struct __list_node
	{
		__list_node<T>* _next;
		__list_node<T>* _prev;
		T _data;

		__list_node(const T& data = T())
			: _data(data)
			, _next(nullptr)
			, _prev(nullptr)
		{}
	};

	//迭代器
	//使用三个模板参数来实现代码复用，可以根据传的参数来同时实现const_iterator和iterator
	//为了能够模拟迭代器，需要重载对应的运算符
	template<class T, class Ref, class Ptr>
	struct __list_iterator
	{
		typedef __list_node<T> Node;
		typedef __list_iterator<T, Ref, Ptr> Self;
		Node* _node;

		__list_iterator(Node* node)
			:_node(node)
		{}

		Ref operator*()
		{
			return _node->_data;
		}

		//对于自定义类型的data，这里其实有两个->->,第一个返回对象的指针，第二次才会通过那个指针访问到数据，这里被编译器优化成一个
		Ptr operator->()
		{
			return &_node->_data;
		}

		Self& operator++()
		{
			_node = _node->_next;
			
			return *this;
		}

		Self operator++(int)
		{
			Self temp(*this);

			++(*this);

			return temp;
		}

		Self& operator--()
		{
			_node = _node->_prev;

			return *this;
		}

		Self operator--(int)
		{
			Self temp(*this);

			--(*this);

			return temp;
		}

		bool operator==(const Self& it)
		{
			return _node == it._node;
		}

		bool operator!=(const Self& it)
		{
			return _node != it._node;
		}

	};

	template<class T>
	class list
	{
	public:
		typedef __list_node<T> Node;
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;

		/*
		------------------------------------------------------------
		默认成员函数部分
		Member functions
		------------------------------------------------------------
		*/

		list() : _head(new Node)
		{
			_head->_next = _head;
			_head->_prev = _head;
		}

		list(const list<T>& l) : _head(new Node)
		{
			_head->_next = _head;
			_head->_prev = _head;

			for (auto it : l)
			{
				push_back(it);
			}
		}

		list<T>& operator=(list<T> l)
		{
			swap(l);
			return *this;
		}

		~list()
		{
			clear();

			delete _head;
			_head = nullptr;
		}

		/*
		------------------------------------------------------------
		迭代器部分
		Iterators:
		------------------------------------------------------------
		*/
		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const 
		{
			return const_iterator(_head);
		}

		/*
		------------------------------------------------------------
		修改部分
		Modifiers:
		------------------------------------------------------------
		*/

		void swap(list<T>& l)
		{
			std::swap(_head, l._head);
		}

		iterator insert(iterator pos, const T& val)
		{
			assert(pos._node != nullptr);

			Node* cur = pos._node;
			Node* prev = cur->_prev;

			Node* newNode = new Node(val);

			prev->_next = newNode;
			cur->_prev = newNode;
			newNode->_next = cur;
			newNode->_prev = prev;


			return iterator(newNode);
		}

		iterator erase(iterator pos)
		{			
			assert(_head->_next != _head);

			Node* cur = pos._node;
			Node* next = cur->_next;

			next->_prev = cur->_prev;
			cur->_prev->_next = next;
			delete cur;

			return iterator(next);
		}

		//和数据结构里面实现的一样，可以直接复用insert和erase
		void push_back(const T& val)
		{
			insert(end(), val);
			//head
		}

		
		void pop_back() 
		{ 
			erase(--end()); 
			//head->prev
		}

		void push_front(const T& val)
		{
			insert(begin(), val);
			//head->next;
		}

		void pop_front()
		{
			erase(begin());
			//head->next;
		}
		
		void clear()
		{
			auto it = begin();

			while (it != end())
			{
				it = erase(it);
			}
		}

		/*
		------------------------------------------------------------
		元素访问部分
		Element access:
		------------------------------------------------------------
		*/
		T& front()
		{
			return _head->_next->_data;
		}

		const T& front()const
		{
			return _head->_next->_data;
		}

		T& back()
		{
			return _head->_prev->_data;
		}

		const T& back()const
		{
			return _head->_prev->_data;
		}

		/*
		------------------------------------------------------------
		容量部分
		Capacity
		------------------------------------------------------------
		*/
		size_t size()const
		{
			size_t count = 0;
			auto it = begin();

			while (it != end())
			{
				count++;
				it++;
			}

			return count;
		}

		bool empty()const
		{
			return _head->_next == _head;
		}

	private:
		Node* _head;
	};
}