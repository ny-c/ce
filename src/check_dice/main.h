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
#include "..\random\randomgen.h"
#include "..\random\tester.h"

using namespace std;

struct CheckdiceParameters {

	string config_file;	
	int iterations;
	int n;
};

void performMainTest(const CheckdiceParameters& p, Random::RandomGen *r);
void printResult(const CheckdiceParameters& p, int result);

#endif // MAIN_H_INCLUDED