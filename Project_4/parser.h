//This parser is for project 4 and is based onff the parser creadted by Rida Bazzi in Project 3

#ifndef __PARSER_H__
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
	public:
		//struct StatementNode* parse_program();
		//parse_var_section();
		//parse_id_list();
		//struct StatementNode* parse_body();
		//struct StatementNode* parse_stmt_list();
		//struct StatementNode* parse_stmt();
		struct StatementNode* assign_stmt();	//-----------------DONE
		//------------   NOT DOING ----------------------     parse_expr();
		struct ValueNode* parse_primary();	//-----------------DONE
		//parse_op();
		//print_stmt();
		struct StatementNode* parse_while_stmt();	//---------DONE
		struct StatementNode* parse_if_stmt();	//-----------------DONE
		//parse_condition();
		Token parse_relop();	//---------------------------------DONE
		struct StatementNode* parse_switch_stmt();
		//parse_for_stmt();
		//parse_case_list();
		//parse_case();
		//parse_default_case();
};

struct variableList
{
	struct ValueNode* variable;
	struct ValueNode* next;
}
