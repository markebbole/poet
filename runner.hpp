#include "lexer.hpp"
#include "parser.hpp"

int main() {
	lexer lex();

	vector<token> tokens = lex.read("test.poem");

	parser p("dict");
}