#include "token.hpp"

token::token(string l) {
	lexeme = l;
}

token::token() {
	lexeme = "";
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

bool token::is_comma() {
	return lexeme == ",";
}

bool token::is_word() {
	return !is_quote() && !is_question() && !is_newline() && !is_comma();
}

bool token::is_newline() {
	return lexeme == "\n";
}

string token::get_lexeme() {
	return lexeme;
}