#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>

class Expression;
class NumberExpression;
class CalculationExpression;

class Expression
{
	public:
		virtual double evaluate()=0;
		virtual ~Expression();
		static Expression* build(const char*);
};

class NumberExpression: public Expression
{
	const char* data;
	public:
		NumberExpression(const char* dat):
			data(dat)
		{
		}
		virtual double evaluate();
		static NumberExpression* parse(const char*);
};

class CalculationExpression: public Expression
{
	Expression *left,*right;
	const char oper;
	public:
		CalculationExpression(Expression* lhs,const char op,Expression* rhs):
			left(lhs),
			right(rhs),
			oper(op)
		{
		}
		virtual double evaluate();
		virtual ~CalculationExpression();
		static bool is_operator(char);
};

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

Expression::~Expression()
{
}

double NumberExpression::evaluate()
{
	//add in my own string to number implementation here.
	//[ adds support for other number systems ].
	//[ also, I can remove old <cstdlib> include!! ]
	return strtod(data,NULL);
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

int main(int argc,char** argv)
{
	std::string expression=argv[1];
	for(int i=2;i<argc;i++)
	{
		expression+=' ';
		expression+=argv[i];
	}
	std::cout << expression << std::endl << std::endl;
	Expression* expr = Expression::build(expression.c_str());
	std::cout << expr->evaluate() << std::endl;
	delete expr;
	return 0;
}