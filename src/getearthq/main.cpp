#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

#include "..\config.h"

using namespace std;
namespace po = boost::program_options;

struct GetearthqParameters {

	int year_from;
	int year_to;	
	string output_file;
};

const string url_host = "www.ngdc.noaa.gov";

// '%1' and '%2' will be replaced
const string url_path =	"/nndc/struts/results?bt_0=%1&st_0=%2&type_17=EXACT&query_17=None+Selected&op_12=eq&type_12=Or&query_14=None+Selected&type_3=Like&type_11=Exact&type_16=Exact&display_look=189&t=101650&s=1&submit_all=Search+Database";

int go(const GetearthqParameters& p);
int get_page(const string& url, const string& path, string *page);

int main(int argc, char *argv[])
{	
	GetearthqParameters p;

	try {

		/*
		 Parse command line options and config file
		*/

		string config_file;

		po::options_description generic("Generic options");
		generic.add_options()
			("help,h", "produce help message")
			("config,c", po::value<string>(&config_file)->default_value(Configuration::default_config_file_name), "name of a configuration file");

		po::options_description config("Configuration");
		config.add_options()
			("getearthq.year-from,f", po::value<int>(&p.year_from)->default_value(-600), "low range years to get")
			("getearthq.year-to,t", po::value<int>(&p.year_to)->default_value(2100), "high range years to get")
			("getearthq.output-file,o", po::value< string >(&p.output_file), "print to specified output file");
		
		po::options_description cmdline_options;
		cmdline_options.add(generic).add(config);

		po::options_description config_file_options;
		config_file_options.add(config);

		po::options_description visible("Allowed options");
		visible.add(generic).add(config);

		po::variables_map vm;
		store(po::command_line_parser(argc, argv).
			options(cmdline_options).run(), vm);
		notify(vm);

		if(vm.count("help")) {

			cout << visible << "\n";
			return 1;
		}

		ifstream ifs(config_file.c_str());

		if(!ifs) {

			cerr << "cannot open config file: " << config_file << "\n";
			return 1;
		}
		
		store(parse_config_file(ifs, config_file_options, true), vm);
		notify(vm);

		return go(p);
	}
	catch(const exception& e)
	{
		cerr << e.what() << "\n";
	}
	catch(...) {

		cerr << "unknown error\n";
	}	
	
	return  1;
}

int go(const GetearthqParameters& p)
{	
	string result;
	
	string path{ url_path };

#if __GNUC__
	{
		ostringstream oss;
		oss << p.year_from;
		path.replace(path.find("%1"), 2, oss.str());
		oss.clear();
		oss << p.year_to;
		path.replace(path.find("%2"), 2, oss.str());
	}
#else
	path.replace(path.find("%1"), 2, ::to_string(p.year_from));
	path.replace(path.find("%2"), 2, ::to_string(p.year_to));
#endif
	
	get_page(url_host, path, &result);

	if(result.empty()) {

		cerr << "nothing was read\n";
		return 1;
	}

	if(p.output_file.empty()) {

		cout << result;
	}
	else {

		ofstream ofs(p.output_file, ios_base::binary );

		if(!ofs) {

			cerr << "couldn't open '" << p.output_file << "' for writing";
			return 1;
		}
		
		ofs << result;		
	}

	return 0;
}