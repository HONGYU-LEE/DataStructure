#pragma once
#include<iostream>

namespace lee
{
	enum Color
	{
		BLACK,
		RED,
	};

	//template<class K, class V>
	//struct KeyOfValue
	//{
	//	const K& operator()(const std::pair<K, V>& kv)
	//	{
	//		return kv.first;
	//	}
	//};

	template<class T>
	struct RBTreeNode
	{
		typedef RBTreeNode<T> Node;

		RBTreeNode(const T& data = T(), const Color& color = RED) 
			: _left(nullptr)
			, _right(nullptr)
			, _parent(nullptr)
			, _data(data)
			, _color(color)
		{}

		Node* _left;
		Node* _right;
		Node* _parent;
		T _data;
		Color _color;
	};

	template<class T, class Ptr, class Ref>
	class __RBTreeIterator
	{

	public:
		typedef RBTreeNode<T> Node;
		typedef __RBTreeIterator<T, Ptr, Ref> Self;

		__RBTreeIterator(Node* node) : _node(node)
		{}

		Ref operator *()
		{
			return _node->_data;
		}

		//调用时其实调用的是->->，这里返回的是数据对象的指针，然后再从指针中取数据。编译器优化所以只看到一个
		Ptr operator ->()
		{
			return &_node->_data;
		}

		//红黑树迭代器的++ --其实就是其在中序遍历中的次序变化
		Self& operator++()
		{
			/*
				中序遍历：先访问所有节点的左子树，接着访问这些节点的右子树。
				而++，其实就是其在中序遍历的下一个位置
				1.如果当前节点的右子树不为空，则说明当前节点的右子树还没遍历完，下一个位置则是右子树的最左节点。

				2.如果此时右子树为空，则说明当前节点的所有子树访问完，但是当前节点也可能为其他树的右子树，所以一直往上，找到孩子为父亲的左子树的结点，那个父亲的位置则是下一个位置
			*/
			if (_node->_right)
			{
				Node* cur = _node->_right;

				//找到右子树的最左节点
				while (cur->_left)
				{
					cur = cur->_left;
				}

				_node = cur;
			}
			else
			{
				Node* parent = _node->_parent;
				Node* cur = _node;
				
				//往上找，直到父节点为空或者孩子节点为父节点的左子树
				while (parent->_right == cur)
				{
					cur = parent;
					parent = parent->_parent;
				}

				_node = parent;
			}
			
			return *this;
		}

		Self operator++(int)
		{
			Self temp(*this);
			++(*this);

			return temp;
		}
		/*
				而--，其实就是其在中序遍历的上一个位置，思路和++差不多
				1.如果当前节点的左子树不为空，则访问左子树的最右节点
				2.如果此时左子树为空，则说明子树的最左节点已经访问，接着就往上查找，找到孩子为父亲的右节点的位置，那个父亲就是下一个位置
		*/
		Self& operator--()
		{
			if (_node->_parent->_parent == _node && _node->_color == RED)
			{
				//如果此节点为头结点，则说明--应该回到最右子树的位置，也就是头结点的右子树，而因为头结点和根节点形成闭环，所以当
				//_node->_parent->_parent == _node，并且color为红时，说明为_head。
				
				_node = _node->_right;
			}
			else if (_node->_left)
			{
				Node* cur = _node->_left;

				//找到左子树的最右节点
				while (cur && cur->_right)
				{
					cur = cur->_right;
				}

				_node = cur;
			}
			else
			{
				Node* parent = _node->_parent;
				Node* cur = _node;

				//往上找，直到父节点为空或者孩子节点为父节点的右子树
				while (parent->_right != cur)
				{
					cur = parent;
					parent = parent->_parent;
				}

				_node = parent;
			}
			return *this;
		}

		Self operator--(int)
		{
			Self temp(*this);
			--(*this);

			return temp;
		}
		bool operator==(const Self& s)
		{
			return _node == s._node;
		}

		bool operator!=(const Self& s)
		{
			return _node != s._node;
		}

	private:
		Node* _node;
	};

	template<class K, class T, class KOfV>
	class RBTree
	{

	public:
		typedef RBTreeNode<T> Node;
		typedef __RBTreeIterator<T, T*, T&> iterator;
		typedef __RBTreeIterator<T, const T*, const T&> const_iterator;

