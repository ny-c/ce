#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <exception>
#include <list>
#include <fstream>
#include <istream>

#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

#include "..\config.h"
#include "..\astro\astro.h"
#include "..\random\randomgen.h"
#include "..\random\tester.h"
#include "..\lists\lists.h"

using namespace std;
using namespace Astro;
using namespace Lists;

struct CheckearthqParameters {

	string config_file;
	string ephemeris_path;
	int year_from;
	int year_to;
	int min_deaths;
	string s_checked_pos;
	int checked_pos;
	int iterations;
	int range;
	string input_file;
	bool excl_unknown;
	bool skip_bad;

	list<DateTime> earthquakes;
	DBFieldNamesEarthquakes dbf;
};

void performMainTest(const CheckearthqParameters& p, Random::RandomGen *r);
void parse_checked_pos(const string& s_checked_pos, int *cp);

void printDesription(const CheckearthqParameters& p, int n, int standard);
void printResult(const CheckearthqParameters& p, int standard, int result);
void printPassedTime(const string& message, int secs);

#endif // MAIN_H_INCLUDED