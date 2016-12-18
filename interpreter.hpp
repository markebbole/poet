
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "statement.hpp"
#include "expression.hpp"

using namespace std;

class interpreter {

map<string, int> values;

public:
	interpreter() {}

	void interpret(vector<statement*> statements);

	int eval(expression* e);

	int eval_binop(binop* b);


};