#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

class phoneme_dictionary {
map<string, vector< string > > dictionary;

public:
	phoneme_dictionary() {}

	void read_file(string filepath);

	vector<string> get_entry(string entry);

	string get_entry_string(string entry);

	bool is_rhyme(string s1, string s2);

	int num_syllables(string entry);
};