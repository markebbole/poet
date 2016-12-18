
#include <vector>
#include <string>
#include "token.hpp"
#include "dictionary.hpp"
#include "expression.hpp"
#include "statement.hpp"




using namespace std;
class parser {

	phoneme_dictionary dict;
public:

	parser(string dictionary_name) {
		dict.read_file(dictionary_name);
	}

	expression* EXPRESSION(vector<token>& tokens, size_t& first_token, size_t last_token);
	statement* IF_STATEMENT(vector<token>& tokens, size_t& next_token);
	statement* PRINT(vector<token>& tokens, size_t& next_token);
	statement* WHILE_STATEMENT(vector<token>& tokens, size_t & next_token);
	statement* DUMMY(vector<token>& tokens, size_t& next_token);
	statement* STATEMENT(vector<token>& tokens, size_t& next_token);
	statement* ASSIGNMENT(vector<token>& tokens, size_t& next_token);

	string get_var(vector<token>& tokens, size_t& next_token);
	vector<statement*> get_body(vector<token>& tokens, size_t& next_token, token term);
	int find_newline(vector<token>& tokens, size_t & next_token);
	bool is_consonant(char c);
	vector<statement*> parse(vector<token> tokens);

};