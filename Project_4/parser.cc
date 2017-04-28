//This is the parser for Project 4
//

#include <iostream>
#include <cstdlib>
#include "parser.h"
#include "compiler.h"

using namespace std;

struct variableList variables = NULL; //global list of variables

void Parser::syntax_error()
{
	cout << "Syntax Error\n";
	exit(1);
}

Token Parser::expect(TokenType expected_type)
{
	Token t = lexer.GetToken();
	if (t.token_type != expected_type)
	{
		syntax_error();
	}
	freturn t;
}

Token Parser::peek();
{
	Token t = lexer.GetToken();
	lexer.UngetToken(t);
	return t;
}

void add(ValueNode* value)
{
	struct variableList* traverser = variables;
	while(traverser->next != NULL)
	{
		traverser = traverser->next;
	}
	traverser->next->variable = value;
}

/***********      PARSING     *************/

struct StatementNode* Parser::parse_assign_stmt()
{
	//expression on left_hand_side is evaluated
	//Result is stored in location associated w/right_hand side of expression
	// assign_stmt->ID EQUAL primary SEMICOLON
	// assign_stmt->ID EQUAL expr SEMICOLON
	
	struct StatementNode asSt = new StatementNode();
	asSt->type = ASSIGN_STMT;
	asSt->assign_stmt = new AssignmentStatement();

	Token id = expect(ID);
	asSt->assign_stmt->left_hand_side = new ValueNode();
	asSt->assign_stmt->left_hand_side->name = id.lexeme;
	asSt->assign_stmt->left_hand_side->value = 0;

	add(asSt->assign_stmt->left_hand_side);	//add new ValueNode to variable list

	expect(EQUAL);
	Token t1 = lexer.GetToken();
	Token t2 = peek();
	if(t2.token_type == SEMICOLON) // assign_stmt --> ID EQUAL primary SEMICOLON
	{
		asSt->assign_stmt->op = OPERATOR_NONE;
		asSt->assign_stmt->operand2 = NULL;
		lexer.UngetToken(t1);
		asSt->assign_stmt->operand1 = parse_primary();
		add(asSt->assign_stmt->operand1);
		expect(SEMICOLON);
	}
	else if (t2.token_type == PLUS || t2.token_type == MINUS || t2.token_type == MULT || t2.token_type == DIV) //assign_stmt --> ID EQUAL primary SEMICOLON
	{
		lexer.UngetToken(t1);
		asSt->assign_stmt->operand1 = parse_primary();
		add(asSt->assign_stmt->operand1);

		if (t2.token_type == PLUS)
		{
			asSt->assign_stmt->op = OPERATOR_PLUS;
		}
		else if (t2.token_type == MINUS)
		{
			asSt->assign_stmt->op = OPERATOR_MINUS;
		}
		else if (t2.token_type == MULT)
		{
			asSt->assign_stmt->op = OPERATOR_MULT;
		}
		else if (t2.token_type == DIV)
		{
			asSt->assign_stmt->op = OPERATOR_DIV;
		}

		asSt->assign_stmt->operand2 = parse_primary();
		add(asSt->assign_stmt->operand2);

		expect(SEMICOLON);
	}
	return asSt;
}

struct ValueNode* Parser::parse_primary()
{
	struct ValueNode* primary = new ValueNode();
	Token t = lexer.GetToken();
	if (t.token_type == ID || t.token_type == NUM)
	{
		primary->name = t.lexeme;
		primary->value = 0;
	}
	else
	{
		syntax_error();
	}
	add(primary);
	return primary;
}

struct StatementNode* Parser::parse_condition()
{
	//values in the locations assoc. w/ operands obtained
	//relational operator applied to these values
	//results in a true or false value
	
	struct StatementNode condition = new StatementNode();
	condition->type = IF_STMT;
	condition->if_stmt = new IfStatement();
	condition->if_stmt->operand1 = parse_primary();
	Token t = parse_relop();
	if (t.token_type == GREATER)
	{
		condition->if_stmt->ConditionalOperatorType = CONDITION_GREATER;
	}
	else if (t.token_type == LESS)
	{
		condition->if_stmt->ConditionalOperatorType = CONDITION_LESS;
	}
	else if (t.token_type == NOTEQUAL)
	{
		condition->if_stmt->ConditionalOperatorType = CONDITION_NOTEQUAL;
	}

	condition->if_stmt->operand2 = parse_primary();

	return condition;
}

Token Parser::parse_relop()
{
	Token t = lexer.GetToken();
	if (t.token_type == GREATER || t.token_type == LESS || t.token_type == NOTEQUAL)
	{
		return t;
	}
	else
	{
		syntax_error();
	}
}

struct StatementNode* compiler::parse_generate_intermediate_representation()
{
	struct StatementNode input = parse_program();
	return input;
}















