#include<vector>

namespace lee
{
	class UnionFindSet
	{
	public:
		UnionFindSet(size_t size)
			: _ufs(size, -1)
		{}

		int FindRoot(int index)
		{
			//根节点的值为负数，如果不为负则说明不是根节点，继续找
			while (_ufs[index] >= 0)
			{
				//因为每个节点存储自己父节点的下标，所以往上继续查找
				index = _ufs[index];
			}

			return index;
		}

		bool Union(int x1, int x2)
		{
			int root1 = FindRoot(x1);
			int root2 = FindRoot(x2);

			//本来就是一个集合
			if (root1 == root2)
			{
				return false;
			}

			//选择root1作为根，将root2所在集合合并到root1中
			_ufs[root1] += _ufs[root2];
			//将另一个的父节点设置为root1
			_ufs[root2] = root1;

			return true;
		}

		//求集合的个数，即负节点的个数
		size_t count() const
		{
			size_t count = 0;
			for (auto it : _ufs)
			{
				if (it < 0)
				{
					count++;
				}
			}

			return count;
		}

	private:
		std::vector<int> _ufs;
	};
};

