#pragma once
#include<iostream>

namespace lee
{
	template<class K, class V>
	struct AVLTreeNode
	{
		AVLTreeNode(const std::pair<K, V>& kv)
			: _left(nullptr)
			, _right(nullptr)
			, _parent(nullptr)
			, _kv(kv)
			, _bf(0)
		{}

		AVLTreeNode<K, V>* _left;
		AVLTreeNode<K, V>* _right;
		AVLTreeNode<K, V>* _parent;
		std::pair<K, V> _kv;
		int _bf;
	};

	template<class K, class V>
	class AVLTree
	{
	public:
		typedef AVLTreeNode<K, V> Node;

		AVLTree() : _root(nullptr)
		{}

		~AVLTree()
		{
			destory(_root);
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
			if (parent == _root)
			{
				_root = subL;
				subL->_parent = nullptr;
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

			//左旋完成后平衡，平衡因子归零。
			subL->_bf = parent->_bf = 0;
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

			if (parent == _root)
			{
				_root = subR;
				subR->_parent = nullptr;
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

			subR->_bf = parent->_bf = 0;
		}

		//右左双旋
		void RotateRL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;
			//这里需要保存subRL的平衡因子，来调节旋转完后的平衡因子
			int bf = subRL->_bf;

			//先右单旋将折线结构转换为直线结构，也就是前面单旋就可以解决的问题。
			RotateR(subR);
			//然后再左单旋即可
			RotateL(parent);

			//根据subRL的bf来调节旋转后的平衡因子
			if (bf == 1)
			{
				parent->_bf = -1;
				subR->_bf = 0;
				subRL->_bf = 0;
			}
			else if (bf == -1)
			{
				parent->_bf = 0;
				subR->_bf = 1;
				subRL->_bf = 0;
			}
			else
			{
				parent->_bf = 0;
				subR->_bf = 0;
				subRL->_bf = 0;
			}
		}


		//左右双旋
		void RotateLR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;

			int bf = subLR->_bf;

			RotateL(subL);
			RotateR(parent);

			if (bf == 1)
			{
				parent->_bf = 0;
				subL->_bf = -1;
				subLR->_bf = 0;
			}
			else if (bf == -1)
			{
				parent->_bf = 1;
				subL->_bf = 0;
				subLR->_bf = 0;
			}
			else
			{
				parent->_bf = 0;
				subL->_bf = 0;
				subLR->_bf = 0;
			}
		}

		bool Insert(const std::pair<K, V>& kv)
		{
			//按照二叉搜索树的规则先找到位置
			if (_root == nullptr)
			{
				_root = new Node(kv);
				return true;
			}

			Node* parent = nullptr;
			Node* cur = _root;

			while (cur)
			{
				if (kv.first > cur->_kv.first)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (kv.first < cur->_kv.first)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return false;
				}
			}

			//插入节点
			cur = new Node(kv);

			//判断插入位置
			if (cur->_kv.first > parent->_kv.first)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}

			cur->_parent = parent;

			//更新平衡因子
			while (parent)
			{
				//更新父节点的平衡因子
				if (cur == parent->_left)
				{
					parent->_bf--;
				}
				else
				{
					parent->_bf++;
				}

				//判断更新后父节点是否平衡
				
				//平衡
				if (parent->_bf == 0)
				{
					break;
				}
				//高度发生变化，要继续往上判断
				else if (parent->_bf == 1 || parent->_bf == -1)
				{
					cur = parent;
					parent = parent->_parent;
				}
				//此时不平衡，需要旋转
				else if (parent->_bf == 2 || parent->_bf == -2)
				{
					//旋转分四种情况，直线单旋，折线双旋

					if (parent->_bf == 2)
					{
						//如果右边不平衡，并且子节点也是右边偏重，则左单旋
						if (cur->_bf == 1)
						{
							RotateL(parent);
						}
						//如果右边不平衡，而子节点是左边偏重，此时需要先转换为上面的状态，先右单旋再左单旋。但是不能直接右单旋再左单旋，还需要根据情况处理平衡因子
						else
						{
							RotateRL(parent);
						}
					}
					else
					{
						//左边不平衡，并且子节点也是左边偏重，右单旋
						if (cur->_bf == -1)
						{
							RotateR(parent);
						}
						//同上，左右双旋
						else
						{
							RotateLR(parent);
						}
					}

					//旋转完后恢复平衡，更新结束。
					break;
				}
			}

