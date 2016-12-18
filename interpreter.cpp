#include "interpreter.hpp"

void interpreter::interpret(vector<statement*> statements) {
	for(size_t i = 0; i < statements.size(); ++i) {
		statement* current = statements[i];

		STATEMENT_TYPE t = current->get_type();

		switch(t) {
			case IF: {
				//cout << "IF" << endl;
				if_statement* if_s = static_cast<if_statement*>(current);
				expression* condition = if_s->condition;
				int e = eval(condition);

				if(e != 0) {
					vector<statement*> body = if_s->body;

					interpret(body);
				}

				break;

			}

			case ASSIGN: {
				assign_statement* a_s = static_cast<assign_statement*>(current);

				string var = a_s->var;
				expression* e = a_s->val;

				int e_int = eval(e);

				values[var] = e_int;

				break;
			}

			case WHILE: {
				while_statement* w_s = static_cast<while_statement*>(current);
				expression* condition = w_s->condition;
				vector<statement*> body = w_s->body;
				int e = eval(condition);

				while(e != 0) {
					interpret(body);
					e = eval(condition);
				}

				break;

			}

			case PRINT: {
				print_statement* p_s = static_cast<print_statement*>(current);

				int e = eval(p_s->print_exp);

				cout << e << endl;
				break;
			}


			default:
			break;
		}
	}
}

int interpreter::eval(expression* e) {

	EXP_TYPE t = e->get_type();

	switch(t) {
		case INT: {
			poet_int* p = static_cast<poet_int*>(e);
			return p->get_int_value();
		}

		case ID: {
			identifier* i = static_cast<identifier*>(e);
			string id = i->get_id();

			int v = values[id];
			return v;
		}

		case BINOP: {

			binop* b = static_cast<binop*>(e);
			return eval_binop(b);
		}

		default:
		break;
	}

	cout << "ERRROR" << endl;

	return 0;
}

int interpreter::eval_binop(binop* b) {
	expression* left = b->get_left();
	expression* right = b->get_right();

	int l = eval(left);
	int r = eval(right);

	BINOP_TYPE t = b->get_binop_type();

	switch(t) {
		case PLUS:
			return l+r;
		case MINUS:
			return l-r;
		case MULT:
			return l*r;
		case DIV:
			return l/r;
		case GT:
			return l > r ? 1 : 0;
		case GEQ:
			return l >= r ? 1 : 0;
		case LT:
			return l < r ? 1 : 0;
		case LEQ:
			return l <= r ? 1 : 0;
		case EQ:
			return l == r ? 1 : 0;
		case MOD:
			return l % r;
		default: break;
	}


	cout << "BINOP ERROR " << b->get_binop_string() << endl;
	return 0;
}


