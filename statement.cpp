#include "statement.hpp"

statement* statement::make_if_statement(expression* condition, vector<statement*> body) {
	if_statement* s = new if_statement(condition, body);

	return s;
}

statement* statement::make_while_statement(expression* condition, vector<statement*> body) {
	while_statement* w = new while_statement(condition, body);

	return w;
}
statement* statement::make_dummy() {
	dummy* d = new dummy();
	return d;
}

statement* statement::make_assign(string var, expression* val) {
	assign_statement* a = new assign_statement(var, val);

	return a;
}