#include<iostream>

namespace lee
{

	template<class K>
	class BSTreeNode
	{
	public:
		BSTreeNode(const K& key)
			: _left(nullptr)
			, _right(nullptr)
			, _key(key)
		{}

		BSTreeNode<K>* _left;
		BSTreeNode<K>* _right;
		K _key;
	};

	template<class K>
	class BSTree
	{
		typedef BSTreeNode<K> Node;
		typedef BSTree<K> Tree;

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
				//先清空本树
				destory(_root);
				_root = copy(temp._root);
			}

			return *this;
		}

		//现代写法
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
			if(!root)
				return nullptr;

			Node* temp = new Node(root->_key);
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

		bool Insert(const K& key)
		{
			//如果此时树为空，则初始化根节点
			if (_root == nullptr)
			{
				_root = new Node(key);
				return true;
			}

			Node* cur = _root;
			Node* parent = cur;

			//找到合适的插入位置
			while (cur)
			{
				//比根节点大则查找右子树
				if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				//比根节点小则查找左子树
				else if (key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				//相同则返回false,因为搜索树不能存在相同数据
				else
				{
					return false;
				}
			}

			cur = new Node(key);

			//判断cur要插入到parent的左子树还是右子树
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
				删除有三种情况，一种是删除叶子节点，可以直接删除
				第二种情况，如果删除的节点只有一个子树，那么删除这个节点后，就让父节点指向他的这一子树
				前两种情况可以合并处理

				第三种情况则是左右子树都不为空，此时选择一个来节点来替换他后，再删除，就可以不破坏原有结构
				如果要保持原有结构不变化，那么选择的节点必须要和删除节点在中序遍历中是连续的，而满足的只有两个节点，一个是其左子树的最大值，一个是其右子树的最小值。
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
					//前两种情况合并处理，如果当前结点只有一个子树，则让父节点指向他的子树
					//处理只有右子树时					
					if (cur->_left == nullptr)
					{
						//如果当前节点为根节点，则让右子树成为新的根节点
						if (cur == _root)
						{
							_root = cur->_left;
						}
						else
						{
							//判断当前节点是他父节点的哪一个子树
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
					//处理只有左子树时	
					else if (cur->_right == nullptr)
					{
						//如果当前节点为根节点，则让左子树成为新的根节点
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
					//处理左右子树都不为空时,选取左子树的最右节点或者右子树的最左节点
					else
					{
						//这里我选取的是左子树的最右节点

						Node* LeftMax = cur->_left;
						Node* LeftMaxParent = cur;

						//找到左子树的最右节点
						while (LeftMax->_right)
						{
							LeftMaxParent = LeftMax;
							LeftMax = LeftMax->_right;
						}

						//替换节点
						cur->_key = LeftMax->_key;

						//判断当前节点是他父节点的哪一个子树, 因为已经是最右子树了，所以这个节点的右子树为空，但是左子树可能还有数据，所以让父节点指向他的左子树
						//并且删除最右节点
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

			//先遍历左子树
			_InordTravel(root->_left);

			//遍历根节点
			std::cout << root->_key << std::ends;

			//遍历右子树
			_InordTravel(root->_right);
		}

		//提供给外界的接口，因为外界无法访问私有成员root
		void InordTravel()
		{
			_InordTravel(_root);
			std::cout << std::endl;
		}


		Node* Find(const K& key)
		{
			//根据二叉搜索树的性质，从根节点出发，比根节点大则查找右子树，比根节点小则查找左子树
			Node* cur = _root;

			while (cur)
			{
				//比根节点大则查找右子树
				if (key > cur->_key)
				{
					cur = cur->_right;
				}
				//比根节点小则查找左子树
				else if (key < cur->_key)
				{
					cur = cur->_left;
				}
				//相同则返回
				else
				{
					return cur;
				}
			}

			//遍历完则说明查找不到，返回false
			return nullptr;
		}

	private:
		Node* _root;
	};
}
