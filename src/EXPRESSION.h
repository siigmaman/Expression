#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <math.h>
#include <algorithm>
#include <string>
#include <map>
#include <memory>
#include <stdexcept>

namespace ExpressionLibrary{

    template <typename T>
    struct Node;

    template <typename T>
    class Expression{
    private:
        std::shared_ptr<Node> root;

        Expression(std::shared_ptr<Node> node);
        
    public:
        Expression(T value);
        Expression(double value);
        Expression(const std::string& value);

        Expression(const Expression& other);
        Expression(Expression&& other) noexcept;

        Expression& operator=(const Expression& other);
        Expression& operator=(const Expression&& other) noexcept;

        ~Expression();

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

    };
}

#endif //EXPRESSION_HPP