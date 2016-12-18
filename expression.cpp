#include "expression.hpp"


expression* expression::make_binop(char c, expression* l, expression* r) {
	binop* b = new binop(c, l, r);
	return b;
}

expression* expression::make_integer(vector<string> int_strings) {
	poet_int* p = new poet_int(int_strings);
	return p;
}

expression* expression::make_id(string id) {
	identifier* i = new identifier(id);
	return i;
}