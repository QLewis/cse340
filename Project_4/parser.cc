//This is the parser for Project 4
//

#include <iostream>
#include <cstdlib>
#include "parser.h"
#include "compiler.h"

using namespace std;

struct variableList* variables = NULL; //global list of variables

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

void Parser::add(struct ValueNode* value)
{	
	/*
 * 	If variables is NULL, next item = variables
 * 	Else traverser to end, then add next item
 * 	*/
	if (variables == NULL)
	{
		variables->variable = value;
	}
	else
	{
		struct variableList* traverser = variables;
		while (traverser->next != NULL)
		{
			traverser = traverser->next;
		}
		traverser->next->variable = value;
	}
//	struct variableList* traverser = variables;
//	while(traverser->next != NULL)
//	{
//		traverser = traverser->next;
//	}
//	traverser->next->variable = value;
}

/***********      PARSING     *************/

struct StatementNode* Parser::parse_program()
{
	/*struct StatementNode* progSt = parse_var_section();
	progSt->next = parse_body();
	return progSt;*/

	parse_var_section();
	struct StatementNode* progSt = parse_body();
	return progSt;
}

void Parser::parse_var_section()
{
	parse_id_list();
	expect(SEMICOLON);
}

struct ValueNode* Parser::parse_id_list()
{
	//struct ValueNode* value = expect(ID);
	//Token id = expect(ID);
	Token id = lexer.GetToken();
	struct ValueNode* value = new ValueNode();
	value->name = id.lexeme;
	//value->value = 0;

	add(value);
	Token t = peek();
	if (t.token_type == COMMA)
	{
		expect(COMMA);
		struct ValueNode* value2 = parse_id_list();
	}
	else if (t.token_type == SEMICOLON)
	{
		//id_list --> ID
	}
	else
	{
		syntax_error();
	}
}

struct StatementNode* Parser::parse_body()
{
	//LBRACE stmt_list RBRACE
	expect(LBRACE);
	struct StatementNode* bodySt = parse_stmt_list();
	expect(RBRACE);

	return bodySt;
}


struct StatementNode* Parser::parse_stmt_list()
{
	//stmt stmt_list
	//stmt
	//struct stl = parse_stmt();
	struct StatementNode* stl = new StatementNode();
	stl = parse_stmt();

	Token t = peek();
	if (t.token_type == ID || t.token_type == PRINT || t.token_type == WHILE || t.token_type == IF || t.token_type == SWITCH || t.token_type == FOR)
	{
		struct StatementNode* stl2 = new StatementNode();
		stl2 = parse_stmt_list();
		//stl->next = stl2;
		if (t.token_type == IF || WHILE)
		{
			stl->next->next = stl2;
		}
		else
		{
			stl->next = stl2;
		}
	}
	return stl;
}

struct StatementNode* Parser::parse_stmt()
{
	struct StatementNode* st = new StatementNode();
	Token t = peek();

	if (t.token_type == ID)
	{
		st = parse_assign_stmt();
	}
	else if (t.token_type == PRINT)
	{
		st = parse_print_stmt();
	}
	else if (t.token_type == WHILE)
	{
		st = parse_while_stmt();
	}
	else if (t.token_type == IF)
	{
		st = parse_if_stmt();
	}
	else if (t.token_type == SWITCH)
	{
		st = parse_switch_stmt();
	}
	else if (t.token_type == FOR)
	{
		st = parse_for_stmt();
	}

	return st;
}

struct StatementNode* Parser::parse_assign_stmt()
{
	//expression on left_hand_side is evaluated
	//Result is stored in location associated w/right_hand side of expression
	// assign_stmt->ID EQUAL primary SEMICOLON
	// assign_stmt->ID EQUAL expr SEMICOLON
	
	struct StatementNode* asSt = new StatementNode();
	asSt->type = ASSIGN_STMT;
	asSt->assign_stmt = new AssignmentStatement();

	Token id = expect(ID);
	asSt->assign_stmt->left_hand_side = new ValueNode();
	asSt->assign_stmt->left_hand_side->name = id.lexeme;
	//asSt->assign_stmt->left_hand_side->value = 0;

	add(asSt->assign_stmt->left_hand_side);	//add new ValueNode to variable list

