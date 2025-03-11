#ifndef NODE_H
#define NODE_H

#include <memory>
#include <map>
#include <string>
#include <stdexcept>
#include <cmath>
#include <complex>
#include <sstream>

namespace ExpressionLibrary {

    template <typename T> struct ConstNode;
    template <typename T> struct VarNode;
    template <typename T> struct AddNode;
    template <typename T> struct MultiplyNode;
    template <typename T> struct SinNode;
    template <typename T> struct CosNode;
    template <typename T> struct SubtractNode;
    template <typename T> struct DivideNode;
    template <typename T> struct PowerNode;
    template <typename T> struct LnNode;
    template <typename T> struct ExpNode;
    template <typename T> struct NegateNode;

    template <typename T>
    struct Node {
        virtual ~Node() = default;
        virtual T evaluate(const std::map<std::string, T>& variables) const = 0;
        virtual std::string to_string() const = 0;
        virtual std::shared_ptr<Node<T>> clone() const = 0;
        virtual std::shared_ptr<Node<T>> differentiate(const std::string& variable) const = 0;
        virtual std::shared_ptr<Node<T>> substitute(const std::string& variable, const T& value) const = 0;
    };

    template <typename T>
    struct ConstNode : public Node<T> {
        T value;

        ConstNode(T value) : value(value) {}

        T evaluate(const std::map<std::string, T>&) const override {
            return value;
        }

        std::string to_string() const override {
            std::ostringstream oss;
            oss << value;
            return oss.str();
        }

        std::shared_ptr<Node<T>> clone() const override {
            return std::make_shared<ConstNode<T>>(value);
        }

        std::shared_ptr<Node<T>> differentiate(const std::string&) const override {
            return std::make_shared<ConstNode<T>>(0);
        }

        std::shared_ptr<Node<T>> substitute(const std::string&, const T&) const override {
            return std::make_shared<ConstNode<T>>(value);
        }
    };

    template <typename T>
    struct VarNode : public Node<T> {
        std::string name;

        VarNode(const std::string& name) : name(name) {}

        T evaluate(const std::map<std::string, T>& variables) const override {
            auto it = variables.find(name);
            if (it == variables.end()) {
                throw std::runtime_error("Variable " + name + " not found");
            }
            return it->second;
        }

        std::string to_string() const override {
            return name;
        }

        std::shared_ptr<Node<T>> clone() const override {
            return std::make_shared<VarNode<T>>(name);
        }

        std::shared_ptr<Node<T>> differentiate(const std::string& variable) const override {
            return std::make_shared<ConstNode<T>>(name == variable ? 1 : 0);
        }

        std::shared_ptr<Node<T>> substitute(const std::string& variable, const T& value) const override {
            if (name == variable) {
                return std::make_shared<ConstNode<T>>(value);
            }
            return std::make_shared<VarNode<T>>(name);
        }
    };

    template <typename T>
    struct AddNode : public Node<T> {
        std::shared_ptr<Node<T>> left, right;

        AddNode(std::shared_ptr<Node<T>> left, std::shared_ptr<Node<T>> right)
            : left(left), right(right) {}

        T evaluate(const std::map<std::string, T>& variables) const override {
            return left->evaluate(variables) + right->evaluate(variables);
        }

        std::string to_string() const override {
            return "(" + left->to_string() + " + " + right->to_string() + ")";
        }

        std::shared_ptr<Node<T>> clone() const override {
            return std::make_shared<AddNode<T>>(left->clone(), right->clone());
        }

        std::shared_ptr<Node<T>> differentiate(const std::string& variable) const override {
            return std::make_shared<AddNode<T>>(
                left->differentiate(variable),
                right->differentiate(variable)
            );
        }

        std::shared_ptr<Node<T>> substitute(const std::string& variable, const T& value) const override {
            return std::make_shared<AddNode<T>>(
                left->substitute(variable, value),
                right->substitute(variable, value)
            );
        }
    };

    template <typename T>
    struct MultiplyNode : public Node<T> {
        std::shared_ptr<Node<T>> left, right;

        MultiplyNode(std::shared_ptr<Node<T>> left, std::shared_ptr<Node<T>> right)
            : left(left), right(right) {}

        T evaluate(const std::map<std::string, T>& variables) const override {
            return left->evaluate(variables) * right->evaluate(variables);
        }

        std::string to_string() const override {
            return "(" + left->to_string() + " * " + right->to_string() + ")";
        }

        std::shared_ptr<Node<T>> clone() const override {
            return std::make_shared<MultiplyNode<T>>(left->clone(), right->clone());
        }

