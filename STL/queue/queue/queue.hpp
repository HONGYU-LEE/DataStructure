#include<deque>
#include<list>

namespace lee
{
	/*
	STL中queue底层的容器是deque，因为deque和list一样插入删除的效率都是O（1），并且deque的效率更高，因为list是一次创建一个结点后插入，并且这些空间是离散分布的.
	deque是每次创建一个固定大小的空间，并在这块空间上面进行插入删除，这样的效率更高，并且因为申请的空间都是一段一段的连续空间，内存的利用率更高
	*/
	template<class T, class Container = std::deque<T>>
	class queue
	{
	public:
		void push(const T& val)
		{
			_con.push_back(val);
		}

		void pop()
		{
			_con.pop_front();
		}

		T& front()
		{
			return _con.front();
		}

		const T& front() const
		{
			return _con.front();
		}

		T& back()
		{
			return _con.back();
		}

		const T& back() const
		{
			return _con.back();
		}

		size_t size() const
		{
			return _con.size();
		}

		bool empty() const
		{
			return _con.empty();
		}

	private:
		Container _con;
	};
}
