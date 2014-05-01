#include "main.h"

namespace po = boost::program_options;

void getProgramOptions(int argc, char *argv[], CheckearthqParameters *p);

int main(int argc, char *argv[])
{
	CheckearthqParameters p;
	
	p.iterations = -1;

	try {

		/*
		Parse command line options and config file
		*/
		getProgramOptions(argc, argv, &p);

		list<Earthquake> earthquakes{ getEarthquakes(p.input_file, p.excl_unknown, p.skip_bad, p.dbf) };

		for(auto e : earthquakes) {

			if(e.deaths >= p.min_deaths
				&& e.when.date().year() >= p.year_from
				&& e.when.date().year() <= p.year_to)
			{
				p.earthquakes.push_back(e.when);
			}
		}

		Random::RandomGen r(p.config_file);
		Ephemeris::SwissEphemeris se(p.ephemeris_path);
		Ephemeris::ephemeris = &se;

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

void getProgramOptions(int argc, char *argv[], CheckearthqParameters *p)
{
	po::options_description generic("Generic options");
	generic.add_options()
		("help,h", "produce help message")
		("config,c", po::value<string>(&p->config_file)->default_value(Configuration::default_config_file_name), "name of a configuration file");

	po::options_description query("Query");
	query.add_options()
		("checkearthq.year-from,f", po::value<int>(&p->year_from)->default_value(-600), "lower range of years to test")
		("checkearthq.year-to,t", po::value<int>(&p->year_to)->default_value(2100), "higher range of years to test")
		("checkearthq.deaths-min,d", po::value<int>(&p->min_deaths)->default_value(0), "death toll minimum value")
		("checkearthq.with-time,e", "skip earthquakes without time")
		("checkearthq.skip-bad-dates,s", "skip incorrect dates and times silently");

	po::options_description test("Test");
	test.add_options()
		// default value "316" corresponds to [09°30'00" – 10°26'15"] of Virgo
		("checkearthq.segment,g", po::value<string>(&p->s_checked_pos)->default_value("316"), "ecliptic segment to test ('[gate].[line]')")
		("checkearthq.iterations,n", po::value<int>(&p->iterations)->default_value(1000), "number of iterations")
		("checkearthq.range,r", po::value<int>(&p->range)->default_value(15), "random dates fork");

	po::options_description config_only("Configuration");
	config_only.add_options()
		("ephemeris.path", po::value< string >(&p->ephemeris_path)->default_value("swe_files"))
		("checkearthq.input-file", po::value< string >(&p->input_file))
		("checkearthq.db-field.name", po::value< string >(&p->dbf.name))
		("checkearthq.db-field.year", po::value< string >(&p->dbf.year))
		("checkearthq.db-field.month", po::value< string >(&p->dbf.month))
		("checkearthq.db-field.day", po::value< string >(&p->dbf.day))
		("checkearthq.db-field.hours", po::value< string >(&p->dbf.hours))
		("checkearthq.db-field.minutes", po::value< string >(&p->dbf.minutes))
		("checkearthq.db-field.seconds", po::value< string >(&p->dbf.seconds))
		("checkearthq.db-field.deaths", po::value< string >(&p->dbf.deaths));

	po::options_description cmdline_options;
	cmdline_options.add(generic).add(query).add(test);

	po::options_description config_file_options;
	config_file_options.add(query).add(config_only);

	po::options_description visible("Allowed options");
	visible.add(generic).add(query).add(test);

	po::variables_map vm;
	store(po::command_line_parser(argc, argv).
		options(cmdline_options).run(), vm);
	notify(vm);

	if(vm.count("help")) {

		cout << visible << "\n";
		exit(1);
	}

	p->excl_unknown = vm.count("checkearthq.with-time") ? true : false;
	p->skip_bad = vm.count("checkearthq.skip-bad-dates") ? true : false;

	ifstream ifs(p->config_file.c_str());

	if(!ifs) {

		throw runtime_error{ (string("cannot open config file: ") + p->config_file).c_str() };
	}

	store(parse_config_file(ifs, config_file_options, true), vm);
	notify(vm);

	parse_checked_pos(p->s_checked_pos, &p->checked_pos);
}

void parse_checked_pos(const string& s_checked_pos, int *cp)
{
	const char* msg = "Position should be from 1 to 384\n";
	istringstream iss{ s_checked_pos };

	try {

#ifdef __GNUC__			
		char *res;
		*cp = strtol(s_checked_pos.c_str(), &res, 10);

		if(s_checked_pos.empty() || *res) {

			throw runtime_error{ msg };
		}
#else				
		*cp = stoi(s_checked_pos);
#endif	
	}
	catch(invalid_argument)
	{
		throw runtime_error{ msg };
	}

	if(*cp < 1 || *cp > 384)
		throw runtime_error{ msg };
}