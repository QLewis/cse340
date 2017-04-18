//This is the parser for Project 4

#include <iostream>
#include <cstdlib>
#include "parser.h"

using namespace std;

void Parser::syntax_error()
{
	cout << "Syntax Error\n";
	exit(1);
}

void Parser::expect(TokenType expected_type)
{
	Token t = lexer.GetToken();
	lexer.UngetToken(t);
	return t;
}

//Parsing

void Parser::Parser::parse_program()
{
	//program --> var_section body
	parse_var_section();
	parse_body();
}

void Parser:: parse_var_section()
{
}

void Parser:: parse_id_list()
{
}

void Parser:: parse_body()
{
}

void Parser:: parse_stmt_list()
{
}

void Parser:: parse_stmt()
{
}

void Parser:: parse_assign_stmt()
{
}

void Parser:: parse_expr()
{
}

void Parser:: parse_primary()
{
}

void Parser:: parse_op()
{
}

void Parser:: parse_print_stmt()
{
}

void Parser:: parse_while_stmt()
{
}

void Parser:: parse_if_stmt()
{
}

void Parser:: parse_condition()
{
}

void Parser:: parse_relop()
{
}

void Parser:: parse_switch_stmt()
{
}

void Parser:: parse_for_stmt()
{
}


void Parser:: parse_case_list()
{
}

void Parser:: parse_case()
{
}

void Parser:: parse_default_case()
{
}







