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
	if (t.token_type != expected_type)
	{
		syntax_error();
	}
	return t;
}

void Parser::peek()
{
	Token t = lexer.GetToken();
	lexer.UngetToken(t);
	return t;
}

//Parsing

void Parser::parse_program()
{
	//program --> var_section body
	parse_var_section();
	parse_body();
}

void Parser::parse_var_section()
{
	//id_list SEMICOLON
	parse_id_list();
	expect(SEMICOLON);
}

void Parser::parse_id_list()
{
	expect(ID);
	Token t = peek();
	if (t.token_type == COMMA) //id_list --> ID COMMA id_list
	{
		expect(COMMA);
		parse_id_list();
	}
	else if (t.token_type == SEMICOLON){ } //id_list --> ID
	else
	{
		syntax_error();
	}
	
}

void Parser::parse_body()
{
	//body --> LBRACE stmt_list RBRACE
	expect(LBRACE);
	parse_stmt_list();
	expect(RBRACE);
}

void Parser::parse_stmt_list()
{
	parse_stmt();
	Token t = peek();
	if (t.token_type == LBRACE) //stmt --> stmt stmt_list
	{
		parse_stmt_list();
	}
	else if (t.token_type == RPAREN || t.token_type == ID) { } //stmt__list --> stmt 
	else
	{
		syntax_error();
	}	
}

void Parser:: parse_stmt()
{
	Token t = peek();
	if (t.token_type == ID) //stmt --> assign_stmt
	{
		parse_assign_stmt();
	}
	else if (t.token_type == print) //stmt --> print_stmt
	{
		parse_print_stmt();
	}
	else if (t.token_type == WHILE) //stmt --> while_stmt
	{
		parse_while_stmt();
	}
	else if (t.token_type == IF) //stmt --> if_stmt
	{
		parse_if_stmt();
	}
	else if (t.token_type == SWITCH) //stmt --> switch_stmt
	{
		parse_switch_stmt();
	}
	else if (t.token_type == FOR) //stmt --> for_stmt
	{
		parse_for_stmt();
	}
	else
	{
		syntax_error();
	}
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







