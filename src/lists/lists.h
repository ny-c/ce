#ifndef LISTS_H
#define LISTS_H

#include "..\astro\astro.h"

namespace Lists {

	using namespace std;
	using namespace Astro;

	struct DBFieldNamesEarthquakes {

		string name;
		string year;
		string month;
		string day;
		string hours;
		string minutes;
		string seconds;
		string deaths;
	};
	
	struct Earthquake {

		string name;
		DateTime when;
		int deaths;
		bool time_is_known;
	};

	list<Earthquake> getEarthquakes(const string& input_file, bool excl_unknown_t, bool skip_bad, const DBFieldNamesEarthquakes& dbf);		

} // namespace

#endif // LISTS_H