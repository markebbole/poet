#include "token.hpp"

token::token(string l) {
	lexeme = l;
}

void token::set_lexeme(string l) {
	lexeme = l;
}

bool token::is_quote() {
	return lexeme == "\"";
}

bool token::is_question() {
	return lexeme == "?";
}

bool token::is_word() {
	return !is_quote() && !is_question();
}

string token::get_lexeme() {
	return lexeme;
}