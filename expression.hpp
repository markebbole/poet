#include <vector>
#include <string>
#include <iostream>


using namespace std;

#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP





enum EXP_TYPE { BINOP, INT, ID };

class expression {

public:
	expression() {}
	virtual string exp_string(int depth = 0) { return ""; }



	static expression* make_binop(char c, expression* l, expression* r);
	static expression* make_integer(vector<string> int_strings);
	static expression* make_id(string id);

	static bool is_consonant(char c) {
		return !(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
	}

	virtual EXP_TYPE get_type() { return INT; }

	string get_depth(int d)
	{
	 string res = "";
	 for(int i=0; i < d; i++)
	   res+="\t";
	 return res;
	}

	virtual ~expression() {}

};


enum BINOP_TYPE { PLUS, MINUS, MULT, DIV, GT, GEQ, LT, LEQ, EQ, MOD };

class binop : public expression {
	char op;
	expression* left;
	expression* right;
public:
	binop(char op, expression* left, expression* right) : op(op), left(left), right(right) {

	}

	expression* get_left() {
		return left;
	}

	expression* get_right() {
		return right;
	}

	BINOP_TYPE get_binop_type() {
		switch(op) {
			case 'a': return PLUS;
			case 'b': return MINUS;
			case 'c': return MULT;
			case 'd': return DIV;
			case 'e': return GT;
			case 'f': return GEQ;
			case 'g': return LT;
			case 'h': return LEQ;
			case 'i': return EQ;
			case 'j': return MOD;
			default:
				{
				cout << "ERROR WITH BINOP TYPE" << endl;
				break;
				}
		}

		return PLUS;


	}

	string get_binop_string() {
		switch(op) {
			case 'a': return "+";
			case 'b': return "-";
			case 'c': return "*";
			case 'd': return "/";
			case 'e': return ">";
			case 'f': return ">=";
			case 'g': return "<";
			case 'h': return "<=";
			case 'i': return "==";
			case 'j': return "\%";
			default:
				break;
		}

		return "ERROR";
	}


	virtual EXP_TYPE get_type() {
		return BINOP;
	}

	virtual string exp_string(int d)
	{
	  string res =  get_depth(d) + "BINOP: " + get_binop_string() + "\n";
	  res += get_depth(d) + "LEFT\n";
	  res += left->exp_string(d+1);
	  res += get_depth(d) + "RIGHT\n";
	  res += right->exp_string(d+1);
	  return res;
	}
};


class poet_int : public expression {
	int p_int;

public:
	poet_int(vector<string> int_strings);

	int get_int_value() {
		return p_int;
	}

	virtual EXP_TYPE get_type() {
		return INT;
	}

	virtual string exp_string(int d)
	{
	  string i = std::to_string(p_int);
	  string res =  get_depth(d) + "Int: " + i + "\n";
	  return res;
	}
};

class identifier : public expression {
	string id;

public:
	identifier(string id) : id(id) {}

	string get_id() {
		return id;
	}

	virtual EXP_TYPE get_type() {
		return ID;
	}

	virtual string exp_string(int d) {
		string res = get_depth(d) + "ID: " + id + "\n";
		return res;
	}
};

#endif