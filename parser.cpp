#include "parser.hpp"

bool in_bounds(vector<token>& tokens, size_t& next_token) {
	return next_token < tokens.size();
}

expression* parser::EXPRESSION(vector<token>& tokens, size_t& first_token, size_t last_token) {
	//first word must be 2 syllables, starting with one of the operator letters

	while(in_bounds(tokens, first_token) && !tokens[first_token].is_word()) { first_token++; }

	if(first_token > last_token) {
		return 0;
	}
	
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
		} else {
			//it's an identifier lookup
			string var = get_var(tokens, first_token);

			expression* id = expression::make_id(var);
			return id;
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

	string f1_lex = F1.get_lexeme();

	if(f1_lex.size() < 2 || f1_lex[0] > f1_lex[1]) {
		return 0;
	}

	//find next word
	while(in_bounds(tokens, next_token) && !tokens[next_token].is_word()) { next_token++; }

	if(in_bounds(tokens, next_token)) {
		F2 = tokens[next_token++];
	} else {
		return 0;
	}



	if(!F1.is_word() || !F2.is_word())  {
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



statement* parser::WHILE_STATEMENT(vector<token>& tokens, size_t& next_token) {
	cout << "trying a while statement" << endl;
	token F1;
	token F2;
	if(in_bounds(tokens, next_token)) {
		F1 = tokens[next_token++];
	} else {
		return 0;
	}

	string f1_lex = F1.get_lexeme();

	if(f1_lex.size() < 2 || f1_lex[0] <= f1_lex[1]) {
		return 0;
	}

	//find next word
	while(in_bounds(tokens, next_token) && !tokens[next_token].is_word()) { next_token++; }

	if(in_bounds(tokens, next_token)) {
		F2 = tokens[next_token++];
	} else {
		return 0;
	}



	if(!F1.is_word() || !F2.is_word())  {
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

	statement* while_statement = statement::make_while_statement(condition, body);
	return while_statement;
}

bool parser::is_consonant(char c) {
	return !(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

string parser::get_var(vector<token>& tokens, size_t& next_token) {
	string var = "";
	for(size_t i = next_token; i < tokens.size(); ++i) {
		next_token++;
		if(!tokens[i].is_word()) { continue; }
		string curr_lex = tokens[i].get_lexeme();

		for(size_t j = 0; j < curr_lex.size(); ++j) {
			if(is_consonant(curr_lex[j])) {
				var += curr_lex[j];
				if(var.size() == 2) {
					return var;
				}
			}
		}
	}



	return ""; //failure
}

statement* parser::PRINT(vector<token>& tokens, size_t& next_token) {

	int quote1 = -1;
	int quote2 = -1;

	for(size_t i = next_token; i < tokens.size(); ++i) {
		//if find a newline before two quotes, not a print
		if(tokens[i].is_newline()) {
			return 0;
		}

		if(tokens[i].is_quote()) {
			if(quote1 >= 0) {
				quote2 = i;
				cout << "quote 2: " << i << endl;
				break;
			} else {
				cout << "quote 1: " << i << endl;
				quote1 = i;
			}
		}
	}

	
	if(quote1 >= 0 && quote2 >= 0) {
		size_t q1 = quote1 +1;
		size_t q2 = quote2 -1;
		std::cout << q1 << " " << q2 << endl;
		expression* print_exp = EXPRESSION(tokens, q1, q2);
		if(print_exp != 0) {
			statement* print = statement::make_print(print_exp);

			while(!tokens[next_token++].is_newline()) {

			}
			return print;
		}
	}

	return 0;
}

statement* parser::ASSIGNMENT(vector<token>& tokens, size_t& next_token) {
	token first;

	string var = get_var(tokens, next_token);		

	if(var == "") {
		return 0;
	}

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

	//now we have a valid variable. find the expression
	expression* val = EXPRESSION(tokens, next_token, n-1);

	if(val == 0) {
		return 0;
	}

	next_token = n+1;
	statement* assign = statement::make_assign(var, val);

	return assign;

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


	s = PRINT(tokens, next_token);

	if(s != 0) {
		return s;
	}

	next_token = token_save;

	s = IF_STATEMENT(tokens, next_token);
	if(s != 0) {

		return s;
	}

	next_token = token_save;


	cout << tokens[next_token].get_lexeme() << " not an if statement" << endl;

	s = WHILE_STATEMENT(tokens, next_token);
	if(s != 0) {
		return s;
	}
	next_token = token_save;

	s = ASSIGNMENT(tokens, next_token);

	if(s != 0) {
		return s;
	}

	next_token = token_save;

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