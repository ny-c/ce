#include "main.h"

namespace po = boost::program_options;

void getProgramOptions(int argc, char *argv[], CheckdiceParameters *p);

int main(int argc, char *argv[])
{
	CheckdiceParameters p;
	
	p.iterations = -1;

	try {

		/*
		Parse command line options and config file
		*/
		getProgramOptions(argc, argv, &p);
		
		Random::RandomGen r(p.config_file);
		performMainTest(p, &r);

		return 0;
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

void getProgramOptions(int argc, char *argv[], CheckdiceParameters *p)
{
	po::options_description generic("Generic options");
	generic.add_options()
		("help,h", "produce help message")
		("config,c", po::value<string>(&p->config_file)->default_value(Configuration::default_config_file_name), "name of a configuration file");

	po::options_description options("Options");
	options.add_options()
		("checkdice.dice-n,n", po::value<int>(&p->n)->default_value(2), "number of dices")
		("checkdice.iterations,p", po::value<int>(&p->iterations)->default_value(1000), "number of iterations");

	po::options_description cmdline_options;
	cmdline_options.add(generic).add(options);

	po::options_description visible("Allowed options");
	visible.add(generic).add(options);

	po::variables_map vm;
	store(po::command_line_parser(argc, argv).
		options(cmdline_options).run(), vm);
	notify(vm);

	if(vm.count("help")) {

		cout << visible << "\n";
		exit(1);
	}
	
	ifstream ifs(p->config_file.c_str());

	if(!ifs) {

		throw runtime_error{ (string("cannot open config file: ") + p->config_file).c_str() };
	}	
}