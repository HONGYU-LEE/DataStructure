#pragma once
#include<vector>

namespace lee
{
	class bitset
	{
	public:

		//每一个位标识一个数据，一个整型4个字节，可存储32个位, 所以需要/32（或者右移五位）。+1是为了取整
		bitset(size_t size = 32) 
			: _bits((size >> 5) + 1, 0)
			, _size(0)
		{}

		//数据的对应标识位置1
		void set(size_t x)
		{
			//计算出在数组中哪一个整型中
			size_t index = x >> 5;
			//计算出在该整型的哪一个位上
			size_t pos = x % 32;

			//对应位置 置1
			_bits[index] |= (1 << pos);
			++_size;
		}

		//数据的对应标识位置0
		void reset(size_t x)
		{
			size_t index = x >> 5;
			size_t pos = x % 32;

			//对应位置数据置零
			_bits[index] &= ~(1 << pos);
			++_size;
		}
		
		//判断数据是否存在
		bool test(size_t x) const
		{
			size_t index = x >> 5;
			size_t pos = x % 32;

			return _bits[index] & (1 << pos);
		}

		size_t size() const
		{
			return _size;
		}

	private:
		std::vector<int> _bits;
		size_t _size;
	};
};