#include "../include/country_lib.hpp"
#include <exception>

namespace mt {

    // ==================== CITY IMPLEMENTATION ====================

    City::City() : name_("Unknown"), population_(0), budget_(0.0) {
        std::cerr << "City default ctor" << std::endl;
    }

    City::City(std::string name, int population, double budget) :
        name_(name), population_(population), budget_(budget) {
        std::cerr << "City param ctor" << std::endl;
    }

    City::City(const City& other) :
        name_(other.name_), population_(other.population_), budget_(other.budget_) {
        std::cerr << "City copy ctor" << std::endl;
    }

    City::~City() {
        std::cerr << "City dtor" << std::endl;
    }

    void City::print_info() const {
        std::cout << "City: " << name_ << ", Population: " << population_
            << ", Budget: " << budget_ << std::endl;
    }

    // ==================== BUDGET IMPLEMENTATION ====================

    Budget::Budget() : money_(0.0), capital_coefficient_(1.0) {
        std::cerr << "Budget default ctor" << std::endl;
    }

    Budget::Budget(double money, double coeff) : money_(money), capital_coefficient_(coeff) {
        std::cerr << "Budget param ctor" << std::endl;
    }

    Budget::Budget(const Budget& other) :
        money_(other.money_), capital_coefficient_(other.capital_coefficient_) {
        std::cerr << "Budget copy ctor" << std::endl;
    }

    Budget::~Budget() {
        std::cerr << "Budget dtor" << std::endl;
    }

    double Budget::get_money() const { return money_; }
    double Budget::get_capital_coefficient() const { return capital_coefficient_; }

    void Budget::set_money(const std::string& money_str) {
        if (money_str.empty()) {
            throw std::string("The budget cannot be empty.");
        }

        std::string allowed_chars = "0123456789.";
        int dot_count = 0;

        for (size_t i = 0; i < money_str.length(); i++) {
            char c = money_str[i];

            if (allowed_chars.find(c) == std::string::npos) {
                std::string error = "The budget should contain only digits and one dot. Invalid character: ";
                error += c;
                throw error;
            }

            if (c == '.') {
                dot_count++;
                if (dot_count > 1) {
                    throw std::string("The budget cannot contain more than one dot.");
                }
            }
        }

        try {
            double money = std::stod(money_str);
            if (money < 0) {
                throw std::string("Budget cannot be negative");
            }
            money_ = money;
            std::cerr << "Budget changed to: " << money_ << std::endl;
        }
        catch (const std::exception& e) {
            throw std::string("Error converting budget to number: ") + e.what();
        }
    }

    void Budget::set_capital_coefficient(const std::string& coeff_str) {
        if (coeff_str.empty()) {
            throw std::string("The coefficient cannot be empty.");
        }

        std::string allowed_chars = "0123456789.";
        int dot_count = 0;

        for (size_t i = 0; i < coeff_str.length(); i++) {
            char c = coeff_str[i];

            if (allowed_chars.find(c) == std::string::npos) {
                std::string error = "The coefficient should contain only digits and one dot. Invalid character: ";
                error += c;
                throw error;
            }

            if (c == '.') {
                dot_count++;
                if (dot_count > 1) {
                    throw std::string("The coefficient cannot contain more than one dot.");
                }
            }
        }

        try {
            double coeff = std::stod(coeff_str);
            if (coeff < 0) {
                throw std::string("Coefficient cannot be negative");
            }
            capital_coefficient_ = coeff;
            std::cerr << "Capital coefficient changed to: " << capital_coefficient_ << std::endl;
        }
        catch (const std::exception& e) {
            throw std::string("Error converting coefficient to number: ") + e.what();
        }
    }

    void Budget::change_money(double amount) {
        money_ += amount;
        std::cerr << "Budget changed by " << amount << ", new money: " << money_ << std::endl;
    }

    void Budget::print_info() const {
        std::cout << "Budget: " << money_ << ", Capital coefficient: " << capital_coefficient_ << std::endl;
    }

} // namespace mt