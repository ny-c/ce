#include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>
#include <exception>
#include <sstream>
#include "tabdelim.h"

using namespace std;

list<string> getFields(string str)
{
	list<string> ret;

	istringstream iss{ str };

	string fld;

	while(getline(iss, fld, '\t'))
		ret.push_back(fld);

	return ret;
}

TabDelimitedFile::TabDelimitedFile(const string& fname)
{
	ifstream ifs{ fname };

	if(!ifs) {

		throw runtime_error{ (string("unable to open ") + fname + '\n').c_str() };
	}

	string line;
	
	while(getline(ifs, line)) {

		if(line.size() > 1) {
			
			if(line.back() == '\r')
				line.pop_back();

			list<string> fields = getFields(line);

			if(line.back() == '\t')
				// last field is empty
				fields.push_back(string{});
	
			all_fields.push_back(fields);
		}
	}

	list<string> hlist = all_fields.front();
	copy(begin(hlist), end(hlist), back_inserter(headers));
	
	all_fields.pop_front();

	auto f = [&](const list<string>& ls) { return ls.size() != headers.size(); };

	if(all_fields.end() != find_if(all_fields.begin(), all_fields.end(), f)) {
		
		throw runtime_error{ (string("unable to parse ") + fname + '\n').c_str() };
	}
}

list<list<string>> TabDelimitedFile::get_fields(const list<string>& fields)
{
	auto f = [&](const string& s)
	{
		return find(begin(headers), end(headers), s) == headers.end();
	};
	
	auto r = find_if(fields.begin(), fields.end(), f);	

	if(r != fields.end()) {		

		throw runtime_error{ (string("no such field: ") + *r + '\n').c_str() };
	}

	list<list<string>> ret;

	for(auto& a : all_fields) {

		list<string> vals;
		
		for(auto& f : fields) {

			int index = 0;

			for(auto b : a) {				

				if(headers[index] == f) {

					vals.push_back(b);
					break;
				}

				index++;
			}			
		}

		ret.push_back(vals);
	}

	return ret;
}