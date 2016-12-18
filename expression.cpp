#include "expression.hpp"
#include <math.h>
#include <iostream>
using namespace std;

expression* expression::make_binop(char c, expression* l, expression* r) {
	binop* b = new binop(c, l, r);
	return b;
}

expression* expression::make_integer(vector<string> int_strings) {
	poet_int* p = new poet_int(int_strings);
	return p;
}

expression* expression::make_id(string id) {
	identifier* i = new identifier(id);
	return i;
}


poet_int::poet_int(vector<string> int_strings) {
	//these are all words.
	p_int = 0;

	for(size_t i = 0; i < int_strings.size(); ++i) {

		string word = int_strings[i];
		cout << word << endl;
		int tmp = 0;
		//we add together consonants and vowels
		if(word.size() >= 2 && word[0] < word[1]) {

			tmp = word.size();
		} else if(word.size() == 1) {
			tmp = 0;
		} else {
			//otherwise, tmp = |vowels - consonants|
			int num_consonants = 0;
			for(size_t j = 0; j < word.size(); ++j) {
				if(expression::is_consonant(word[j])) {
					num_consonants ++;
				}
			}

			int num_vowels = word.size() - num_consonants;

			tmp = abs(num_vowels - num_consonants);
		}

		cout << tmp << endl;

		p_int += pow(10, int_strings.size()-1-i) * tmp;

		if(i == 0 && tmp == 0) {
			//starts with 0, end
			break;
		}

	}
}