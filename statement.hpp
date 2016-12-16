

#include <vector>
#include <string>
#include "expression.hpp"
#ifndef STATEMENT_HPP
#define STATEMENT_HPP


class expression;
using namespace std;

enum STATEMENT_TYPE { IF, ASSIGN, DUMMY };
class statement {



public:
	statement() {}

	virtual string statement_string(int depth = 0) { return ""; }

	static statement* make_if_statement(expression* condition, vector<statement*> body);
	static statement* make_dummy();

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

	expression* condition;
	vector<statement*> body;
public:
	if_statement(expression* condition, vector<statement*> body) : condition(condition), body(body) {}


	virtual string statement_string(int depth) {
		string res = get_depth(depth) + "IF\n";
		res += condition->exp_string(depth+1);
		res += get_depth(depth) + "THEN\n";
		for(size_t i = 0; i < body.size(); ++i) {
			res += body[i]->statement_string(depth+1) + "\n";
		}

		return res;

	}

	virtual STATEMENT_TYPE get_type() {
		return IF;
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