#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include "../include/calculator.hpp"

using namespace Calculator;

static inline char* skip_spaces(const char* optr)
{
	char* ptr = ((char*)optr);
	while(isspace(*ptr)&&*ptr) ptr++;
	return ptr;
}

static inline char* skip_nonspace(const char* optr)
{
	char* ptr = ((char*)optr);
	while(!isspace(*ptr)&&*ptr) ptr++;
	return ptr;
}


Expression::~Expression()
{
}

Expression* Expression::build(const char* expression)
{
	char* ptr = skip_spaces(expression);
	char* end = ptr + strlen(ptr);
	Expression* lhs = NumberExpression::parse(ptr);
	if(lhs!=nullptr){
		// we have a number!
		while(ptr<end)
		{
			int index =  strcspn(ptr,"^+-/*%");
			if((ptr+=index)<end)
			{
				char op = *ptr++;
				if(op=='*'&&*ptr=='*')
				{
					ptr++;
					op = '^';//support the alternative syntax of power's as python does.
				}
				if(op=='/'&&*ptr=='/')
				{
					ptr++;
					op = '%';//fraking MSDOS uses it's characters weirdly.
				}
				ptr = skip_spaces(ptr);
				if(ptr<end)
				{
					Expression* rhs = NumberExpression::parse(ptr);
					lhs = new CalculationExpression(lhs,op,rhs);
				}
			}
		}
	}
	return lhs;
}

/*
Number Expression Class
 - Constructor: (char*)
                The class is responsible for parsing the given string as a number.
 - [static] parse: (char*)
                Searches for a number, returns a new Number Expression from the heap.
*/

NumberExpression::NumberExpression(const char* d):
data(d)
{
}

NumberExpression* NumberExpression::parse(const char* ptr)
{
	NumberExpression* ret = nullptr;
	char* mptr = skip_spaces(ptr);
	if(isdigit(*mptr))
	{
		ret = new NumberExpression(mptr);
	}
	return ret;
}

double NumberExpression::evaluate()
{
	//add in my own string to number implementation here.
	//[ adds support for other number systems ].
	//[ also, I can remove old <cstdlib> include!! ]
	return strtod(data,NULL);
}

/*
Calculation Expression Class
 - Constructor: (Expression*,char,Expression*)
                left-hand-side of a calculation.
                operator to combine left and right hand sides.
                right-hand-side of the calculation.
 - [static] is_operator: (char)
                returns true if supplied character matches a calculation operator.
*/

CalculationExpression::CalculationExpression(Expression* l,char o,Expression* r):
left(l),
oper(o),
right(r)
{
}

bool CalculationExpression::is_operator(char op)
{
	return op=='+'||op=='-'||op=='*'||op=='/'||op=='^'||op=='%';
}

double CalculationExpression::evaluate()
{
	double lhs = left->evaluate(), rhs = right->evaluate();
	switch(oper)
	{
		case '+':
			return lhs + rhs;
		case '-':
			return lhs - rhs;
		case '*':
			return lhs * rhs;
		case '/':
			return lhs / rhs;
		case '^':
			return pow(lhs,rhs);
		case '%':
			return fmod(lhs,rhs);
		default:
			return 0;
	}
}

CalculationExpression::~CalculationExpression()
{
	delete left;
	delete right;
	left = right = nullptr; // just in case it gets destroyed twice?
}