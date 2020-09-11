#include<iostream>

namespace lee
{

	template<class K, class V>
	class BSTreeNode
	{
	public:
		BSTreeNode(const K& key = K(), const V& value = V())
			: _left(nullptr)
			, _right(nullptr)
			, _key(key)
			, _value(value)
		{}

		BSTreeNode<K, V>* _left;
		BSTreeNode<K, V>* _right;
		K _key;
		V _value;
	};

	template<class K, class V>
	class BSTree
	{
		typedef BSTreeNode<K, V> Node;
		typedef BSTree<K, V> Tree;

	public:
		BSTree() : _root(nullptr)
		{}

		~BSTree()
		{
			destory(_root);
		}

		BSTree(const Tree& temp) : _root(nullptr)
		{
			_root = copy(temp._root);
		}

		Tree& operator=(const Tree& temp)
		{
			if (this != &temp)
			{
				//����ձ���
				destory(_root);
				_root = copy(temp._root);
			}

			return *this;
		}

		//�ִ�д��
		//Tree& operator=(Tree temp)
		//{
		//	swap(temp);

		//	return *this;
		//}

		void swap(Tree& temp)
		{
			std::swap(_root, temp._root);
		}

		Node* copy(const Node* root)
		{
			if (!root)
				return nullptr;

			Node* temp = new Node(root->_key, root->_value);
			temp->_left = copy(root->_left);
			temp->_right = copy(root->_right);

			return temp;
		}

		void destory(Node*& root)
		{
			Node* node = root;
			if (!root)
				return;

			destory(node->_left);
			destory(node->_right);

			delete node;
			node = nullptr;
		}

		bool Insert(const K& key, const V& value)
		{
			//�����ʱ��Ϊ�գ����ʼ�����ڵ�
			if (_root == nullptr)
			{
				_root = new Node(key, value);
				return true;
			}

			Node* cur = _root;
			Node* parent = cur;
			
			//�ҵ����ʵĲ���λ��
			while (cur)
			{
				//�ȸ��ڵ�������������
				if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				//�ȸ��ڵ�С�����������
				else if (key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				//��ͬ�򷵻�false,��Ϊ���������ܴ�����ͬ����
				else
				{
					return false;
				}
			}

			cur = new Node(key, value);
			
			//�ж�curҪ���뵽parent������������������
			if (parent->_key > key)
			{
				parent->_left = cur;
			}
			else if (parent->_key < key)
			{
				parent->_right = cur;
			}

			return true;
		}

		bool erase(const K& key)
		{
			/*
				ɾ�������������һ����ɾ��Ҷ�ӽڵ㣬����ֱ��ɾ��
				�ڶ�����������ɾ���Ľڵ�ֻ��һ����������ôɾ������ڵ�󣬾��ø��ڵ�ָ��������һ����
				ǰ����������Ժϲ�����

				�������������������������Ϊ�գ���ʱѡ��һ�����ڵ����滻������ɾ�����Ϳ��Բ��ƻ�ԭ�нṹ
				���Ҫ����ԭ�нṹ���仯����ôѡ��Ľڵ����Ҫ��ɾ���ڵ�������������������ģ��������ֻ�������ڵ㣬һ�����������������ֵ��һ����������������Сֵ��
			*/

			Node* cur = _root;
			Node* parent = cur;

			while (cur)
			{
				if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					//ǰ��������ϲ������������ǰ���ֻ��һ�����������ø��ڵ�ָ����������
					//����ֻ��������ʱ					
					if (cur->_left == nullptr)
					{
						//�����ǰ�ڵ�Ϊ���ڵ㣬������������Ϊ�µĸ��ڵ�
						if (cur == _root)
						{
							_root= cur->_left;
						}
						else
						{
							//�жϵ�ǰ�ڵ��������ڵ����һ������
							if (parent->_right == cur)
							{
								parent->_right = cur->_right;
							}
							else
							{
								parent->_left = cur->_right;
							}
						}

						delete cur;
					}
					//����ֻ��������ʱ	
					else if (cur->_right == nullptr)
					{
						//�����ǰ�ڵ�Ϊ���ڵ㣬������������Ϊ�µĸ��ڵ�
						if (cur == _root)
						{
							_root = cur->_right;
						}
						else
						{
							if (parent->_right == cur)
							{
								parent->_right = cur->_left;
							}
							else
							{
								parent->_left = cur->_left;
							}
						}

						delete cur;
					}
					//����������������Ϊ��ʱ,ѡȡ�����������ҽڵ����������������ڵ�
					else
					{
						//������ѡȡ���������������ҽڵ�

						Node* LeftMax = cur->_left;
						Node* LeftMaxParent = cur;

						//�ҵ������������ҽڵ�
						while (LeftMax->_right)
						{
							LeftMaxParent = LeftMax;
							LeftMax = LeftMax->_right;
						}

						//�滻�ڵ�
						cur->_key = LeftMax->_key;
						cur->_value = LeftMax->_value;

						//�жϵ�ǰ�ڵ��������ڵ����һ������, ��Ϊ�Ѿ������������ˣ���������ڵ��������Ϊ�գ��������������ܻ������ݣ������ø��ڵ�ָ������������
						//����ɾ�����ҽڵ�
						if (LeftMax == LeftMaxParent->_left)
						{
							LeftMaxParent->_left = LeftMax->_left;
						}
						else
						{
							LeftMaxParent->_right = LeftMax->_left;
						}

						delete LeftMax;
					}

					return true;
				}

			}
			return false;
		}

		void _InordTravel(Node* root)
		{
			if (root == nullptr)
				return;

			//�ȱ���������
			_InordTravel(root->_left);

			//�������ڵ�
			std::cout << root->_key << ':' << root->_value << std::ends;

			//����������
			_InordTravel(root->_right);
		}

		//�ṩ�����Ľӿڣ���Ϊ����޷�����˽�г�Աroot
		void InordTravel()
		{
			_InordTravel(_root);
			std::cout << std::endl;
		}

		
		Node* Find(const K& key)
		{
			//���ݶ��������������ʣ��Ӹ��ڵ�������ȸ��ڵ����������������ȸ��ڵ�С�����������
			Node* cur = _root;

			while (cur)
			{
				//�ȸ��ڵ�������������
				if (key > cur->_key)
				{
					cur = cur->_right;
				}
				//�ȸ��ڵ�С�����������
				else if (key < cur->_key)
				{
					cur = cur->_left;
				}
				//��ͬ�򷵻�
				else
				{
					return cur;
				}
			}

			//��������˵�����Ҳ���������false
			return nullptr;
		}

	private:
		Node* _root;
	};
}