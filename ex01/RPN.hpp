#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <sstream>
#include <iostream>


class RPN {
	public:
		RPN();
		RPN(char* expr);
		RPN(const RPN &rpn);
		RPN& operator=(const RPN& rpn);
		~RPN();

		void execute();
		int calc(int A, int B, char op);
	private:
		std::stack<int> _stack;
		std::string _expr;
};

#endif
