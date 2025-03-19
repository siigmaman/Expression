#include <iostream>
#include <string>
#include <map>
#include <memory>
#include "EXPRESSION.h"
#include "NODE.h"

void printUsage() {
    std::cout << "Usage:\n"
              << "  differentiator --eval \"expression\" var1=value1 var2=value2 ...\n"
              << "  differentiator --diff \"expression\" --by var1\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printUsage();
        return 1;
    }

    std::string command = argv[1];

    if (command == "--eval") {
        std::string expression = argv[2];
        std::map<std::string, double> variables;

        for (int i = 3; i < argc; ++i) {
            std::string arg = argv[i];
            size_t pos = arg.find('=');
            if (pos == std::string::npos) {
                std::cerr << "Invalid variable format: " << arg << "\n";
                return 1;
            }
            std::string varName = arg.substr(0, pos);
            double varValue = std::stod(arg.substr(pos + 1));
            variables[varName] = varValue;
        }

        try {
            ExpressionLibrary::Parser<double> parser(expression);
            std::shared_ptr<ExpressionLibrary::Node<double>> root = parser.parse();

            double result = root->evaluate(variables);
            std::cout << "Result: " << result << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            return 1;
        }
    } else if (command == "--diff") {
        if (argc < 5 || std::string(argv[3]) != "--by") {
            printUsage();
            return 1;
        }

        std::string expression = argv[2];
        std::string varName = argv[4];

        try {
            ExpressionLibrary::Parser<double> parser(expression);
            std::shared_ptr<ExpressionLibrary::Node<double>> root = parser.parse();

            auto derivative = root->differentiate(varName);

            std::cout << "Derivative: " << derivative->to_string() << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            return 1;
        }
    } else {
        printUsage();
        return 1;
    }

    return 0;
}