//This is the parser for Project 4

#include <iostream>
#include <cstdlib>
#include "parser.h"
#include "compiler.h"

using namespace std;

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
	return t;
}

Token Parser::peek()
{
	Token t = lexer.GetToken();
	lexer.UngetToken(t);
	return t;
}

//Parsing

struct StatementNode* Parser::parse_program()
{
	//program --> var_section body
	parse_var_section();
	parse_body();
}

struct StatementNode* Parser::parse_var_section()
{
	//id_list SEMICOLON
	parse_id_list();
	expect(SEMICOLON);
}

struct StatementNode* Parser::parse_id_list()
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

//DONE DONE DONE
struct StatementNode* Parser::parse_body()
{
	//body --> LBRACE stmt_list RBRACE
	struct StatementNode * stl;
	
	expect(LBRACE);
	stl = parse_stmt_list();
	expect(RBRACE);

	return stl;
}

//DONE DONE DONE
struct StatementNode* Parser::parse_stmt_list()
{
	struct StatementNode* st; //statement
	struct StatementNode* stl; //statement list

	st = parse_stmt();

	Token t = peek();
	if (t.token_type == ID || t.token_type == PRINT || t.token_type == WHILE || t.token_type == IF || t.token_type == SWITCH || t.token_type == FOR)
	{
		//stmt_list --> stmt stmt_list
		stl = parse_stmt_list();
		st->next = stl;
		return st;
	}
	else if (t.token_type == RBRACE)
	{
		//stmt_list --> stmt
		return st;
	}
	else
	{
		syntax_error();
	}
}

struct StatementNode* Parser::parse_stmt()
{
	struct StatementNode* st;
	Token t = peek();

	if (t.token_type == ID) //stmt --> assign_stmt
	{
		parse_assign_stmt();
	}
	else if (t.token_type == PRINT) //stmt --> print_stmt
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
		//st->type = IF_STMT;
		//struct IfStatement* ifNode = parse_if_stmt();
		//st->if_stmt = ifNode;
		//parse condition
		//set ifNode->condition_op
		//set ifNode->condition_operand1
		//set ifNode->condition_operand2
		//ifNode->true_branch = parse_body();
		//create no-op node
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

struct StatementNode* Parser::parse_assign_stmt()
{
	expect(ID);
	expect(EQUAL);
	Token t1 = lexer.GetToken(); //this will be primary, no matter what
	Token t2 = peek(); // get whatever is after primary
	if (t2.token_type == SEMICOLON) //assign_stmt --> ID EQUAL primary SEMICOLON
	{
		lexer.UngetToken(t1);
		parse_primary();
		expect(SEMICOLON);
	}
	else if (t2.token_type == PLUS || t2.token_type == MINUS || t2.token_type == MULT || t2.token_type == DIV) //assign_stmt --> ID EQUAL expr SEMICOLON
	{
		lexer.UngetToken(t1);
		/*parse_primary();
		parse_op();
		parse_primary();*/
		parse_expr();
		expect(SEMICOLON);
		
	}
}

struct StatementNode* Parser::parse_expr()
{
	//expr --> primary op primary
	parse_primary();
	parse_op();
	parse_primary();
}

struct StatementNode* Parser::parse_primary()
{
	//return ValueNode
	Token t = lexer.GetToken();
	if (t.token_type == ID || t.token_type == NUM)
	{
		//primary --> ID
		//primary --> NUM
	}
	else
	{
		syntax_error();
	}
}

struct StatementNode* Parser::parse_op()
{
	Token t = lexer.GetToken();
	if (t.token_type == PLUS)
	{
		//op --> PLUS
	}
	else if (t.token_type == MINUS)
	{
		//op --> MINUS
	}
	else if (t.token_type == MULT)
	{
		//op --> MULT
	}
	else if (t.token_type == DIV)
	{
		//op --> DIV
	}
	else
	{
		syntax_error();
	}
}

struct StatementNode* Parser::parse_print_stmt()
{
	//print_stmt --> print ID SEMICOLON
	expect(PRINT);
	expect(ID);
	expect(SEMICOLON);
}

struct StatementNode* Parser::parse_while_stmt()
{
	//while_stmt --> WHILE condition body
	expect(WHILE);
	parse_condition();
	parse_body();
}

struct StatementNode* Parser::parse_if_stmt()
{
	/*expect(IF);
	parse_condition();
	parse_body();*/
	struct StatementNode* st;
	expect(IF);
	//st->type = IF_STMT;
	//struct IfStatement ifNode;
	//st->if_stmt = ifNode;
	st = parse_condition();
	/*ifNode->condition_op;
	ifNode->condition_operand1;
	ifNode->conditione_operand2;*/
	st->if_stmt->true_branch = parse_body();

	
	struct StatementNode* noop = new StatementNode();
	noop->type = NOOP_STMT;
	struct StatmentNode* traverser = st->if_stmt->true_branch;
	while (traverser->next != NULL)
	{
		traverser = traverser->next;
	}
	traverser->next = noop;
	
