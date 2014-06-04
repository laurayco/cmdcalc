
namespace Calculator
{
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
			NumberExpression(const char*);
			virtual double evaluate();
			static NumberExpression* parse(const char*);
	};

	class CalculationExpression: public Expression
	{
		Expression *left,*right;
		const char oper;
		public:
			CalculationExpression(Expression* lhs,const char op,Expression* rhs);
			virtual double evaluate();
			virtual ~CalculationExpression();
			static bool is_operator(char);
	};

}