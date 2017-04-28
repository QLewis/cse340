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
		//struct StatementNode* parse_generate_intermediate_representation();

};