		RBTree() 
			: _head(new Node(T(), RED))
		{
			_head->_left = _head;
			_head->_right = _head;
			_head->_parent = _head;
		}

		~RBTree()
		{
			destory(_head->_parent);
		}

		//头结点的左子树即是begin()
		iterator begin() 
		{
			return iterator(_head->_left);
		}

		//头结点本身就是end()
		iterator end() 
		{
			return iterator(_head);
		}

		const_iterator begin() const
		{
			return iterator(_head->_left);
		}

		const_iterator end() const
		{
			return iterator(_head);
		}

		Node* leftMax()
		{
			Node* cur = _head->_parent;

			while (cur && cur->_left)
			{
				cur = cur->_left;
			}

			return cur;
		}

		Node* rightMax()
		{
			Node* cur = _head->_parent;

			while (cur && cur->_right)
			{
				cur = cur->_right;
			}

			return cur;
		}

		void _InOrderTravel(Node* root) const
		{
			if (root == nullptr)
				return;

			_InOrderTravel(root->_left);

			std::cout << root->_data.first << ':' << root->_data.second << std::endl;

			_InOrderTravel(root->_right);
		}

		void InOrderTravel() const
		{
			_InOrderTravel(_head->_parent);
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

		//右旋
		void RotateR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			parent->_left = subLR;

			//如果subLR存在，则让他的父节点指向parent。
			if (subLR)
			{
				subLR->_parent = parent;
			}

			subL->_right = parent;

			Node* ppNode = parent->_parent;
			parent->_parent = subL;

			//两种情况
			//如果parent为根节点，则让subL成为新的根节点
			if (parent == _head->_parent)
			{
				_head->_parent = subL;
				subL->_parent = _head;
			}
			//如果不是根节点，则改变subL与其祖父节点的指向关系
			else
			{
				if (ppNode->_left == parent)
				{
					ppNode->_left = subL;
				}
				else
				{
					ppNode->_right = subL;
				}

				subL->_parent = ppNode;
			}
		}

		//左旋
		void RotateL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;

			parent->_right = subRL;

			if (subRL)
			{
				subRL->_parent = parent;
			}

			subR->_left = parent;
			Node* ppNode = parent->_parent;
			parent->_parent = subR;

			if (parent == _head->_parent)
			{
				_head->_parent = subR;
				subR->_parent = _head;
			}
			else
			{
				if (ppNode->_left == parent)
				{
					ppNode->_left = subR;
				}
				else
				{
					ppNode->_right = subR;
				}

				subR->_parent = ppNode;
			}
		}

		iterator Find(const T& data)
		{
			//根据二叉搜索树的性质，从根节点出发，比根节点大则查找右子树，比根节点小则查找左子树
			Node* cur = _head->_parent;
			KOfV kofv;

			while (cur)
			{
				//比根节点大则查找右子树
				if (koft(data) > kofv(cur->_data))
				{
					cur = cur->_right;
				}
				//比根节点小则查找左子树
				else if (koft(data) < kofv(cur->_data))
				{
					cur = cur->_left;
				}
				//相同则返回
				else
				{
					return iterator(cur);
				}
			}

			//遍历完则说明查找不到，返回false
			return iterator(_head);
		}

		std::pair<iterator, bool> Insert(const T& data)
		{
			KOfV kofv;

			//按照二叉搜索树的规则先找到位置
			//创建根节点
			if (_head->_parent == _head)
			{
				Node* root = new Node(data, BLACK);

				//形成环形结构
				root->_parent = _head;
				_head->_left = root;
				_head->_right = root;
				_head->_parent = root;

				return std::make_pair(iterator(_head->_parent), true);
			}

			Node* cur = _head->_parent;
			Node* parent = _head;

			while (cur)
			{
				if (kofv(data) > kofv(cur->_data))
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (kofv(data) < kofv(cur->_data))
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return std::make_pair(iterator(cur), false);
				}
			}

			//新插入节点为红色
			cur = new Node(data, RED);

			//保存插入的结点，因为后面会往上更新红黑树，所以cur可能会变化。
			Node* newNode = cur;

