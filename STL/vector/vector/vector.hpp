#pragma once
#include<cassert>

namespace lee
{
	//类模板
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		/*
		------------------------------------------------------------
		默认成员函数部分
		Member functions
		------------------------------------------------------------
		*/
		vector()
			: _start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{}

		vector(int n, const T& value = T())
		{
			assert(n > 0);

			//直接用resize就可以，功能一样
			resize(n, value);
		}



		vector(const_iterator first, const_iterator last)
			: _start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
			reserve(last - first);

			//深拷贝
			while (first != last)
			{
				*_finish++ = *first++;
			}

			_endOfStorage = _finish;
		}

		vector(const vector<T>& v)
			: _start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
			/*
			直接构建一个然后交换
			vector temp(v.begin(), v.end());
			swap(temp);
			*/

			reserve(v.capacity());

			for (const auto& i : v)
			{
				push_back(i);
			}
		}

		vector<T>& operator=(vector<T> v)
		{
			//直接和形参交换，交换过去的数据也会在栈帧销毁时清除。
			swap(v);

			return *this;
		}


		~vector()
		{
			delete[] _start;
			_start = _finish = _endOfStorage = nullptr;
		}

		/*
		------------------------------------------------------------
		迭代器部分
		Iterators:
		------------------------------------------------------------
		*/
		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator begin() const
		{
			return _start;
		}

		const_iterator end() const
		{
			return _finish;
		}

		/*
			------------------------------------------------------------
			容量部分
			Capacity
			------------------------------------------------------------
		*/

		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _endOfStorage - _start;
		}

		void reserve(size_t n)
		{
			//容量没增大则不操作
			if (n <= capacity())
				return;

			//后面会修改到_finish和_start，所以后面无法调用size（）
			size_t length = size();
			T* temp = new T[n];

			//判断_start是否为空，防止释放空指针
			if (_start)
			{
				//深拷贝，这里不能像string一样使用strcpy或者memcpy，因为这两个都是按照字节拷贝
				//还有一个原因，就是对于某些容器如string，memcpy拷贝时会直接浅拷贝_str,就会出现问题，而如果使用赋值则会自动调用对应类型的重载赋值运算符
				for (size_t i = 0; i < length; i++)
				{
					temp[i] = _start[i];
				}

				delete[] _start;
			}

			_start = temp;
			_finish = _start + length;
			_endOfStorage = _start + n;
		}


		//value为该类型的缺省值
		void resize(size_t n, const T& value = T())
		{
			//如果原来的大则初始化后面的数据
			if (size() < n)
			{
				//如果容量不够则扩容
				if (capacity() < n)
				{
					reserve(n);
				}

				//将多出来的部分初始化为value
				while (_finish < _start + n)
				{
					*_finish++ = value;
				}
			}
			//如果容量比原来的小，则直接从对应位置截断数据
			else
			{
				_finish = _start + n;
			}
		}

		bool empty() const
		{
			return _start == _finish;
		}
		/*
		------------------------------------------------------------
		元素访问部分
		Element access:
		------------------------------------------------------------
		*/

		T& operator[](size_t pos)
		{
			assert(pos < size());

			return _start[pos];
		}

		const T& operator[](size_t pos) const
		{
			assert(pos < size());

			return _start[pos];
		}

		/*
			------------------------------------------------------------
			修改部分
			Modifiers:
			------------------------------------------------------------
		*/

		void push_back(const T& x)
		{
			//容量满了则扩容
			if (_finish == _endOfStorage)
			{
				size_t newCapacity = capacity() == 0 ? 2 : 2 * capacity();
				reserve(newCapacity);
			}

			*_finish++ = x;
		}

		void pop_back()
		{
			
			assert(_start < _finish);

			_finish--;
		}

		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endOfStorage, v._endOfStorage);
		}

		iterator insert(iterator pos, const T& x)
		{
			assert(pos <= _finish);

			//空间满了则扩容
			if (_finish == _endOfStorage)
			{
				size_t newCapacity = capacity() == 0 ? 2 : 2 * capacity();
				reserve(newCapacity);
			}

			//数据后移
			for (auto i = _finish; i >= pos; i--)
			{
				*i = *(i - 1);
			}

			//插入数据，并且结束位置后移
			*pos = x;
			_finish++;

			return pos;
		}

		iterator erase(iterator pos)
		{
			assert(pos <= _finish);

			//数据前移
			for (auto i = pos; i <= _finish; i++)
			{
				*i = *(i + 1);
			}

			_finish--;
			return pos;
		}

		void clear()
		{
			_finish = _start;
		}

	private:
		iterator _start; // 指向数据的开始
		iterator _finish; // 指向数据的结束
		iterator _endOfStorage; // 指向存储容量的尾
	};
}