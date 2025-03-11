#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <cmath>
#include <algorithm>
#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include <cctype>
#include <vector>
#include <complex>
#include "NODE.h"

namespace ExpressionLibrary{

    template <typename T>
    struct Node;

    template <typename T>
    class Expression{
    private:
        std::shared_ptr<Node<T>> root;

        Expression(std::shared_ptr<Node<T>> node);
        
    public:
        Expression(T value);
        Expression(const std::string& value);

        Expression(const Expression& other);
        Expression(Expression&& other) noexcept;

        Expression& operator=(const Expression& other);
        Expression& operator=(const Expression&& other) noexcept;


        Expression operator+(const Expression& other) const;
        Expression operator-(const Expression& other) const;
        Expression operator*(const Expression& other) const;
        Expression operator/(const Expression& other) const;
        Expression operator^(const Expression& other) const;

        Expression sin() const;
        Expression cos() const;
        Expression ln() const;
        Expression exp() const;

        std::string ToString() const;

        Expression substitute(const std::string& variable, T value) const;

        T evaluate(const std::map<std::string, T>& variables) const;

        Expression differentiate(const std::string& variable) const;
        
        static Expression Parse(const std::string& s);
    };

    enum class TokenType {
        Number,
        Variable,
        Function,
        Operator,
        LeftParen,
        RightParen,
        End
    };

    struct Token {
        TokenType type;
        std::string value;
    };

    class Lexer {
    private:
        std::string input;
        size_t pos;

        char currentChar() const {
            return (pos < input.size()) ? input[pos] : '\0';
        }

        void advance() {
            if (pos < input.size()) ++pos;
        }

        void skipWhitespace() {
            while (std::isspace(currentChar())) advance();
        }

        std::string readNumber() {
            std::string result;
            bool hasDecimal = false;
            while (std::isdigit(currentChar()) || currentChar() == '.') {
                if (currentChar() == '.') {
                    if (hasDecimal) break;
                    hasDecimal = true;
                }
                result += currentChar();
                advance();
            }
            return result;
        }

        std::string readIdentifier() {
            std::string result;
            while (std::isalnum(currentChar()) || currentChar() == '_') {
                result += currentChar();
                advance();
            }
            return result;
        }

    public:
        Lexer(const std::string& input) : input(input), pos(0) {}

        Token nextToken() {
            skipWhitespace();
            if (pos >= input.size()) return {TokenType::End, ""};

            char c = currentChar();

            if (std::isdigit(c) || c == '.') {
                return {TokenType::Number, readNumber()};
            } else if (std::isalpha(c)) {
                std::string id = readIdentifier();
                if (currentChar() == '(') {
                    return {TokenType::Function, id};
                } else {
                    return {TokenType::Variable, id};
                }
            } else if (c == '(') {
                advance();
                return {TokenType::LeftParen, "("};
            } else if (c == ')') {
                advance();
                return {TokenType::RightParen, ")"};
            } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
                advance();
                return {TokenType::Operator, std::string(1, c)};
            } else {
                throw std::runtime_error("Unexpected character: " + std::string(1, c));
            }
        }
    };

    template <typename T>
    class Parser {
    private:
        Lexer lexer;
        Token currentToken;

        void advance() {
            currentToken = lexer.nextToken();
        }

        std::shared_ptr<Node<T>> parseExpression() {
            auto left = parseTerm();
            while (currentToken.type == TokenType::Operator &&
                  (currentToken.value == "+" || currentToken.value == "-")) {
                std::string op = currentToken.value;
                advance();
                auto right = parseTerm();
                if (op == "+") {
                    left = std::make_shared<AddNode<T>>(left, right);
                } else {
                    left = std::make_shared<SubtractNode<T>>(left, right);
                }
            }
            return left;
        }

        std::shared_ptr<Node<T>> parseTerm() {
            auto left = parseFactor();
            while (currentToken.type == TokenType::Operator &&
                  (currentToken.value == "*" || currentToken.value == "/")) {
                std::string op = currentToken.value;
                advance();
                auto right = parseFactor();
                if (op == "*") {
                    left = std::make_shared<MultiplyNode<T>>(left, right);
                } else {
                    left = std::make_shared<DivideNode<T>>(left, right);
                }
            }
            return left;
        }

        std::shared_ptr<Node<T>> parseFactor() {
            auto left = parsePower();
            if (currentToken.type == TokenType::Operator && currentToken.value == "^") {
                advance();
                auto right = parseFactor();
                return std::make_shared<PowerNode<T>>(left, right);
            }
            return left;
        }

        std::shared_ptr<Node<T>> parsePower() {
            return parsePrimary();
        }

        std::shared_ptr<Node<T>> parsePrimary() {
            Token token = currentToken;
            if (token.type == TokenType::Number) {
                advance();
                T value = T(0);
                if constexpr (std::is_arithmetic_v<T>) {
                    value = static_cast<T>(std::stod(token.value));
                } else {
                    throw std::runtime_error("Complex number parsing not implemented");
                }
                return std::make_shared<ConstNode<T>>(value);
            } else if (token.type == TokenType::Variable) {
                std::string varName = token.value;
                advance();
                return std::make_shared<VarNode<T>>(varName);
            } else if (token.type == TokenType::Function) {
                std::string funcName = token.value;
                advance(); 
                advance(); 
                auto arg = parseExpression();
                if (currentToken.type != TokenType::RightParen) {
                    throw std::runtime_error("Expected ')' after function argument");
                }
                advance(); 
                if (funcName == "sin") {
                    return std::make_shared<SinNode<T>>(arg);
                } else if (funcName == "cos") {
                    return std::make_shared<CosNode<T>>(arg);
                } else if (funcName == "ln") {
                    return std::make_shared<LnNode<T>>(arg);
                } else if (funcName == "exp") {
                    return std::make_shared<ExpNode<T>>(arg);
                } else {
                    throw std::runtime_error("Unknown function: " + funcName);
                }
            } else if (token.type == TokenType::LeftParen) {
                advance();
                auto expr = parseExpression();
                if (currentToken.type != TokenType::RightParen) {
                    throw std::runtime_error("Expected ')'");
                }
                advance();
                return expr;
            } else if (token.type == TokenType::Operator && token.value == "-") {
                advance();
                auto expr = parsePrimary();
                return std::make_shared<NegateNode<T>>(expr);
            } else {
                throw std::runtime_error("Unexpected token");
            }
        }

    public:
        Parser(const std::string& input) : lexer(input) {
            advance();
        }

        std::shared_ptr<Node<T>> parse() {
            return parseExpression();
        }
    };

    template <typename T>
    Expression<T> Expression<T>::Parse(const std::string& s) {
        Parser<T> parser(s);
        return Expression<T>(parser.parse());
    }
}

#endif //EXPRESSION_HPP