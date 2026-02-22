#pragma once
#include <string>
#include <iostream>

namespace mt {

    // ==================== STRUCT CITY ====================
    struct City {
        std::string name_;
        int population_;
        double budget_;

        City();
        City(std::string name, int population, double budget);
        City(const City& other);
        ~City();

        void print_info() const;
    };

    // ==================== CLASS BUDGET ====================
    class Budget {
    private:
        double money_;
        double capital_coefficient_;
    public:
        Budget();
        Budget(double money, double coeff);
        Budget(const Budget& other);
        ~Budget();

        double get_money() const;
        double get_capital_coefficient() const;

        void set_money(const std::string& money_str);
        void set_capital_coefficient(const std::string& coeff_str);

        void change_money(double amount = 10000.0);

        void print_info() const;
    };

} // namespace mt