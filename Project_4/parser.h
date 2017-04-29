//This parser is for project 4 and is based onff the parser creadted by Rida Bazzi in Project 3

#ifndef _PARSER_H__
#define __PARSER_H__

#include <string>
#include "lexer.h"
#include "compiler.h"

class Parser{
	private:
		LexicalAnalyzer lexer;

		void syntax_error();
		Token expect(TokenType expected_type);
		Token peek();
		void parse_var_section();
		struct ValueNode* parse_id_list();
		struct StatementNode* parse_body();
		struct StatementNode* parse_stmt_list();
		struct StatementNode* parse_stmt();
		struct StatementNode* parse_assign_stmt();	//-----------------DONE
		//------------   NOT DOING ----------------------     parse_expr();
		struct ValueNode* parse_primary();	//-----------------DONE
		ArithmeticOperatorType parse_op();
		struct StatementNode* parse_print_stmt();	//-----------------DONE
		struct StatementNode* parse_while_stmt();	//---------DONE
		struct StatementNode* parse_if_stmt();	//-----------------DONE
		struct StatementNode* parse_condition();
		ConditionalOperatorType parse_relop();	//---------------------------------DONE
		struct StatementNode* parse_switch_stmt();
		struct StatementNode* parse_for_stmt();   //------- NEED TO FINISH
		struct StatementNode* parse_case_list();
		struct StatementNode* parse_case();
		struct StatementNode* parse_default_case();
	public:
		//struct StatementNode* parse_generate_intermediate_representation();
		struct StatementNode* parse_program();
		void add(struct ValueNode* value);
};

struct variableList
{
	struct ValueNode* variable;
	struct variableList* next;
};

#endif
