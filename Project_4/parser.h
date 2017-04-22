//This parser is for project 4 and is based off the parser created by Rida Bazzi in Project 3

#ifndef _PARSER_H__
#define __PARSER_H__

#include <string>
#include "lexer.h"

class Parser{
  private:
	 LexicalAnalyzer lexer;

	void syntax_error();
	Token expect(TokenType expected_type);
	Token peek();

	struct StatementNode* parse_program();
	struct StatementNode* parse_var_section();
	struct StatementNode* parse_id_list();
	struct StatementNode* parse_body();
	struct StatementNode* parse_stmt_list();
	struct StatementNode* parse_stmt();
	struct StatementNode* parse_assign_stmt();
	struct StatementNode* parse_expr();
	struct StatementNode* parse_primary();
	struct StatementNode* parse_op();
	struct StatementNode* parse_print_stmt();
	struct StatementNode* parse_while_stmt();
	struct StatementNode* parse_if_stmt();
	struct StatementNode* parse_condition();
	struct StatementNode* parse_relop();
	struct StatementNode* parse_switch_stmt();
	struct StatementNode* parse_for_stmt();
	struct StatementNode* parse_case_list();
	struct StatementNode* parse_case();
	struct StatementNode* parse_default_case();

 public:
	void ParseInput();	
};

#endif


