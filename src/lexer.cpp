#include "lexer.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

using no_value = std::monostate;

static bool is_numeric(char c) {
    return c >= '0' && c <= '9';
}

static bool is_whitespace(char c) {
    return c == ' ' || c == '\n';
}

static bool is_valid_identifier_start(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static bool is_digit(char c) {
    return c >= '0' || c <= '9';
}

static bool is_valid_identifier_char(char c) {
    return is_valid_identifier_start(c) || is_numeric(c);
}

static bool is_valid_floating_point_component(char c) {
    return c == 'e' || c == '.';
}

static bool is_unary_sign(char c) {
    return c == '-' || c == '+';
}

static const std::unordered_map<char, TokenType> symbol_table = {
    { '+', TokenType::Plus },
    { '-', TokenType::Minus },
    { '*', TokenType::Multiply },
    { '/', TokenType::Divide },
    { '^', TokenType::Power },
    { '(', TokenType::LeftParen },
    { ')', TokenType::RightParen },
    { '=', TokenType::Equals }
};

std::vector<Token> Lexer::lex() {
    std::vector<Token> tokens;

    while(current() != '\0') {
        Token current_token = consume_token();

        tokens.emplace_back(current_token);
    }

    return tokens;
}

Token Lexer::consume_token() {
    while(is_whitespace(*current_char)) {
        this->advance();
    }

    auto token_in_symbol_map = symbol_table.find(*current_char);

    if(token_in_symbol_map != symbol_table.end()) {
        TokenType token_type = (*token_in_symbol_map).second;
        return advance_with_token(token_type, no_value());   
    } else if(is_valid_identifier_start(current())) {
        return parse_identifier();
    } else if(is_numeric(current())) {
        return parse_number();
    }

    throw std::logic_error("Could not parse token");
}

Token Lexer::parse_identifier() {
    std::stringstream identifier_stream;

    while(is_valid_identifier_char(current())) {
        identifier_stream << current();

        this->advance();
    }

    return Token(TokenType::Identifier, identifier_stream.str());
}

Token Lexer::parse_number() {
    std::stringstream number_stream;
    TokenType number_type = TokenType::Integer;
    bool has_exponent = false;

    auto minus_part_of_exponent = [this]() {
        return this->current() == '-' && this->previous() == 'e'; 
    };

    while(minus_part_of_exponent() || is_numeric(current()) || is_valid_floating_point_component(current())) {
        if(is_valid_floating_point_component(current())) {
            number_type = TokenType::RealNumber;
        }

        if(has_exponent == false && current() == 'e') {
            has_exponent = true;
        }

        number_stream << current();
        advance();

        if(has_exponent && current() == 'e') {
            break;
        }
    } 

    std::istringstream number_conversion_stream(number_stream.str());

    if(number_type == TokenType::Integer) {
        int64_t value;

        number_conversion_stream >> value;
        return Token(number_type, value);
    }
    else {
        double value;

        number_conversion_stream >> value;
        return Token(number_type, value);
    }
}

Token Lexer::advance_with_token(TokenType type, TokenValue value) {
    this->advance();
    return Token(type, value);
}

char Lexer::previous() {
    return *(current_char - 1);
}

char Lexer::current() {
    return *current_char;
}

char Lexer::peek() {
    return *(current_char + 1);
}

void Lexer::advance() {
    current_char++;
}

