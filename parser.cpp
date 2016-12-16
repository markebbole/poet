#include "parser.hpp"

bool in_bounds(vector<token>& tokens, size_t& next_token) {
	return next_token < tokens.size();
}

expression* parser::EXPRESSION(vector<token>& tokens, size_t& first_token, size_t last_token) {
	//first word must be 2 syllables, starting with one of the operator letters

	token op = tokens[first_token];

	string lexeme = op.get_lexeme();


	if(dict.num_syllables(lexeme) == 2) {
		char c = lexeme[0];

		//to lowercase
		if(c >= 65 && c <= 90) {
			c+= 32; 
		}

		//is an operator!
		if(c >= 97 && c <= 105) {
			cout << lexeme << " is an operator" << endl;
			first_token++;
			while(!tokens[first_token].is_newline() && !tokens[first_token].is_word()) { first_token++; }

			expression* left_operand = EXPRESSION(tokens, first_token, last_token);
			

			if(left_operand == 0) {
				return 0;
			}

			cout << "left operand: " << left_operand->get_type() << endl;

			while(!tokens[first_token].is_newline() && !tokens[first_token].is_word()) { first_token++; }

			cout << "start of right exp: " << tokens[first_token].get_lexeme() << endl;
			expression* right_operand = EXPRESSION(tokens, first_token, last_token);
			if(right_operand == 0) {
				return 0;
			}

			expression* binop = expression::make_binop(c, left_operand, right_operand);
			return binop;
		}
	}

	//otherwise, it has to be an integer!

	if(dict.num_syllables(lexeme) == 1) {
		//now continue finding one syllable words until you come across something that is not a one syllable word.

		vector<string> int_strings;
		string s = tokens[first_token].get_lexeme();

		do {
			int_strings.push_back(s);
			first_token++;
			s = tokens[first_token].get_lexeme();

		}while(dict.num_syllables(s) == 1);

		expression* number = expression::make_integer(int_strings);
		return number;

	}

	//not an operator or an integer, so return 0
	return 0;
}



statement* parser::IF_STATEMENT(vector<token>& tokens, size_t& next_token) {
	cout << "trying an if statement" << endl;
	token F1;
	token F2;
	if(in_bounds(tokens, next_token)) {
		F1 = tokens[next_token++];
	} else {
		return 0;
	}

	//find next word
	while(in_bounds(tokens, next_token) && !tokens[next_token].is_word()) { next_token++; }

	if(in_bounds(tokens, next_token)) {
		F2 = tokens[next_token++];
	} else {
		return 0;
	}

	if(!F1.is_word() || !F2.is_word()) {
		return 0;
	}

	//simple alliteration check for now. should be based on phonemes really
	if(F1.get_lexeme()[0] != F2.get_lexeme()[0]) {
		return 0;
	}

	cout << "first two words are good" << endl;



	//first part is good

	//now find the newline.

	bool found_newline = false;
	size_t n;
	for(n = next_token; n < tokens.size(); ++n) {
		if(tokens[n].is_newline()) {
			found_newline = true;
			break;
		}
	}

	if(!found_newline) {
		return 0;
	}


	//now, the tokens from [next_token, n) should be an expression

	expression* condition = EXPRESSION(tokens, next_token, n-1);



	if(condition == 0) {
		return 0;
	}

	next_token = n+1;

	//now, the token at n-1 is the terminator.
	token term = tokens[n-1];

	vector<statement*> body;
	token cmp_with_term;

	do {
		statement* b = STATEMENT(tokens, next_token);
		cout << b->get_type() << endl;
		if(b == 0) {
			return 0;
		}

		//otherwise, add to body list.
		body.push_back(b);
		cout << "cmp term: " << tokens[next_token-2].get_lexeme()  << "term: " << term.get_lexeme() << endl;
		cmp_with_term = tokens[next_token-2];
		cout << dict.is_rhyme(term.get_lexeme(), cmp_with_term.get_lexeme()) <<endl;

	}while(!dict.is_rhyme(term.get_lexeme(), cmp_with_term.get_lexeme()));

	cout << term.get_lexeme() << " and " << cmp_with_term.get_lexeme() << " rhyme." << endl;

	statement* if_statement = statement::make_if_statement(condition, body);
	return if_statement;


}


statement* parser::DUMMY(vector<token>& tokens, size_t& next_token) {
	while(!tokens[next_token++].is_newline()) {

	}

	statement* dummy = statement::make_dummy();
	return dummy;
}




statement* parser::STATEMENT(vector<token>& tokens, size_t& next_token) {
	statement* s;

	size_t token_save;


	token_save = next_token;
	cout << "trying to find statement starting with " << tokens[next_token].get_lexeme() << endl;

	s = IF_STATEMENT(tokens, next_token);
	if(s != 0) {

		return s;
	}

	

	next_token = token_save;
	cout << tokens[next_token].get_lexeme() << " not an if statement" << endl;

	s = DUMMY(tokens, next_token);



	return s;
}



vector<statement*> parser::parse(vector<token> tokens) {
	size_t next_token = 0;
	vector<statement*> statements;



	while(next_token < tokens.size()) {
		statement* s = STATEMENT(tokens, next_token);
		statements.push_back(s);
	}

	return statements;
	
}