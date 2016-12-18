#include "runner.hpp"


int main() {
	lexer lex;

	vector<token> tokens = lex.read("test.poem");

	for(size_t i = 0; i < tokens.size(); ++i) {
		std::cout << tokens[i].get_lexeme() << std::endl;
	}


	parser p("dict");

	vector<statement*> statements = p.parse(tokens);

	for(size_t i = 0; i < statements.size(); ++i) {
		std::cout << statements[i]->statement_string() << std::endl;
	}

	interpreter evaluator;

	evaluator.interpret(statements);

	
}