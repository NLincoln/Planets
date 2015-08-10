//
//
//
//
//
#include "Main.h"
#include "Util.h"

std::vector<std::string> ParseStringIntoArray(std::string string, char pch)
{
	std::string t;
	std::vector<std::string> out;
	for (uint i = 0; i < string.size(); ++i)
	{
		if (string[i] == pch)
		{
			out.push_back(t);
			t.erase();
			continue;
		}
		if (i == string.size()) // end of string
		{
			out.push_back(t);
			t.erase();
			continue;
		}
		t.push_back(string[i]);

	}
	return out;
}

