

#include <string>
#include <vector>
#include "token.hpp"
#include <fstream>
#include <sstream>
#include <iterator>


using namespace std;



enum CHAR_TYPE { WHITESPACE, LETTER, QUOTE, COMMA, QUESTION, OTHER };

class lexer {
public:
	lexer() {
	}

	CHAR_TYPE char_type(char c);

	vector<token> read(string filename);
};