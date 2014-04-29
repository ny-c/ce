#include <iostream>
#include <sstream>
#include <chrono>
#include "main.h"

using namespace std;
using namespace Astro::Ephemeris;
using namespace std::chrono;

// Use the ecliptic division on the 384 parts starting from 13 deg 15' 00" of Scorpio or 223.25
Ecliptic::Divider<384> div_(223.25);
	
int checked_pos;	
		
inline bool check(double j, body b)
{		
	double pos = ephemeris->pos(b, j);		
				
	return checked_pos == div_.pos(pos);
}

bool check_earthquake(double julian_day)
{
	return check(julian_day, body::sun)
		|| check(julian_day, body::mars)
		|| check(julian_day, body::jupiter)
		|| check(julian_day, body::venus);
}	

void performMainTest(const CheckearthqParameters& p, Random::RandomGen *r)
{			
	checked_pos = p.checked_pos;

	int standard = 0;
	for(auto a : p.earthquakes)
		if(check_earthquake(a.julian_day()))
			standard++;

	if(!standard) {

		cout << "No such earthquakes in your group (" << p.earthquakes.size() << " earthquakes).\n";
		return;
	}

	printDesription(p, p.earthquakes.size(), standard);

	Random::Tester rt(r, p.earthquakes, &check_earthquake);

	// print possible running time
	{
		auto t = system_clock::now();

		ostringstream oss{};

		rt.performTest(1, standard, p.range, oss);

		auto t1 = system_clock::now() - t;

		int t2 = int(duration_cast<seconds>(p.iterations*t1).count());

		printPassedTime("Estimated time: ", t2);
	}

	auto t = system_clock::now();

	int result = rt.performTest(p.iterations, standard, p.range, cout);

	cout << endl;

	printDesription(p, p.earthquakes.size(), standard);
	printResult(p, standard, result);

	{
		int t2 = int(duration_cast<seconds>(system_clock::now() - t).count());

		printPassedTime("\nElapsed time: ", t2);
	}
}

void printDesription(const CheckearthqParameters& p, int n, int standard)
{
	cout << "Year range: " << p.year_from << " - " << p.year_to << endl;
	cout << "Death toll: " << p.min_deaths;

	cout << endl << endl;

	cout << "Number of earthquakes in your group: " << n << endl;
	cout << "Standard: " << standard << endl << endl;
}

void printResult(const CheckearthqParameters& p, int standard, int result)
{
	cout << "Result:\n\n";

	cout << "Number of groups among " << p.iterations << " random groups with\n"
		<< "Sun/Jupiper/Mars/Venus in " << p.checked_pos << " >= standard (" << standard << "): "
		<< result << endl;
}

void printPassedTime(const string& message, int secs)
{
	cout.precision(1);
	cout << message << fixed << secs / 60. << " min.\n\n";
}