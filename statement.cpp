#include "statement.hpp"

statement* statement::make_if_statement(expression* condition, vector<statement*> body) {
	if_statement* s = new if_statement(condition, body);

	return s;
}
statement* statement::make_dummy() {
	dummy* d = new dummy();
	return d;
}