			return true;
		}

		Node* Find(const K& key)
		{
			//根据二叉搜索树的性质，从根节点出发，比根节点大则查找右子树，比根节点小则查找左子树
			Node* cur = _root;

			while (cur)
			{
				//比根节点大则查找右子树
				if (key > cur->_kv.first)
				{
					cur = cur->_right;
				}
				//比根节点小则查找左子树
				else if (key < cur->_kv.first)
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

		bool erase(const K& key)
		{
			//删除直接按照二叉搜索树的规则删除，然后再进行平衡因子的更新即可
			Node* cur = _root;
			Node* parent = cur;

			
			/*
				删除有三种情况，一种是删除叶子节点，可以直接删除
				第二种情况，如果删除的节点只有一个子树，那么删除这个节点后，就让父节点指向他的这一子树
				前两种情况可以合并处理

				第三种情况则是左右子树都不为空，此时选择一个来节点来替换他后，再删除，就可以不破坏原有结构
				如果要保持原有结构不变化，那么选择的节点必须要和删除节点在中序遍历中是连续的，而满足的只有两个节点，一个是其左子树的最大值，一个是其右子树的最小值。
			*/
			//删除部分
			while (cur)
			{
				//找到删除的位置
				if (key > cur->_kv.first)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (key < cur->_kv.first)
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
						std::swap(cur->_kv, LeftMax->_kv);

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

					//删除成功，中断
					break;
				}
			}

			//查找不到
			if (cur == nullptr)
				return false;

			//更新平衡因子
			while (parent)
			{
				//更新父节点的平衡因子
				if (cur == parent->_left)
				{
					parent->_bf++;
				}
				else
				{
					parent->_bf--;
				}

				//判断更新后父节点是否平衡

				//平衡
				if (parent->_bf == 0)
				{
					break;
				}
				//高度发生变化，要继续往上判断
				else if (parent->_bf == 1 || parent->_bf == -1)
				{
					cur = parent;
					parent = parent->_parent;
				}
				//此时不平衡，需要旋转
				else if (parent->_bf == 2 || parent->_bf == -2)
				{
					//旋转分四种情况，直线单旋，折线双旋

					if (parent->_bf == 2)
					{
						//如果右边不平衡，并且子节点也是右边偏重，则左单旋
						if (cur->_bf == 1)
						{
							RotateL(parent);
						}
						//如果右边不平衡，而子节点是左边偏重，此时需要先转换为上面的状态，先右单旋再左单旋。但是不能直接右单旋再左单旋，还需要根据情况处理平衡因子
						else
						{
							RotateRL(parent);
						}
					}
					else
					{
						//左边不平衡，并且子节点也是左边偏重，右单旋
						if (cur->_bf == -1)
						{
							RotateR(parent);
						}
						//同上，左右双旋
						else
						{
							RotateLR(parent);
						}
					}

					//旋转完后恢复平衡，更新结束。
					break;
				}
			}

			return true;
		}

		void _InOrderTravel(Node* root) const
		{
			if (root == nullptr)
				return;

			_InOrderTravel(root->_left);

			std::cout << root->_kv.first << ':'  << root->_kv.second << std::endl;

			_InOrderTravel(root->_right);
		}

		void InOrderTravel() const
		{
			_InOrderTravel(_root);
		}

		int countHeight(Node* root) const
		{
			if (root == nullptr)
				return 0;

			int leftHeight = countHeight(root->_left);
			int rightHeight = countHeight(root->_right);

			return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
		}

		bool _IsBalance(Node* root) const
		{
			if (root == nullptr)
				return true;

			int leftHeight = countHeight(root->_left);
			int rightHeight = countHeight(root->_right);

			return abs(leftHeight - rightHeight) < 2
				&& _IsBalance(root->_left)
				&& _IsBalance(root->_right);
		}

		bool IsBalance() const
		{
			return _IsBalance(_root);
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
	private:
		Node* _root;
	};
};