#include<vector>
#include<deque>

namespace lee
{
	/*
		STL底层中的容器选择的是deque，因为deque是假想的连续空间，他每次插入时扩容都会直接在插入的地方直接插入一片固定大小的空间，
		这样就保证了逻辑上的线性，不需要拷贝数据。而vector每次扩容，都需要创建新空间，拷贝原数据，销毁原空间，并且开的空间是原数据的1.5倍或2倍（不同版本）
		vector不仅效率不比deque高，空间的利用率也不高，多次扩容会导致空间的碎片化

	*/
	template<class T, class Container = std::deque<T>>
	class stack
	{
	public:
		void push(const T& val)
		{
			_con.push_back(val);
		}

		void pop()
		{
			_con.pop_back();
		}

		T& top() 
		{
			return _con.back();
		}

		const T& top() const
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
