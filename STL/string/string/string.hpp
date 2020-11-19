#pragma once
#include<iostream>
#include<cstring>
#include<cassert>


namespace lee
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		friend std::ostream& operator<<(std::ostream& _cout, const string& s);
		friend std::istream& operator>>(std::istream& _cin, string& s);

		//构造函数
		string(const char* str = "")
			: _size(strlen(str))
			, _capacity(_size)
			, _str(new char[_size + 1])
		{
			strcpy(_str, str);
		}

		/*
		//拷贝构造函数
		//传统写法开空间拷数据
		string(const string& s)
			: _size(s._size)
			, _capacity(s._capacity)
			, _str(new char[_size + 1])
		{
			strcpy(_str, s._str);
		}
		*/

		//现代写法，直接构造一个临时对象，然后和那个临时对象进行交换，交换过去的数据在函数结束便销毁
		string(const string& s)
			: _size(0)
			, _capacity(0)
			, _str(nullptr)
		{
			string temp(s._str);
			std::cout << "拷贝构造" << std::endl;
			swap(temp);
		}

		string(string&& s)
			: _size(s._size)
			, _capacity(s._capacity)
			, _str(nullptr)
		{
			std::cout << "移动构造" << std::endl;
			std::swap(_str, s._str);
		}
		
		//传统写法,开空间拷贝数据
		string& operator=(const string& s)
		{
			//相同则不交换
			if (this != &s)
			{
				char* str = new char[strlen(s._str) + 1];
				strcpy(str, s._str);
				delete[] _str;

				_str = str;

			}
			std::cout << "赋值" << std::endl;
			return *this;
		}
		

		////现代写法,直接用构造函数构建然后交换
		//string& operator=(const string& s)
		//{
		//	string temp(s);
		//	swap(temp);

		//	std::cout << "赋值" << std::endl;
		//	return *this;
		//}

		string& operator=(string&& s)
		{
			_size = s._size;
			_capacity = s._capacity;
			std::swap(_str, s._str);
			std::cout << "移动赋值" << std::endl;
			return *this;
		}

		//析构函数
		~string()
		{
			_size = _capacity = 0;
			delete[] _str;
			_str = nullptr;
		}

		/*
			------------------------------------------------------------
			容量部分
			Capacity
			------------------------------------------------------------
		*/

		//返回capacity
		size_t capacity() const
		{
			return _capacity;
		}

		//返回size
		size_t size() const
		{
			return _size;
		}

		//如果为空返回true,不为空返回false
		bool empty() const
		{
			return !_size;
		}

		//重新分配size
		void resize(size_t newSize, char c = '\0')
		{
			//如果size不够，扩容
			if (_size < newSize)
			{
				//如果capacity不够，调用reserve扩容
				if (_capacity < newSize)
				{
					reserve(newSize);
				}

				//将多出的空间全部初始化为c
				memset(_str + _size, c, newSize - _size);
			}

			//当空间够的时候，直接截断数据
			_size = newSize;
			_str[_size] = '\0';
		}

		//重新分配capacity
		void reserve(size_t newCapacity)
		{
			if (_capacity >= newCapacity)
				return;


			char* str = new char[newCapacity + 1];
			strcpy(str, _str);
			delete[] _str;

			_str = str;
			_capacity = newCapacity;
		}

		/*
			------------------------------------------------------------
			迭代器部分
			Iterators:
			------------------------------------------------------------
		*/

		//首部迭代器啊
		iterator begin()
		{
			return _str;
		}

		//尾部迭代器
		iterator end()
		{
			return _str + _size;
		}

		//首部常量迭代器
		const_iterator cbegin() const
		{
			return _str;
		}

		//尾部常量迭代器
		const_iterator cend() const
		{
			return _str + _size;
		}

		/*
			------------------------------------------------------------
			修改部分
			Modifiers:
			------------------------------------------------------------
		*/

		//在某个位置后插入字符
		string& insert(size_t pos, char c)
		{
			assert(pos < _size);

			if (_capacity == _size)
			{
				size_t newcapacity = (_capacity == 0) ? 2 : 2 * _capacity;

				reserve(newcapacity);
			}

			//数据后移
			for (size_t i = _size; i > pos; i--)
			{
				_str[i] = _str[i - 1];
			}


			_str[pos] = c;
			_str[++_size] = '\0';

			return *this;
		}

		//在某个位置后插入字符串
		string& insert(size_t pos, const char* str)
		{
			assert(pos < _size);
			size_t size = strlen(str);

			//检查容量，不够就扩容
			if (size + _size > _capacity)
			{
				reserve(size + _size);
			}

			//数据后移size个位置
			for (size_t i = _size + size - 1; i > pos + size - 1; i--)
			{
				_str[i] = _str[i - size];
			}

			//拷贝数据到第pos个位置
			memcpy(_str + pos, str, size);
			_size += size;
			_str[_size] = '\0';

			return *this;
		}

		// 删除pos位置上的元素，并返回该元素的下一个位置
		string& erase(size_t pos, size_t len = npos)
		{
			//如果那个位置后面没有那么多数据，就直接从那个位置截断，删除后面所有数据
			if (len >= _size - pos)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				//从数据删除后前移pos个位置
				for (size_t i = pos + len; i <= _size; i++)
				{
					_str[i - len] = _str[i];
				}
			}

			//重新设置size和结尾的\0
			_size -= len;
			_str[_size] = '\0';
			return *this;
		}
		//尾插

		void push_back(char c)
		{
			if (_capacity == _size)
			{
				size_t newcapacity = (_capacity == 0) ? 2 : 2 * _capacity;

				reserve(newcapacity);
			}

			_str[_size++] = c;
			_str[_size] = '\0';
		}

		//尾删
		void pop_back()
		{
			_str[--_size] = '\0';
		}
		string operator+(const string& s2)
		{
			string ret(*this);

			return ret;  
		}
		//追加字符
		string& operator+=(char c)
		{
			push_back(c);

			return *this;
		}

		//尾部追加字符串
		void append(const char* str)
		{
			size_t size = strlen(str);

			//检查容量，不够就扩容
			if (size + _size > _capacity)
			{
				reserve(size + _size);
			}

			//尾部追加字符串
			strcpy(_str + _size, str);
			_size += size;
		}

		//追加字符串
		string& operator+=(const char* str)
		{
			append(str);

			return *this;
		}

		//清空string
		void clear()
		{
			_size = 0;
			_str[_size] = '\0';
		}

		//交换string
		void swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}



		/*
			------------------------------------------------------------
			元素访问部分
			Element access:
			------------------------------------------------------------
		*/

		char& operator[](size_t index)
		{
			assert(index < _size);
			return _str[index];
		}
		const char& operator[](size_t index) const
		{
			assert(index < _size);
			return _str[index];
		}

		/*
			------------------------------------------------------------
			关系运算符
			relational operators:
			------------------------------------------------------------
		*/
		bool operator<(const string& s)
		{
			if (strcmp(_str, s._str) == -1)
				return true;
			else
				return false;
		}

		bool operator<=(const string& s)
		{
			return (*this < s) || (*this == s);
		}

		bool operator>(const string& s)
		{
			return !(*this <= s);
		}

		bool operator>=(const string& s)
		{
			return !(*this < s);
		}

		bool operator==(const string& s)
		{
			if (strcmp(_str, s._str) == 0)
				return true;
			else
				return false;
		}

		bool operator!=(const string& s)
		{
			return !(*this == s);
		}

		/*
		------------------------------------------------------------
		字符串操作
		String operations:
		------------------------------------------------------------
		*/
		//返回C风格的字符串
		const char* c_str() const
		{
			return _str;
		}

		//查找字符c第一次出现的位置
		size_t find(char c, size_t pos = 0) const
		{
			assert(pos < _size);
			size_t i = pos;

			while (i < _size)
			{
				if (_str[i] == c)
					return i;

				i++;
			}

			return npos;
		}

		// 返回子串s在string中第一次出现的位置
		size_t find(const char* s, size_t pos = 0) const
		{
			const char* src = _str;
			const char* sub = s;

			while (*src)
			{
				//如果两个位置匹配则继续遍历
				while (*src == *sub && *sub)
				{
					src++;
					sub++;
				}
				//如果sub走完就说明完全匹配，返回sub第一次出现的位置
				if ('\0' == *sub)
				{
					return (src - _str - strlen(s));
				}
				//不匹配则回溯，继续匹配下一个位置
				else
				{
					sub = sub;
					src = ++src;
				}
			}

			return npos;
		}


	private:
		size_t _size;
		size_t _capacity;
		char* _str;
		static size_t npos;
	};

	size_t string::npos = -1;

	std::ostream& operator<<(std::ostream& out, const string& s)
	{
		out << s._str;
		return out;
	}

	std::istream& operator>>(std::istream& in, string& s)
	{
		//直接用cin输入进str会有无法扩容的问题，需要手动扩容
		while (1)
		{
			char ch;
			ch = in.get();
			//遇到分隔符则暂停
			if (ch == '\n' || ch == ' ')
			{
				break;
			}
			else
			{
				s.push_back(ch);
			}
		}
		
		return in;
	}
}

