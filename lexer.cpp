#include "lexer.hpp"
#include <iostream>

vector<token> lexer::read(string filename) {
	vector<token> tokens;

	string prog_line;
	ifstream source_file(filename);

	while(getline (source_file, prog_line)) {
		string lexeme = "";

		bool in_word = false;

		for(size_t i = 0; i < prog_line.size(); ++i) {
			char c = prog_line[i];

			CHAR_TYPE t = char_type(c);

			if(t == LETTER) {
				if(c >= 97 && c <= 122) {
					c -= 32; //to uppercase
				}
				lexeme += c;
				in_word = true;
			}
			else if(t == WHITESPACE) {
				if(in_word) {
					token tok(lexeme);
					tokens.push_back(tok);
				}

				in_word = false;
				lexeme = "";
			}
			else if(t == QUOTE || t == QUESTION || t == COMMA) {
				if(in_word) {
					token tok(lexeme);
					tokens.push_back(tok);
				}

				in_word = false;
				lexeme =  c;
				token tok(lexeme);
				tokens.push_back(tok);
				lexeme = "";
			}
		}

		//reached end of line.
		if(in_word) {
			token tok(lexeme);
			tokens.push_back(tok);
		}

		lexeme = "\n";
		token tok(lexeme);
		tokens.push_back(tok);
	}


	return tokens;
}


CHAR_TYPE lexer::char_type(char c) {

	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 39) ? LETTER :
		   (c == ' ' || c == '\n' || c == '\t') ? WHITESPACE :
		   (c == '\"') ? QUOTE :
		   (c == '?') ? QUESTION :
		   (c == ',') ? COMMA : OTHER;
}

