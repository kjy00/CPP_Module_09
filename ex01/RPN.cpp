#include "RPN.hpp"

RPN::RPN()
{
	_expr = "";
}

RPN::RPN(char* expr)
{
	_expr = expr;
}

RPN::RPN(const RPN &rpn)
{
	*this = rpn;
}

RPN& RPN::operator=(const RPN& rpn)
{
	_expr = rpn._expr;
	_stack = rpn._stack;
	return *this;
}

RPN::~RPN()
{

}

int RPN::calc(int A, int B, char op)
{
	switch (op)
	{
		case '+':
			return A + B;
		case '-':
			return B - A;
		case '*':
			return A * B;
		case '/':
		{
			if (A == 0) throw std::invalid_argument("cannot divide by zero.");
			return B / A;
		}
	}
	return 0;
}

void RPN::execute()
{
	std::string operators = "+-*/";

	for (size_t i = 0; i < _expr.length(); i++) {
		if (isspace(_expr[i])) continue;
		if (isdigit(_expr[i])) _stack.push(_expr[i] - '0');
		else if (operators.find(_expr[i]) != std::string::npos)
		{
			if (_stack.size() == 0) throw std::invalid_argument("Invalid input");
			int A = _stack.top();
			_stack.pop();
			if (_stack.size() == 0) throw std::invalid_argument("Invalid input");
			_stack.top() = calc(A, _stack.top(), _expr[i]);
		}
		else throw std::invalid_argument("Invalid input");
	}
	if (_stack.size() != 1) throw std::invalid_argument("Invalid input");
	std::cout << _stack.top() << std::endl;
}
