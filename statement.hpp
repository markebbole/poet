

#include <vector>
#include <string>
#include "expression.hpp"
#ifndef STATEMENT_HPP
#define STATEMENT_HPP


class expression;
using namespace std;

enum STATEMENT_TYPE { IF, ASSIGN, DUMMY, WHILE, PRINT };
class statement {



public:
	statement() {}

	virtual string statement_string(int depth = 0) { return ""; }

	static statement* make_if_statement(expression* condition, vector<statement*> body);
	static statement* make_dummy();
	static statement* make_assign(string var, expression* val);
	static statement* make_while_statement(expression* condition, vector<statement*> body);
	static statement* make_print(expression* print_exp);

	string get_depth(int d)
	{
	 string res = "";
	 for(int i=0; i < d; i++)
	   res+="\t";
	 return res;
	}

	virtual STATEMENT_TYPE get_type() { return IF; }


};



class if_statement : public statement {

public:
	expression* condition;
	vector<statement*> body;

	if_statement(expression* condition, vector<statement*> body) : condition(condition), body(body) {}


	virtual string statement_string(int depth) {
		string res = get_depth(depth) + "IF\n";
		res += condition->exp_string(depth+1);
		res += get_depth(depth) + "THEN{\n";
		for(size_t i = 0; i < body.size(); ++i) {
			res += body[i]->statement_string(depth+1) + "\n";
		}

		res += get_depth(depth) + "}\n";

		return res;

	}

	virtual STATEMENT_TYPE get_type() {
		return IF;
	}
};

class while_statement : public statement {

	
public:

	expression* condition;
	vector<statement*> body;
	while_statement(expression* condition, vector<statement*> body) : condition(condition), body(body) {}


	virtual string statement_string(int depth) {
		string res = get_depth(depth) + "WHILE\n";
		res += condition->exp_string(depth+1);
		res += get_depth(depth) + "DO{\n";
		for(size_t i = 0; i < body.size(); ++i) {
			res += body[i]->statement_string(depth+1) + "\n";
		}

		res += get_depth(depth) + "}\n";

		return res;

	}

	virtual STATEMENT_TYPE get_type() {
		return WHILE;
	}
};


class print_statement : public statement {
	

public:
	expression* print_exp;
	print_statement(expression* p) : print_exp(p) {}

	virtual string statement_string(int d) {
		string res = get_depth(d) + "PRINT\n";
		res += print_exp->exp_string(d+1);
		return res;
	}

	virtual STATEMENT_TYPE get_type() {
		return PRINT;
	}
};


class assign_statement : public statement {
	
public:

	string var;
	expression* val;
	assign_statement(string v, expression* val) : var(v), val(val) {}

	virtual string statement_string(int d) {
		string res = get_depth(d) + "ASSIGN " + var + "\n";
		res += get_depth(d) + "VAL\n";
		res += val->exp_string(d+1);

		return res;
	}

	virtual STATEMENT_TYPE get_type() {
		return ASSIGN;
	}
};

class dummy : public statement {

public:
	dummy() {}

	virtual string statement_string(int depth) {
		string res = get_depth(depth) + "DUMMY\n";
		return res;
	}

	virtual STATEMENT_TYPE get_type() {
		return DUMMY;
	}
};


#endif