			//判断插入位置
			if (kofv(cur->_data) > kofv(parent->_data))
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}
			cur->_parent = parent;

			//更新红黑树，如果父节点的颜色为黑，则说明满足条件，不需要处理，如果为红，则说明不满足，需要处理。
			while (cur != _head->_parent->_parent && parent && parent->_color == RED)
			{
				Node* ppNode = parent->_parent;

				//如果父节点为祖父的左子树
				if (ppNode->_left == parent)
				{
					//此时判断叔叔节点的状态，红黑树状态取决于叔叔
					Node* uncle = ppNode->_right;

					//第一种情况，如果叔叔节点存在且为红，则直接把父亲和叔叔变黑，祖父节点边红即可。然后再从祖父的位置继续往上调整
					if (uncle && uncle->_color == RED)
					{
						//变色
						uncle->_color = parent->_color = BLACK;
						ppNode->_color = RED;

						//继续往上
						cur = ppNode;
						parent = cur->_parent;
					}
					/*
						叔叔节点为黑或者不存在，此时有两种情况
						情况二：cur为父节点的左子树，即直线状态。
						情况三：cur为父节点的右子树，即折线状态。

						情况二单旋一次后更改颜色即可完成
						对于情况三，如果将其进行一次旋转后再稍微处理，就可以转换成情况二
					 */
					else
					{
						//因为这里的双旋和AVL不一样，可以不用处理平衡因子，所以如果为折线则先旋转处理后，将其转换为直线处理即可。

						//第三种情况，折线状态，转换为直线状态处理
						if (parent->_right == cur)
						{
							RotateL(parent);
							//单旋后再交换节点，即可变成直线状态。
							std::swap(parent, cur);
						}

						//处理第二种状态
						RotateR(ppNode);

						parent->_color = BLACK;
						ppNode->_color = RED;

						//处理完成
						break;
					}

				}
				//如果父亲为祖父的右子树
				else
				{
					//此时叔叔为左子树。
					Node* uncle = ppNode->_left;

					if (uncle && uncle->_color == RED)
					{
						uncle->_color = parent->_color = BLACK;
						ppNode->_color = RED;

						cur = ppNode;
						parent = cur->_parent;
					}
					else
					{
						if (parent->_left == cur)
						{
							RotateR(parent);
							std::swap(cur, parent);
						}

						RotateL(ppNode);

						ppNode->_color = RED;
						parent->_color = BLACK;

						break;
					}
				}
			}

			//为了防止不小心把根节点改为红色，最后手动改为黑色即可
			_head->_parent->_color = BLACK;

			//插入后更新头结点的状态。
			_head->_left = leftMax();
			_head->_right = rightMax();

			return std::make_pair(iterator(newNode), true);
		}

		/*
			判断是否为红黑树，就是判断其是否满足红黑树的特性

			特性：	3.根节点必须为黑节点
					1.不存在连续的红结点
				    2.从某一节点出发到其所有的叶子节点，其中经过的黑色节点数量相等
				  
		*/
		bool IsRBTree()
		{
			if (_head->_parent == nullptr)
			{
				//空树也是红黑树
				return true;
			}

			//违反性质1
			if (_head->_parent->_color != BLACK)
			{
				return false;
			}

			//获取从根节点出发的任意一条子路径的黑色节点数，这里选取最左子树。
			Node* cur = _head->_parent;
			size_t blackCount = 0;
			size_t count = 0;

			while (cur)
			{
				if (cur->_color == BLACK)
				{
					blackCount++;
				}

				cur = cur->_left;
			}

			//递归判断其他路径的黑色节点数
			return _IsRBTree(_head->_parent, count, blackCount);
		}

		bool _IsRBTree(Node* root, size_t count, const size_t blackCount)
		{
			//此时说明已经走到叶子节点，判断黑色节点数是否相等，不相等则违反性质3
			if (root == nullptr)
			{
				if (count != blackCount)
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			//如果没走完，就接着判断其他情况

			//判断性质2，如果存在连续的红结点，则返回错误
			Node* parent = root->_parent;

			if (parent && root->_color == RED && parent->_color == RED)
			{
				return false;
			}

			//如果当前节点为黑色，则记录
			if (root->_color == BLACK)
			{
				count++;
			}

			//接着递归判断当前节点的所有路径
			return _IsRBTree(root->_left, count, blackCount) && _IsRBTree(root->_right, count, blackCount);
		}
		
	private:
		//封装一个头结点，头结点的父亲指向根节点，左子树指向begin()也就是最左节点，右子树则为最右节点，这么做的意义是因为end(）要返回最右节点的下一个节点。
		//并且头结点为红色，用于区分根节点
		Node* _head;
	};
}