        std::shared_ptr<Node<T>> differentiate(const std::string& variable) const override {
            return std::make_shared<AddNode<T>>(
                std::make_shared<MultiplyNode<T>>(left->differentiate(variable), right->clone()),
                std::make_shared<MultiplyNode<T>>(left->clone(), right->differentiate(variable))
            );
        }

        std::shared_ptr<Node<T>> substitute(const std::string& variable, const T& value) const override {
            return std::make_shared<MultiplyNode<T>>(
                left->substitute(variable, value),
                right->substitute(variable, value)
            );
        }
    };

    template <typename T>
    struct SinNode : public Node<T> {
        std::shared_ptr<Node<T>> arg;

        SinNode(std::shared_ptr<Node<T>> arg) : arg(arg) {}

        T evaluate(const std::map<std::string, T>& variables) const override {
            return std::sin(arg->evaluate(variables));
        }

        std::string to_string() const override {
            return "sin(" + arg->to_string() + ")";
        }

        std::shared_ptr<Node<T>> clone() const override {
            return std::make_shared<SinNode<T>>(arg->clone());
        }

        std::shared_ptr<Node<T>> differentiate(const std::string& variable) const override {
            return std::make_shared<MultiplyNode<T>>(
                std::make_shared<CosNode<T>>(arg->clone()),
                arg->differentiate(variable)
            );
        }

        std::shared_ptr<Node<T>> substitute(const std::string& variable, const T& value) const override {
            return std::make_shared<SinNode<T>>(arg->substitute(variable, value));
        }
    };

    template <typename T>
    struct CosNode : public Node<T> {
        std::shared_ptr<Node<T>> arg;

        CosNode(std::shared_ptr<Node<T>> arg) : arg(arg) {}

        T evaluate(const std::map<std::string, T>& variables) const override {
            return std::cos(arg->evaluate(variables));
        }

        std::string to_string() const override {
            return "cos(" + arg->to_string() + ")";
        }

        std::shared_ptr<Node<T>> clone() const override {
            return std::make_shared<CosNode<T>>(arg->clone());
        }

        std::shared_ptr<Node<T>> differentiate(const std::string& variable) const override {
            return std::make_shared<MultiplyNode<T>>(
                std::make_shared<NegateNode<T>>(std::make_shared<SinNode<T>>(arg->clone())),
                arg->differentiate(variable)
            );
        }

        std::shared_ptr<Node<T>> substitute(const std::string& variable, const T& value) const override {
            return std::make_shared<CosNode<T>>(arg->substitute(variable, value));
        }
    };

    template <typename T>
    struct SubtractNode : public Node<T> {
        std::shared_ptr<Node<T>> left, right;

        SubtractNode(std::shared_ptr<Node<T>> left, std::shared_ptr<Node<T>> right)
            : left(left), right(right) {}

        T evaluate(const std::map<std::string, T>& variables) const override {
            return left->evaluate(variables) - right->evaluate(variables);
        }

        std::string to_string() const override {
            return "(" + left->to_string() + " - " + right->to_string() + ")";
        }

        std::shared_ptr<Node<T>> clone() const override {
            return std::make_shared<SubtractNode<T>>(left->clone(), right->clone());
        }

        std::shared_ptr<Node<T>> differentiate(const std::string& variable) const override {
            return std::make_shared<SubtractNode<T>>(
                left->differentiate(variable),
                right->differentiate(variable)
            );
        }

        std::shared_ptr<Node<T>> substitute(const std::string& variable, const T& value) const override {
            return std::make_shared<SubtractNode<T>>(
                left->substitute(variable, value),
                right->substitute(variable, value)
            );
        }
    };

    template <typename T>
    struct DivideNode : public Node<T> {
        std::shared_ptr<Node<T>> left, right;

        DivideNode(std::shared_ptr<Node<T>> left, std::shared_ptr<Node<T>> right)
            : left(left), right(right) {}

        T evaluate(const std::map<std::string, T>& variables) const override {
            return left->evaluate(variables) / right->evaluate(variables);
        }

        std::string to_string() const override {
            return "(" + left->to_string() + " / " + right->to_string() + ")";
        }

        std::shared_ptr<Node<T>> clone() const override {
            return std::make_shared<DivideNode<T>>(left->clone(), right->clone());
        }

        std::shared_ptr<Node<T>> differentiate(const std::string& variable) const override {
            return std::make_shared<DivideNode<T>>(
                std::make_shared<SubtractNode<T>>(
                    std::make_shared<MultiplyNode<T>>(left->differentiate(variable), right->clone()),
                    std::make_shared<MultiplyNode<T>>(left->clone(), right->differentiate(variable))
                ),
                std::make_shared<PowerNode<T>>(right->clone(), std::make_shared<ConstNode<T>>(2))
            );
        }

