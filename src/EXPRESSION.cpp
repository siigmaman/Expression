#include "EXPRESSION.h"
#include "NODE.h"
#include <complex>

namespace ExpressionLibrary {

    template <typename T>
    Expression<T>::Expression(T value) : root(std::make_shared<ConstNode<T>>(value)) {}

    template <typename T>
    Expression<T>::Expression(const std::string& variable) : root(std::make_shared<VarNode<T>>(variable)) {}

    template <typename T>
    Expression<T>::Expression(std::shared_ptr<Node<T>> node) : root(node) {}

    template <typename T>
    Expression<T>::Expression(const Expression& other) : root(other.root->clone()) {}

    template <typename T>
    Expression<T>::Expression(Expression&& other) noexcept : root(std::move(other.root)) {}

    template <typename T>
    Expression<T>& Expression<T>::operator=(const Expression& other) {
        if (this != &other) {
            root = other.root->clone();
        }
        return *this;
    }

    template <typename T>
    Expression<T>& Expression<T>::operator=(const Expression&& other) noexcept {
        if (this != &other) {
            root = std::move(other.root);
        }
        return *this;
    }

    template <typename T>
    Expression<T> Expression<T>::operator+(const Expression& other) const {
        return Expression(std::make_shared<AddNode<T>>(root, other.root));
    }

    template <typename T>
    Expression<T> Expression<T>::operator-(const Expression& other) const {
        return Expression(std::make_shared<SubtractNode<T>>(root, other.root));
    }

    template <typename T>
    Expression<T> Expression<T>::operator*(const Expression& other) const {
        return Expression(std::make_shared<MultiplyNode<T>>(root, other.root));
    }

    template <typename T>
    Expression<T> Expression<T>::operator/(const Expression& other) const {
        return Expression(std::make_shared<DivideNode<T>>(root, other.root));
    }

    template <typename T>
    Expression<T> Expression<T>::operator^(const Expression& other) const {
        return Expression(std::make_shared<PowerNode<T>>(root, other.root));
    }

    template <typename T>
    Expression<T> Expression<T>::sin() const {
        return Expression(std::make_shared<SinNode<T>>(root));
    }

    template <typename T>
    Expression<T> Expression<T>::cos() const {
        return Expression(std::make_shared<CosNode<T>>(root));
    }

    template <typename T>
    Expression<T> Expression<T>::ln() const {
        return Expression(std::make_shared<LnNode<T>>(root));
    }

    template <typename T>
    Expression<T> Expression<T>::exp() const {
        return Expression(std::make_shared<ExpNode<T>>(root));
    }

    template <typename T>
    std::string Expression<T>::ToString() const {
        return root->to_string();
    }

    template <typename T>
    Expression<T> Expression<T>::substitute(const std::string& variable, T value) const {
        return Expression(root->substitute(variable, value));
    }

    template <typename T>
    T Expression<T>::evaluate(const std::map<std::string, T>& variables) const {
        return root->evaluate(variables);
    }

    template <typename T>
    Expression<T> Expression<T>::differentiate(const std::string& variable) const {
        return Expression(root->differentiate(variable));
    }

    template class Expression<double>;
    template class Expression<std::complex<double>>;

} 