

#include <string>
#include <vector>
#include "token.hpp"
#include "dictionary.hpp"
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;



enum CHAR_TYPE { WHITESPACE, LETTER, QUOTE, COMMA, QUESTION, OTHER };

class lexer {
	phoneme_dictionary dict;
public:
	lexer(string dictionary_name) {
		dict.read_file(dictionary_name);
	}

	CHAR_TYPE char_type(char c);

	vector<token> read(string filename);
};