	expect(EQUAL);
	Token t1 = lexer.GetToken();
	Token t2 = peek();
	if(t2.token_type == SEMICOLON) // assign_stmt --> ID EQUAL primary SEMICOLON
	{
		//asSt->assign_stmt->op = parse_op();
		asSt->assign_stmt->op = OPERATOR_NONE;
		asSt->assign_stmt->operand2 = NULL;
		/*if (asSt->assign_stmt->op == OPERATOR_NONE)
		{
			asSt->assign_stmt->operand2 = NULL;
		}*/
		lexer.UngetToken(t1);
		asSt->assign_stmt->operand1 = parse_primary();
		add(asSt->assign_stmt->operand1);
		expect(SEMICOLON);
	}
	else if (t2.token_type == PLUS || t2.token_type == MINUS || t2.token_type == MULT || t2.token_type == DIV) //assign_stmt --> ID EQUAL expr SEMICOLON
	{
		lexer.UngetToken(t1);
		asSt->assign_stmt->operand1 = parse_primary();
		add(asSt->assign_stmt->operand1);
		asSt->assign_stmt->op = parse_op();
		/*if (t2.token_type == PLUS)
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
		}*/

		asSt->assign_stmt->operand2 = parse_primary();
		add(asSt->assign_stmt->operand2);

		expect(SEMICOLON);
	}
	return asSt;
}


//parse_expr

struct ValueNode* Parser::parse_primary()
{
	struct ValueNode* primary = new ValueNode();
	Token t = lexer.GetToken();
	if (t.token_type == ID || t.token_type == NUM)
	{
		primary->name = t.lexeme;
		//primary->value = 0;
	}
	else
	{
		syntax_error();
	}
	add(primary);
	return primary;
}

ArithmeticOperatorType Parser::parse_op()
{
	Token t = lexer.GetToken();
	//Token t = lexer.GetToken();
	if (t.token_type == PLUS)
	{
		return OPERATOR_PLUS;
	}
	else if (t.token_type == MINUS)
	{
		return OPERATOR_MINUS;
	}
	else if (t.token_type == MULT)
	{
		return OPERATOR_MULT;
	}
	else if (t.token_type == DIV)
	{
		return OPERATOR_DIV;
	}
	else
	{
		return OPERATOR_NONE;
	}
}
struct StatementNode* Parser::parse_print_stmt()
{
	/*struct StatementNode* printSt = new StatementNode();
	printSt->type = PRINT_STMT;
	printSt->print_stmt = new PrintStatement();
	
	struct variableList* traverser = variables;
	while (traverser->next != NULL)
	{
		traverser = traverser->next;
	} 

	printSt->print_stmt->id = traverser->variable;

	return printSt;*/

	expect(PRINT);
	struct StatementNode* printSt = new StatementNode();
	printSt->type = PRINT_STMT;
	printSt->print_stmt = new PrintStatement();

	Token id = expect(ID);
	expect(SEMICOLON);
	std::string name = id.lexeme;

	struct variableList*traverser = variables;
	while (traverser->next != NULL)
	{
		if (traverser->variable->name == id.lexeme)
		{
			printSt->print_stmt->id = traverser->variable;
		}
		traverser = traverser->next;
	}
	//expect print
	//expect id
	//expect semicolon
	//compare id with items in list
	//point print->id to valueNode in variable list
}


struct StatementNode* Parser::parse_while_stmt()
{
	//while_stmt --> WHILE condition body
	expect(WHILE);
	struct StatementNode* whileSt = new StatementNode();
	//whileSt->type = new IfStatement();
	whileSt = parse_condition();
	whileSt->if_stmt->true_branch = parse_body();
	
	struct StatementNode* gotoNode = new StatementNode();
	gotoNode->type = GOTO_STMT;
	gotoNode->goto_stmt = new GotoStatement();
	gotoNode->goto_stmt->target = whileSt;

	struct StatementNode* traverser = whileSt->if_stmt->true_branch;
	while (traverser->next != NULL)
	{
		traverser = traverser->next;
	}
	traverser->next = gotoNode;


	struct StatementNode* noop = new StatementNode();
	noop->type = NOOP_STMT;

	whileSt->if_stmt->false_branch = noop;
	whileSt->next = noop;

	return whileSt;
}





struct StatementNode* Parser::parse_if_stmt()
{
	//if_stmt --> IF condition body
	expect(IF);
	struct StatementNode* ifSt = parse_condition();

	ifSt->if_stmt->true_branch = parse_body();

	struct StatementNode* noop = new StatementNode();
	noop->type = NOOP_STMT;

	ifSt->if_stmt->false_branch = noop;

	struct StatementNode* traverser = ifSt->if_stmt->true_branch;
	while(traverser->next != NULL)
	{
		traverser = traverser->next;
	}
	traverser->next = noop;

	return ifSt;
}


struct StatementNode* Parser::parse_condition()
{
	//values in the locations assoc. w/ operands obtained
	//relational operator applied to these values
	//results in a true or false value
	
