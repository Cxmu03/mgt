#include <string>
#include <vector>
#include <variant>

#include "token.hpp"

class Lexer {
public:
    Lexer(std::string input) : input_source(std::move(input)), current_char(input_source.data()) {}
    
public:
    std::vector<Token> lex();

private:
    Token consume_token();

    Token parse_number();
    Token parse_identifier();
    Token advance_with_token(TokenType type, TokenValue value);
    
    char peek();
    char current();
    char previous();
    void advance();

private:
    std::string input_source;
    char* current_char;
};