        std::shared_ptr<Node<T>> substitute(const std::string& variable, const T& value) const override {
            return std::make_shared<DivideNode<T>>(
                left->substitute(variable, value),
                right->substitute(variable, value)
            );
        }
    };

    template <typename T>
    struct PowerNode : public Node<T> {
        std::shared_ptr<Node<T>> base, exponent;

        PowerNode(std::shared_ptr<Node<T>> base, std::shared_ptr<Node<T>> exponent)
            : base(base), exponent(exponent) {}

        T evaluate(const std::map<std::string, T>& variables) const override {
            return std::pow(base->evaluate(variables), exponent->evaluate(variables));
        }

        std::string to_string() const override {
            return "(" + base->to_string() + " ^ " + exponent->to_string() + ")";
        }

        std::shared_ptr<Node<T>> clone() const override {
            return std::make_shared<PowerNode<T>>(base->clone(), exponent->clone());
        }

        std::shared_ptr<Node<T>> differentiate(const std::string& variable) const override {
            return std::make_shared<MultiplyNode<T>>(
                std::make_shared<MultiplyNode<T>>(
                    exponent->clone(),
                    std::make_shared<PowerNode<T>>(
                        base->clone(),
                        std::make_shared<SubtractNode<T>>(exponent->clone(), std::make_shared<ConstNode<T>>(1))
                    )
                ),
                base->differentiate(variable)
            );
        }

        std::shared_ptr<Node<T>> substitute(const std::string& variable, const T& value) const override {
            return std::make_shared<PowerNode<T>>(
                base->substitute(variable, value),
                exponent->substitute(variable, value)
            );
        }
    };

    template <typename T>
    struct LnNode : public Node<T> {
        std::shared_ptr<Node<T>> arg;

        LnNode(std::shared_ptr<Node<T>> arg) : arg(arg) {}

        T evaluate(const std::map<std::string, T>& variables) const override {
            return std::log(arg->evaluate(variables));
        }

        std::string to_string() const override {
            return "ln(" + arg->to_string() + ")";
        }

        std::shared_ptr<Node<T>> clone() const override {
            return std::make_shared<LnNode<T>>(arg->clone());
        }

        std::shared_ptr<Node<T>> differentiate(const std::string& variable) const override {
            return std::make_shared<DivideNode<T>>(
                arg->differentiate(variable),
                arg->clone()
            );
        }

        std::shared_ptr<Node<T>> substitute(const std::string& variable, const T& value) const override {
            return std::make_shared<LnNode<T>>(arg->substitute(variable, value));
        }
    };

    template <typename T>
    struct ExpNode : public Node<T> {
        std::shared_ptr<Node<T>> arg;

        ExpNode(std::shared_ptr<Node<T>> arg) : arg(arg) {}

        T evaluate(const std::map<std::string, T>& variables) const override {
            return std::exp(arg->evaluate(variables));
        }

        std::string to_string() const override {
            return "exp(" + arg->to_string() + ")";
        }

        std::shared_ptr<Node<T>> clone() const override {
            return std::make_shared<ExpNode<T>>(arg->clone());
        }

        std::shared_ptr<Node<T>> differentiate(const std::string& variable) const override {
            return std::make_shared<MultiplyNode<T>>(
                std::make_shared<ExpNode<T>>(arg->clone()),
                arg->differentiate(variable)
            );
        }

        std::shared_ptr<Node<T>> substitute(const std::string& variable, const T& value) const override {
            return std::make_shared<ExpNode<T>>(arg->substitute(variable, value));
        }
    };

    template <typename T>
    struct NegateNode : public Node<T> {
        std::shared_ptr<Node<T>> arg;

        NegateNode(std::shared_ptr<Node<T>> arg) : arg(arg) {}

        T evaluate(const std::map<std::string, T>& variables) const override {
            return -arg->evaluate(variables);
        }

        std::string to_string() const override {
            return "-(" + arg->to_string() + ")";
        }

        std::shared_ptr<Node<T>> clone() const override {
            return std::make_shared<NegateNode<T>>(arg->clone());
        }

        std::shared_ptr<Node<T>> differentiate(const std::string& variable) const override {
            return std::make_shared<NegateNode<T>>(arg->differentiate(variable));
        }

        std::shared_ptr<Node<T>> substitute(const std::string& variable, const T& value) const override {
            return std::make_shared<NegateNode<T>>(arg->substitute(variable, value));
        }
    };

}

#endif // NODE_H