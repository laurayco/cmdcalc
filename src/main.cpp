#include <iostream>
#include "../include/calculator.hpp"

int main(int argc,char** argv)
{
	std::string expression=argv[1];
	for(int i=2;i<argc;i++)
	{
		expression+=' ';
		expression+=argv[i];
	}
	Calculator::Expression* expr = Calculator::Expression::build(expression.c_str());
	std::cout << expr->evaluate() << std::endl;
	delete expr;
	return 0;
}