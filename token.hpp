#include <string>
using namespace std;
class token {

	string lexeme;

public:

	token(string l);
	bool is_quote();
	bool is_question();

	bool is_word();

	void set_lexeme(string l);

	string get_lexeme();

};