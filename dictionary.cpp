#include "dictionary.hpp"

void phoneme_dictionary::read_file(string filepath) {

	string line;
	ifstream myfile (filepath);

	while(getline (myfile, line)) {

		if(line[0] == ';') { continue; }
		istringstream buf(line);
		istream_iterator<string> beg(buf), end;

		vector<string> tokens(beg, end);
		string key = tokens[0];

		vector<string> phonemes;
		for(auto it = tokens.begin()+1; it != tokens.end(); ++it) {
			phonemes.push_back(*it);
		}

		dictionary[key] = phonemes;
		
	}

	myfile.close();
}


vector<string> phoneme_dictionary::get_entry(string entry) {
	transform(entry.begin(), entry.end(), entry.begin(), ::toupper);
	vector<string> res;
	if(dictionary.count(entry) > 0) {
		res = dictionary[entry];

	}

	return res;
}

string phoneme_dictionary::get_entry_string(string entry) {
	vector<string> res = get_entry(entry);


	string ret = "";
	for(auto& i : res) {
		ret += i + " ";
	}

	return ret;
}

int phoneme_dictionary::num_syllables(string entry) {
	auto vec = get_entry(entry);

	int c = 0;
	for(auto& i : vec) {
		if(i.find('1') != string::npos || i.find('0') != string::npos || i.find('2') != string::npos) {
			c++;
		}
	}

	return c;
}

bool phoneme_dictionary::is_rhyme(string s1, string s2) {
	vector<string> v1 = get_entry(s1);
	vector<string> v2 = get_entry(s2);

	if(v1.size() == 0 || v2.size() == 0) {
		return false;
	}

	size_t strong_phoneme1;
	size_t strong_phoneme2;
	for(size_t i = 0; i < v1.size(); ++i) {
		if(v1[i].find('1') != string::npos) {
			strong_phoneme1 = i;
		}


	}

	for(size_t i = 0; i < v2.size(); ++i) {
		if(v2[i].find('1') != string::npos) {
			strong_phoneme2 = i;
		}

		
	}

	if(v1.size() - strong_phoneme1 != v2.size() - strong_phoneme2) {
		return false;
	}

	for(; strong_phoneme1 < v1.size(); strong_phoneme1++, strong_phoneme2++) {
		if(v1[strong_phoneme1] != v2[strong_phoneme2]) {
			return false;
		}
	}

	//todo: also check that v2 has no more phonemes left!

	return true;
}