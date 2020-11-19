#include<vector>

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

	template <class T, class Container = std::vector<T>, class Compare = less<T> >
	class priority_queue
	{
	public:
		priority_queue()
		{}

		template<class iterator>
		priority_queue(iterator begin, iterator end) : _con(begin, end)
		{
			for (int i = (_con.size() - 2) / 2; i >= 0; i--)
			{
				AdjustDown(i);
			}
		}

		void AdjustUp(size_t child)
		{
			size_t parent = (child - 1) / 2;

			while (child > 0)
			{
				if (_com(_con[parent], _con[child]))
				{
					std::swap(_con[child], _con[parent]);
				}
				else
				{
					break;
				}

				child = parent;
				parent = (child - 1) / 2;
			}
		}

		void AdjustDown(size_t root)
		{
			size_t parent = root;
			size_t child = parent * 2 + 1;

			while (child < _con.size())
			{
				if (child + 1 < _con.size() && _com(_con[child], _con[child + 1]))
				{
					++child;
				}

				if (_com(_con[parent], _con[child]))
				{
					std::swap(_con[child], _con[parent]);
				}
				else
				{
					break;
				}

				parent = child;
				child = parent * 2 + 1;
			}
		}

		void push(const T& x)
		{
			_con.push_back(x);

			AdjustUp(_con.size() - 1);
		}

		void pop()
		{
			std::swap(_con[0], _con[_con.size() - 1]);

			_con.pop_back();
			AdjustDown(0);
		}

		const T& top() const 
		{
			return _con[0];
		}

		bool empty() const
		{
			return _con.empty();
		}

		size_t size() const
		{
			return _con.size();
		}

	private:
		Container _con;
		Compare _com;
	};
}