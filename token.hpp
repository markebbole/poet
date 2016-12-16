#include <string>


using namespace std;


#ifndef TOKEN_HPP
#define TOKEN_HPP
class token {

	string lexeme;

public:

	token(string l);
	token();
	bool is_quote();
	bool is_question();

	bool is_comma();

	bool is_word();

	bool is_newline();

	void set_lexeme(string l);

	string get_lexeme();

};


#endif