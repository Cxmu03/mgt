#include <unordered_map>
#include <iostream>

#include "token.hpp"

struct TokenOutputVisitor {
    std::ostream& out;

    void operator()(auto value) {
        out << value;
    }

    void operator()(std::monostate) {
        out << "No Value";
    }
};

static const std::unordered_map<char, TokenType> token_from_char = {
    { '+', TokenType::Plus },
    { '-', TokenType::Minus },
    { '*', TokenType::Multiply },
    { '/', TokenType::Divide },
    { '(', TokenType::LeftParen },
    { ')', TokenType::RightParen },
    { '=', TokenType::Equals }
};

std::ostream& operator<<(std::ostream& out, const Token& token) {
    out << "Token<Type: ";
    out << h8::to_string(token.type);
    out << ", Value: ";

    std::visit(TokenOutputVisitor{out}, token.value);

    out << ">";

    return out;
}
