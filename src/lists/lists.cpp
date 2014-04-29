#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <cctype>
#include <algorithm>
#ifdef __GNUC__
#include <cstdlib>
#endif

#include "lists.h"
#include "tabdelim.h"

namespace Lists {

	using namespace std;
	
	list<Earthquake> getEarthquakes(const string& input_file, bool excl_unknown_t, bool skip_bad, const DBFieldNamesEarthquakes& dbf)
	{
		list<Earthquake> earthquakes;

		TabDelimitedFile td{ input_file };

		// query
		list<string> fnames;
		fnames.push_back(dbf.name);
		fnames.push_back(dbf.year);
		fnames.push_back(dbf.month);
		fnames.push_back(dbf.day);
		fnames.push_back(dbf.hours);
		fnames.push_back(dbf.minutes);
		fnames.push_back(dbf.seconds);
		fnames.push_back(dbf.deaths);

		list<list<string>> fields = td.get_fields(fnames);

		for(auto& a : fields) {

			vector<string> vec;
			copy(begin(a), end(a), back_inserter(vec));

			Earthquake q;

			/*
			parse name
			*/

			q.name = vec[0];

			/*
			parse date
			*/
						
			Date d; // Gregorian calendar by default.
					// All of the historical databases (earthquake, volcanic eruptions, tsunami)
					// in the NOAA Significant Earthquake Database use the Gregorian calendar.											

			try {

#ifdef __GNUC__
				d.setYear(strtol(vec[1].c_str(), 0, 10));
				d.setMonth(strtol(vec[2].c_str(), 0, 10));
				d.setDay(strtol(vec[3].c_str(), 0, 10));

				if((!d.year() && !vec[1].empty()) || !d.month() || !d.day()) continue;
#else
				d.setYear(stoi(vec[1]));
				d.setMonth(stoi(vec[2]));
				d.setDay(stoi(vec[3]));
#endif
			}
			catch(invalid_argument) {

				// month or day not specified: skip
				continue;
			}			

			/*
			parse time
			*/

			Time t;

			try {

#ifdef __GNUC__
				char *res1, *res2;
				
				int hour = strtol(vec[4].c_str(), &res1, 10); 
				int minute = strtol(vec[5].c_str(), &res2, 10);

				q.time_is_known = true;

				if(!vec[4].empty() && !*res1)
					t.setHour(hour);
				else
					q.time_is_known = false;

				if(!vec[5].empty() && !*res2)
					t.setMinute(minute);
				else
					q.time_is_known = false;

				if(excl_unknown_t && !q.time_is_known)
						continue;
#else				
				t.setHour(stoi(vec[4]));
				t.setMinute(stoi(vec[5]));
				q.time_is_known = true;
#endif		
			}
			catch(invalid_argument) {

				if(excl_unknown_t)
					continue;

				q.time_is_known = false;
			}

			try {

#ifdef __GNUC__
				t.setSecond(strtol(vec[6].c_str(), 0, 10));				
#else				
				t.setSecond(stoi(vec[6]));
#endif				
			}
			catch(invalid_argument) {

				// no seconds: ok
			}

			try {

				q.when = DateTime(d, t);
			}
			catch(runtime_error) {
				
				if(!skip_bad)
					throw;
			}

			/*
			 parse deaths
			*/

			try {

#ifdef __GNUC__
				q.deaths = strtol(vec[7].c_str(), 0, 10);
#else				
				q.deaths = stoi(vec[7]);
#endif
			}
			catch(invalid_argument) {

				q.deaths = 0;
			}

			earthquakes.push_back(q);
		}

		return earthquakes;
	}

} // namespace