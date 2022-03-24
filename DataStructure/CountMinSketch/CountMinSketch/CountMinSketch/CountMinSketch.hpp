#include <vector>
#include <random>
#include <chrono>

namespace lee {

	class CountMinRow {
	private:
		friend class CountMinSketch;
		std::vector<int> _bits;

	public:
		explicit CountMinRow(size_t countNum = 32) {
			if (countNum < 8) {
				countNum = 8;
			}

			int intSize = countNum / 8;
			_bits.resize(intSize, 0);
		}

	private:
		int get(int num) const {
			int countIndex = num / 8;
			int countOffset = num % 8 * 4;

			return (_bits[countIndex] >> countOffset) & 0x7;
		}


		//增加计数
		void increment(int num) {
			int countIndex = num / 8;
			int countOffset = num % 8 * 4;

			int value = (_bits[countIndex] >> countOffset) & 0x7;

			if (value < 15) {
				_bits[countIndex] += (1 << countOffset);
			}
		}

		void clear() {
			for (auto& it : _bits) {
				it = 0;
			}
		}

		//保鲜算法，使计数值减半
		void reset() {
			for (auto& it : _bits) {
				it = (it >> 1) & 0x77777777;
			}
		}
	};

	class CountMinSketch {

	private:
		std::vector<CountMinRow> _cmRows;
		std::vector<uint64_t> _seed;	//用于打散哈希值
		uint64_t _mask;					//掩码用于取低n位

	public:
		explicit CountMinSketch(size_t countNum = 32, size_t depth = 4)
			: _seed(4)
		{
			countNum = next2Power(countNum);
			if (countNum < 8) {
				countNum = 8;
			}
			_cmRows.resize(4, CountMinRow(countNum));
			_mask = countNum - 1;


			//利用当前时间作为generator的seed
			unsigned time = std::chrono::system_clock::now().time_since_epoch().count();
			std::mt19937_64 generator(time);
			for (int i = 0; i < depth; i++) {
				//随机生成一个64位seed
				generator.discard(generator.state_size);
				_seed[i] = generator();
			}
		}

		//选择几个cmRow最小的一个作为有效值返回
		int getCountMin(uint64_t hash) {
			int min = 16, value = 0;
			for (int i = 0; i < _cmRows.size(); i++) {
				value = _cmRows[i].get((hash ^ _seed[i]) & _mask);

				min = (value < min) ? value : min;
			}
			return min;
		}

		void Increment(uint64_t hash) {
			for (int i = 0; i < _cmRows.size(); i++) {
				_cmRows[i].increment((hash ^ _seed[i]) & _mask);
			}
		}

		void Reset() {
			for (auto& cmRow : _cmRows) {
				cmRow.reset();
			}
		}

		void Clear() {
			for (auto& cmRow : _cmRows) {
				cmRow.clear();
			}
		}

		//Mrmurhash2 算法
		static unsigned int murMurHash2(const void* key, int len)
		{
			const unsigned int m = 0x5bd1e995;
			const int r = 24;
			const int seed = 97;
			unsigned int h = seed ^ len;

			const unsigned char* data = (const unsigned char*)key;
			while (len >= 4)
			{
				unsigned int k = *(unsigned int*)data;
				k *= m;
				k ^= k >> r;
				k *= m;
				h *= m;
				h ^= k;
				data += 4;
				len -= 4;
			}

			switch (len)
			{
			case 3: h ^= data[2] << 16;
			case 2: h ^= data[1] << 8;
			case 1: h ^= data[0];
				h *= m;
			};

			h ^= h >> 13;
			h *= m;
			h ^= h >> 15;
			return h;
		}

	private:
		//用于计算下一个最接近x的二次幂
		int next2Power(int x) {
			x--;
			x |= x >> 1;
			x |= x >> 2;
			x |= x >> 4;
			x |= x >> 8;
			x |= x >> 16;
			x |= x >> 32;
			x++;
			return x;
		}
	};

};