	struct StatementNode* condition = new StatementNode();
	condition->type = IF_STMT;
	condition->if_stmt = new IfStatement();
	condition->if_stmt->condition_operand1 = parse_primary();
	condition->if_stmt->condition_op = parse_relop();

	condition->if_stmt->condition_operand2 = parse_primary();

	return condition;
}

ConditionalOperatorType Parser::parse_relop()
{
	Token t = lexer.GetToken();
	if (t.token_type == GREATER)
        {
                return CONDITION_GREATER;
        }
        else if (t.token_type == LESS)
        {
                return CONDITION_LESS;
        }
        else if (t.token_type == NOTEQUAL)
        {
                return CONDITION_NOTEQUAL;
        }

	/*if (t.token_type == GREATER || t.token_type == LESS || t.token_type == NOTEQUAL)
	{
		return t;
	}
	else
	{
		syntax_error();
	}*/
}

//parse_switch
struct StatementNode* Parser::parse_switch_stmt()
{
	//SWITCH ID LBRACE case_list RBRACE
	//SWITCH ID LBRACE case_list default_case RBRACE
	expect(SWITCH);
	struct StatementNode* swiSt = new StatementNode();
	
	Token var = expect(ID);
	struct ValueNode* vari = new ValueNode();
	vari->name = var.lexeme;
	vari->value = 0;
	/*struct variableList* traverser = variables;
	while(traverser->next != NULL)
	{
		traverser = traverser->next;
	}
	traverser->next->variable = vari;*/
	add(vari);
	expect(LBRACE);

	swiSt = parse_case_list();
	Token t = peek();

	if (t.token_type == DEFAULT)
	{
		struct StatementNode* defSt = parse_default_case();
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

	struct StatementNode* noop = new StatementNode();
	noop->type = NOOP_STMT;

	struct StatementNode* gotoNode = new StatementNode();
	gotoNode->type = GOTO_STMT;
	gotoNode->goto_stmt = new GotoStatement();
	gotoNode->goto_stmt->target = noop;
}





struct StatementNode* Parser::parse_for_stmt()
{
	//FOR LPAREN assign_stmt condition SEMICOLON assign_stmt RPAREN body
	expect(FOR);
	expect(LPAREN);
	struct StatementNode* asSt1 = parse_assign_stmt();
	struct StatementNode* condition = parse_condition();
	asSt1->next = condition;
	expect(SEMICOLON);
	struct StatementNode* asSt2 = parse_assign_stmt();
	condition->next = asSt2;
	expect(RPAREN);
	struct StatementNode* boSt = parse_body();
	asSt2->next = boSt;
	
	struct StatementNode* noop = new StatementNode();
	noop->type = NOOP_STMT;

	boSt->next = noop;

	return asSt1;
	
}


struct StatementNode* Parser::parse_case_list()
{
	//case case_list
	//case
	struct StatementNode* caslSt = parse_case();
	Token t = peek();
	if (t.token_type == CASE)
	{
		struct StatementNode* caslSt2 = parse_case_list();
		caslSt->next = caslSt2;
	}
	else if (t.token_type == RBRACE || t.token_type == DEFAULT)
	{
		//case_list --> case
	}
	return caslSt;
}

struct StatementNode* Parser::parse_case()
{
	//case --> CASE NUM COLON body
	expect(CASE);
	struct StatementNode* caseSt = new StatementNode();
	caseSt->type = IF_STMT;
	caseSt->if_stmt = new IfStatement();
	Token id = expect(NUM);
	struct ValueNode* compare = new ValueNode();
	compare->name = id.lexeme;
	caseSt->if_stmt->condition_operand1 = compare;

	struct ValueNode* var =  new ValueNode();
	variableList* traverser = variables;
	while (traverser->next != NULL)
	{
		traverser = traverser->next;
	}
	caseSt->if_stmt->condition_operand2 = traverser->variable;
	caseSt->if_stmt->condition_op = CONDITION_NOTEQUAL;

	caseSt->if_stmt->true_branch->type = NOOP_STMT;
	expect(COLON);
	caseSt->if_stmt->false_branch = parse_body();
	
	return caseSt;
}
//
struct StatementNode* Parser::parse_default_case()
{
	expect(DEFAULT);
	expect(COLON);
	struct StatementNode* defSt = parse_body();
	return defSt;
}	

struct StatementNode* parse_generate_intermediate_representation()
{
	Parser parser; //create a parser object
	struct StatementNode* input = parser.parse_program();
	return input;
}


