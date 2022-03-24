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


		//���Ӽ���
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

		//�����㷨��ʹ����ֵ����
		void reset() {
			for (auto& it : _bits) {
				it = (it >> 1) & 0x77777777;
			}
		}
	};

	class CountMinSketch {

	private:
		std::vector<CountMinRow> _cmRows;
		std::vector<uint64_t> _seed;	//���ڴ�ɢ��ϣֵ
		uint64_t _mask;					//��������ȡ��nλ

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


			//���õ�ǰʱ����Ϊgenerator��seed
			unsigned time = std::chrono::system_clock::now().time_since_epoch().count();
			std::mt19937_64 generator(time);
			for (int i = 0; i < depth; i++) {
				//�������һ��64λseed
				generator.discard(generator.state_size);
				_seed[i] = generator();
			}
		}

		//ѡ�񼸸�cmRow��С��һ����Ϊ��Чֵ����
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

		//Mrmurhash2 �㷨
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
		//���ڼ�����һ����ӽ�x�Ķ�����
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

