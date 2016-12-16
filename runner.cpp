#include "runner.hpp"


int main() {
	lexer lex;

	vector<token> tokens = lex.read("test.poem");

	parser p("dict");

	vector<statement*> statements = p.parse(tokens);

	for(size_t i = 0; i < statements.size(); ++i) {
		std::cout << statements[i]->statement_string() << std::endl;
	}

	
}