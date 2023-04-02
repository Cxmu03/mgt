#include <string>
#include <variant>

#include "h8.hpp"

using namespace h8::literals;

class ostream;

enum TokenType {
    Identifier = "Name"_h8,
    Integer = "Int"_h8,
    RealNumber = "Real"_h8,
    LeftParen = "LParen"_h8,
    RightParen = "RParen"_h8,
    Plus = "Plus"_h8,
    Minus = "Minus"_h8,
    Divide = "Divide"_h8,
    Multiply = "Multiply"_h8,
    Power = "Power"_h8,
    Equals = "Equals"_h8
};

using TokenValue = std::variant<int64_t, double, std::string, std::monostate>;

struct Token {
    TokenType type;
    TokenValue value;
    
    template <typename Value>
    Token(TokenType type, Value value) : type(type), value(value) {}

    Token(const Token& other) = default;

};

std::ostream& operator <<(std::ostream& out, const Token& token); 
