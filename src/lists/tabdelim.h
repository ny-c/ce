#ifndef TABDELIM_H_INCLUDED
#define TABDELIM_H_INCLUDED

#include <string>
#include <list>
#include <vector>
#include <utility>

using namespace std;

class TabDelimitedFile {

public:

	TabDelimitedFile(const std::string& fname);
	list<list<string>> get_fields(const list<string>& fields);

private:
		
	vector<string> headers;
	list<list<string>> all_fields;
};

#endif // TABDELIM_H_INCLUDED