#ifndef TESTER_H_INCLUDED
#define TESTER_H_INCLUDED

#include <iostream>
#include <list>
#include <vector>
#include "..\astro\types.h"
#include "..\astro\utilities.h"
#include "randomgen.h"

namespace Random {

	using namespace Astro;

	class Tester {

	public:
		Tester(Random::RandomGen* random_gen, const std::list<DateTime>& dt, bool(*test_function)(double julian_day), bool shuffle_times = false);		
		
		int performTest(int iterations, int standard, int rangeint, ostream& os);

	private:

		vector<Date> dates;
		vector<Time> times;
		int size;

		Random::RandomGen* rg;
		bool(*test_f)(double julian_day);

		int current_range;

		bool shuffle_times;

		vector<Time> shuffleTimes();
		int countValue(const vector<Time>& shuffled_times);		
	};
} // namespace

#endif // TESTER_H_INCLUDED