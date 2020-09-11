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

	//����ڵ�
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
		Node* _head;	//ͷ�ڵ�
		Node* _tail;	//β�ڵ�
		double _promoteRate;	//��������
		int _maxLevel;	//��߲���

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

		//����д�������죬��ֱ�ӷ�������
		/*
		SkipList(const SkipList&) = delete;
		SkipList& operator=(const SkipList&) = delete;
		*/

		//����Ԫ��
		bool insert(const T& data)
		{
			//�ҵ�ǰ���ڵ��λ��
			Node* prev = findPrev(data);
			if (prev->_data == data)
			{
				//�����ͬ����˵���Ѿ����룬ֱ�ӷ��ؼ���
				return false;
			}

			//���ڵ�׷�ӵ�ǰ���ڵ����
			Node* cur = new Node(data);
			appendNode(prev, cur);

			//�ж��Ƿ���Ҫ����
			int curLevel = 0;
			std::default_random_engine eg;	//�������������
			std::uniform_real_distribution<double> random(0, 1); //������ֲ�����

			//����׵�������һֱ����
			while (random(eg) < _promoteRate)
			{
				//�жϵ�ǰ�Ƿ�Ϊ��߲㣬�������߲�����Ҫ���Ӳ���
				if (curLevel == _maxLevel)
				{
					addLever();
				}

				//�ҵ���һ���ǰ���ڵ�
				while (prev->_up == nullptr)
				{
					prev = prev->_left;
				}
				prev = prev->_up;
				
				//����cur�ڵ���ϲ������ڵ�,���뵽�ϲ��ǰ���ڵ��
				Node* upCur = new Node(data);
				appendNode(prev, upCur);

				upCur->_down = cur;
				cur->_up = upCur;
				cur = upCur;	//�������Ͻ���

				++curLevel;
			}

			return true;
		}

		//ɾ��Ԫ��
		bool erase(const T& data)
		{
			Node* cur = find(data);
			if (cur == nullptr)
			{
				//���Ϊ����˵���ýڵ㲻���ڣ�����Ҫɾ��
				return false;
			}

			//�Ե����Ͻ��ýڵ㼰��������ɾ��
			int curLevel = 0;
			while (cur != nullptr)
			{
				cur->_right->_left = cur->_left;
				cur->_left->_right = cur->_right;
				
				//�����ǰΪ��ֻ�иýڵ㣬��ɾ����һ��
				if (curLevel != 0 && cur->_right->_data == INT_MAX && cur->_left->_data == INT_MAX)
				{
					earseLevel(cur->_left);
				}
				else
				{
					++curLevel;
				}

				//ɾ���ò�Ľڵ���������ɾ������
				Node* upCur = cur->_up;
				delete cur;
				cur = upCur;
			}
			return true;
		}

		//ɾ��ȫ���ڵ�
		void clear()
		{
			//����ײ㿪ʼ������һ��һ��˳������ɾ��
			Node* cur = _head;
			while (cur->_down != nullptr)
			{
				cur = cur->_down;
			}

			if (cur->_right->_data == INT_MAX)
			{
				return;
			}

			//ɾ�����нڵ�
			cur = cur->_right;
			while (cur->_data != INT_MAX)
			{
				Node* next = cur->_right;
				erase(cur->_data);
				cur = next;
			}
		}

		//����Ԫ��
		Node* find(const T& data)
		{
			Node* ret = findPrev(data);

			//����ҵ����򷵻ؽڵ㣬û�ҵ��򷵻ؿ�ָ��
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
		//����ǰ���ڵ�
		Node* findPrev(const T& data)
		{
			Node* cur = _head;
			while (1)
			{
				//�ҵ��ò���ӽ�Ŀ�������
				while (cur->_right->_data != INT_MAX && Compare()(cur->_right->_data, data))
				{
					cur = cur->_right;
				}

				//�����ǰ�Ѿ�������ײ㣬��˵����ǰλ�þ���ǰ���ڵ�,�����������
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

		//��ǰ���ڵ�������ڵ�
		void appendNode(Node* prev, Node* cur)
		{
			cur->_left = prev;
			cur->_right = prev->_right;

			prev->_right->_left = cur;
			prev->_right = cur;
		}

		//����һ��
		void addLever()
		{
			Node* upHead = new Node();
			Node* upTail = new Node();

			//�޸��໥��ϵ
			upHead->_right = upTail;
			upTail->_left = upHead;

			upHead->_down = _head;
			_head->_up = upHead;

			upTail->_down = _tail;
			_tail->_up = upTail;

			//��Ϊ��ѯ���Զ����µģ����Խ��µ�ͷβ�ڵ���Ϊ��ǰ��ͷβ�ڵ�
			_head = upHead;
			_tail = upTail;

			++_maxLevel;	//������һ
		}

		//ɾ��һ��
		void earseLevel(const Node* upHead)
		{
			Node* upTail = upHead->_right;
			//�����ǰΪ��߲�,�����ֱ��ɾ��
			if (upTail->_up == nullptr)
			{
				upHead->_down->_up = nullptr;
				upTail->_down->_up = nullptr;

				//�����µ���β
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