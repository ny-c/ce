#ifndef RANDOMGEN_H_INCLUDED
#define RANDOMGEN_H_INCLUDED

#include <cstdint>
#include <string>
#include <limits>

namespace Random {

	const uint16_t random_max = UINT16_MAX;
	
	class RandomGen {
		
	public:
		RandomGen(const std::string& config_file = std::string{});
		~RandomGen();
		
		int nextInt(int min, int max);

		inline bool isOverflowed() const { return overflowed; }

	private:
		
		bool overflowed;
		uint16_t *random_set;
		size_t index, size, start_i;		
		void loadRandomSet(const std::string& fname);
		void randomize();

		inline void incrementIndex()
		{
			++index;

			if(index == start_i) {

				overflowed = true;
			}

			if(index >= size) {

				index = 0;		
			}
		}

		inline uint16_t nextInt()
		{
			uint16_t val = random_set[index];

			incrementIndex();

			return val;
		}
	}; // class RandomGen
} // namespace

#endif // RANDOMGEN_H_INCLUDED
