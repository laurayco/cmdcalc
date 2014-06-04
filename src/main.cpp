#include <iostream>
#include <algorithm>
#include <string> 
#include "../include/calculator.hpp"

#define NO_INTERVENE 0
#define DISPLAY_HELP 1
#define QUIT_PROGRAM 2

static inline void evaluate(const char* str)
{
	auto expr = Calculator::Expression::build(str);
	std::cout << expr->evaluate() << std::endl;
	delete expr;
}

static inline void display_help()
{
	std::string help =
	"-helptext-"
	"\n";
	std::cout<<help<<std::endl;
}

static inline int intervene(std::string str)
{
	std::string data = str;
	int RET_MASK = NO_INTERVENE;
	//std::transform(data.begin(), data.end(), data.begin(), std::tolower);
	if(data.find("help")!=std::string::npos)
		RET_MASK |= DISPLAY_HELP;
	if(data.find("exit")!=std::string::npos||
	   data.find("quit")!=std::string::npos)
		RET_MASK |= QUIT_PROGRAM;
	return RET_MASK;
}

int main(int argc,char** argv)
{
	if(argc<2)
	{
		std::string expression;
		bool run=true;
		while(run)
		{
			std::cout << ">";
			std::getline(std::cin,expression);
			int actions = intervene(expression);
			if(actions&DISPLAY_HELP)
				display_help();
			if(actions&QUIT_PROGRAM)
				run=false;
			if(actions==NO_INTERVENE)
			{
				std::cout << "\t";
				evaluate(expression.c_str());
			}
		}
	}
	else
	{
		std::string expression=argv[1];
		for(int i=2;i<argc;i++)
			expression += ' ' + argv[i];
		evaluate(expression.c_str());
	}
	return 0;
}