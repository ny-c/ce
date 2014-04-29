#include <exception>
#include <vector>
#include <list>
#include <future>
#include <forward_list>
#include <string>
#include <cassert>
#include "tester.h"

namespace Random {

	using namespace std;

	Tester::Tester(Random::RandomGen* random_gen, const std::list<DateTime>& dt, bool(*test_function)(double julian_day), bool shuffle_times)
		:
		rg{ random_gen },
		test_f{ test_function },
		shuffle_times{ shuffle_times }
	{
		assert(rg != nullptr);		

		size = dt.size();
		
		dates.resize(size);
		times.resize(size);
				
		int i = 0;

		for(const auto& a : dt) {

			dates[i] = a.date();
			times[i] = a.time();
			++i;
		}
	}
	
	int Tester::performTest(int iterations, int standard, int range, ostream& os)
	{
		current_range = range;

		int count = 0;

		double avg = 0;

		for(int i = 0; i < iterations; ++i) {

			int r = countValue(shuffle_times ? shuffleTimes() : times);

			avg += r;

			os << i + 1 << " : " << r << endl;

			if(standard <= r)
				count++;
		}

		os << "\nRandom average: " << avg / iterations << endl;

		return count;
	}

	vector<Time> Tester::shuffleTimes()
	{			
		vector<Time> shuffled;
		vector<int> indexes;
				
		shuffled.resize(size);
		indexes.resize(size);

		for(int i = 0; i < size; ++i)
			indexes[i] = i;

		for(int i = 0; i < size; ++i) {

			int r = rg->nextInt(0, int(indexes.size()));			

			int time_index = indexes[r];
			indexes.erase(indexes.begin() + r);

			shuffled[i] = times[time_index];
		}

		return shuffled;
	}

	int Tester::countValue(const vector<Time>& shuffled_times)
	{
		int count = 0;	

		const int two_ranges = 2 * current_range;
		const int n_range = -1 * current_range;
		
		for(int i = 0; i < size; ++i) {

			double jd = Astro::Utilities::to_julian_day(dates[i], shuffled_times[i]);
			
			jd += n_range + rg->nextInt(0, two_ranges + 1);
			
			if((*test_f)(jd)) count++;
		}

		return count;
	}

} // namespace