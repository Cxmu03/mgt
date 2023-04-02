#include "lexer.hpp"
#include <iostream>

int main() {
    Lexer lexer("33.5e-4e-5");

    auto tokens = lexer.lex();

    for(auto token : tokens) {
        std::cout << token << std::endl;
    }
}
