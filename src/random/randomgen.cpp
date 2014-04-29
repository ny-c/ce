#include <exception>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h> 

#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

#include "..\config.h"
#include "randomgen.h"

namespace Random {

	using namespace std;
	using namespace std::chrono;
	namespace po = boost::program_options;

	RandomGen::RandomGen(const string& config_file)
	:
		overflowed{ false },
		size{ 0 },
		index{ 0 },
		start_i{ 0 }
	{	
		string fname;

		po::options_description config("Configuration");
		config.add_options()
			("random.file", po::value< string >(&fname));

		string config_file_name = !config_file.empty() ? config_file.c_str() : Configuration::default_config_file_name.c_str();

		ifstream ifs(config_file_name);

		if(!ifs) {

			throw runtime_error((string("cannot open config file: ") + Configuration::default_config_file_name + "\n").c_str());
		}

		po::variables_map vm;
		po::store(po::parse_config_file(ifs, config, true), vm);
		po::notify(vm);

		loadRandomSet(fname);
		randomize();
	}
		
	void RandomGen::loadRandomSet(const string& fname)
	{
		static_assert(sizeof(uint16_t) == 2 * sizeof(char), "bad chars");

		ifstream ifs{ fname, std::ios::in | ios::binary };

		if(!ifs) {
			
			throw runtime_error((string("cannot open file: ") + fname + "\n").c_str());
		}

		ifs.seekg(0, std::ios::end);		
		size_t file_size = size_t(ifs.tellg());
		ifs.seekg(0, std::ios::beg);

		if(!file_size || file_size % 2) {

			throw runtime_error((string("random numbers file size must be positive and even: ") + fname + "\n").c_str());
		}		

		random_set = new uint16_t[file_size / 2];
		
		ifs.read((char *)random_set, file_size);

		if(!ifs.good()) {

			throw runtime_error((string("error reading file: ") + fname + "\n").c_str());
		}	

		size = file_size / 2;
	}

	void RandomGen::randomize()
	{		
		time_t now__second_precision = high_resolution_clock::to_time_t(high_resolution_clock::now());
		
		unsigned int current_mcs = (unsigned int)duration_cast<microseconds>
		(
			high_resolution_clock::now() - high_resolution_clock::from_time_t(now__second_precision)
		)
		.count();

		srand(current_mcs % UINT_MAX);
				
		index = start_i = size_t((double(rand()) / RAND_MAX)*(size - 1));
	}

	RandomGen::~RandomGen()
	{
		delete[] random_set;
	}		

	/*
	 algorithm from Ryan Reich http://stackoverflow.com/a/6852396
	*/
	int RandomGen::nextInt(int min, int max)
	{
		uint16_t base_random = nextInt();

		if(random_max == base_random) return nextInt(min, max);

		int range = max - min,
			remainder = random_max % range,
			bucket = random_max / range;

		if(base_random < (random_max - remainder)) {

			return min + base_random / bucket;
		}
		else {

			return nextInt(min, max);
		}
	}
} // namespace