	st->if_stmt->false_branch = noop;
	st->next = noop;

	return st;
	
}

struct StatementNode* Parser::parse_condition()
{
	/*parse_primary();
	parse_relop();
	parse_primary();*/
	
	struct StatementNode* st = new StatementNode();
	st->type = IF_STMT;
	st->if_stmt = new IfStatement();
	st->if_stmt->conditional_operand1 = parse_primary();
	st->if_stmt->conditional_op = parse_relop();
	st->if_stmt->conditional_operand2 = parse_primary();

	return st;
}

struct StatementNode* Parser::parse_relop()
{
	Token t = lexer.GetToken();
	if (t.token_type == GREATER)
	{
		//relop --> GREATER
	}
	else if (t.token_type == LESS)
	{
		//relop --> LESS
	}
	else if (t.token_type == NOTEQUAL)
	{
		//relop --> NOTEQUAL
	}
	else
	{
		syntax_error();
	}
}

struct StatementNode* Parser::parse_switch_stmt()
{
	//switch_stmt --> SWITCH ID LBRACE case_list RBRACE
	//switch_stmt --> SWITCH  ID LBRACE case_list default_case RBRACE
	expect(SWITCH);
	expect(ID);
	expect(LBRACE);
	parse_case_list();
	Token t = peek();
	if (t.token_type == DEFAULT)
	{
		parse_default_case();
		expect(RBRACE);
	}
	else if (t.token_type == RBRACE)
	{
		expect(RBRACE);
	}
	else
	{
		syntax_error();
	}
}

struct StatementNode* Parser:: parse_for_stmt()
{
	//for_stmt --> FOR LPAREN assign_stmt condition SEMICOLON assign_stmt RPAREN body
	expect(FOR);
	expect(LPAREN);
	parse_assign_stmt();
	parse_condition();
	expect(SEMICOLON);
	parse_assign_stmt();
	expect(RPAREN);
	parse_body();
}

struct StatementNode* Parser:: parse_case_list()
{
	//case_list --> case
	//case_list --> case case_list
	parse_case();
	Token t = peek();
	if (t.token_type == CASE)
	{
		parse_case_list();
	}
	else if (t.token_type == RBRACE || t.token_type == DEFAULT)
	{
		//case_list --> case
	}
	else
	{
		syntax_error();
	}
}

struct StatementNode* Parser:: parse_case()
{
	//case --> CASE NUM COLON body
	expect(CASE);
	expect(NUM);
	expect(COLON);
	parse_body();
}

struct StatementNode* Parser:: parse_default_case()
{
	//default_case --> DEFAULT COLON body
	expect(DEFAULT);
	expect(COLON);
	parse_body();
}


/*struct StatementNode* Parser::ParseInput()
{
	stuct StatementNode* program = parse_program();
	expect(END_OF_FILE);
	return program;
}*/

struct StatementNode* compiler::parse_generate_intermediate_representation()
{
	struct StatementNode program = parse_program();
	return program;
}




