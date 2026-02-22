#include <iostream>
#include <string>
#include <vector>
#include "Country.hpp"
#include <cstdlib> 
#include <ctime> 
#include "include/country_lib.hpp"
using str = std::string;

void print_lab_rating() {
    std::cout << "LABORATORY WORK RATING: " << std::endl;
    std::cout << "Interest: 9/10 - Very interesting to work with budget distribution" << std::endl;
    std::cout << "Content: 10/10 - All requirements fulfilled: library, new classes" << std::endl;
    std::cout << "Difficulty: 8/10 - Difficult but interesting" << std::endl;
}

int main() {
    using namespace mt;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<City> russia_cities = {
        City("Moscow", 12000, 0.0),
        City("SaintPetersburg", 5000, 0.0),
        City("Novosibirsk", 1500, 0.0),
        City("Yekaterinburg", 1400, 0.0)
    };

    std::vector<City> belarus_cities = {
        City("Minsk", 2000, 0.0),
        City("Brest", 3500, 0.0),
        City("Gomel", 5000, 0.0)
    };

    Country russia("Russia", "Moscow", 1990, 171251.0, 146000, russia_cities);
    Country belarus("Belarus", "Minsk", 1990, 20760.0, 9400, belarus_cities);

    Budget state_budget(100000.0, 1.5);

    Country* current_country = nullptr;
    int country_choice;
    int choice = -1;

    do {
        std::cout << "CURRENT STATE:" << std::endl;
        std::cout << "  Country A: " << russia.get_name()
            << " (capital: " << russia.get_capital()
            << ", population: " << russia.get_population() << ")" << std::endl;
        std::cout << "  Country B: " << belarus.get_name()
            << " (capital: " << belarus.get_capital()
            << ", population: " << belarus.get_population() << ")" << std::endl;
        std::cout << "  Budget: " << state_budget.get_money()
            << ", capital coefficient: " << state_budget.get_capital_coefficient() << std::endl;

        std::cout << " ===MENU=== " << std::endl;
        std::cout << "1.  Demonstrate operator + (A + B)" << std::endl;
        std::cout << "2.  Demonstrate operator * (A * B)" << std::endl;
        std::cout << "3.  Demonstrate operator += (A += B or B += A)" << std::endl;
        std::cout << "4.  Show country getters" << std::endl;
        std::cout << "5.  Change country name" << std::endl;
        std::cout << "6.  Change capital" << std::endl;
        std::cout << "7.  Change foundation date" << std::endl;
        std::cout << "8.  Change area" << std::endl;
        std::cout << "9.  Change total population" << std::endl;
        std::cout << "10. Change city population" << std::endl;
        std::cout << "11. Show country information" << std::endl;
        std::cout << "12. Show city information" << std::endl;
        std::cout << "13. Demonstrate budget work" << std::endl;
        std::cout << "14. Change budget" << std::endl;
        std::cout << "15. Distribute budget to cities" << std::endl;
        std::cout << "16. Show laboratory work rating" << std::endl;
        std::cout << "17. Increase budget by 10000" << std::endl;
        std::cout << "0.  Exit" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> choice;

        if (choice >= 4 && choice <= 12 && choice != 1 && choice != 2 && choice != 3 && choice != 13 && choice != 14 && choice != 15 && choice != 16 && choice != 17) {
            std::cout << "Select country:" << std::endl;
            std::cout << "1. Country A (Russia)" << std::endl;
            std::cout << "2. Country B (Belarus)" << std::endl;

            try {
                std::cin >> country_choice;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    throw "Error: Please enter a number, not letters!";
                }
                if (country_choice != 1 && country_choice != 2) {
                    throw "Error: Invalid country choice! Please enter 1 or 2.";
                }

                if (country_choice == 1) {
                    current_country = &russia;
                    std::cout << "Selected country: Russia" << std::endl;
                }
                else if (country_choice == 2) {
                    current_country = &belarus;
                    std::cout << "Selected country: Belarus" << std::endl;
                }
            }
            catch (const char* msg) {
                std::cout << msg << std::endl;
                continue;
            }
        }

        switch (choice) {
        case 1: {
            std::cout << "===Operator + (A + B)===" << std::endl;
            try {
                Country C = russia + belarus;
                C.print_info();
            }
            catch (const str& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }

        case 2: {
            std::cout << "=== Operator * (A * B) ===" << std::endl;
            try {
                Country D = russia * belarus;
                D.print_info();
            }
            catch (const str& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }

        case 3: {
            std::cout << "\n=== Operator += ===" << std::endl;
            std::cout << "Select operation:" << std::endl;
            std::cout << "1. A += B (Russia += Belarus)" << std::endl;
            std::cout << "2. B += A (Belarus += Russia)" << std::endl;
            int op_choice;
            std::cin >> op_choice;

            try {
                if (op_choice == 1) {
                    std::cout << "Before A += B:" << std::endl;
                    russia.print_info();
                    russia += belarus;
                    std::cout << "After A += B:" << std::endl;
                    russia.print_info();
                }
                else if (op_choice == 2) {
                    std::cout << "Before B += A:" << std::endl;
                    belarus.print_info();
                    belarus += russia;
                    std::cout << "After B += A:" << std::endl;
                    belarus.print_info();
                }
            }
            catch (const str& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }

        case 4: {
            std::cout << "=== Getters for " << current_country->get_name() << " ===" << std::endl;
            std::cout << "Name: " << current_country->get_name() << std::endl;
            std::cout << "Capital: " << current_country->get_capital() << std::endl;
            std::cout << "Foundation date: " << current_country->get_foundation_date() << std::endl;
            std::cout << "Area: " << current_country->get_area() << std::endl;
            std::cout << "Population: " << current_country->get_population() << std::endl;
            std::cout << "Total city population: " << current_country->get_total_population() << std::endl;

            const std::vector<City>& cities = current_country->get_cities();
            std::cout << "Cities (" << cities.size() << "):" << std::endl;
            for (size_t i = 0; i < cities.size(); i++) {
                std::cout << "  " << i + 1 << ". " << cities[i].name_
                    << " (pop: " << cities[i].population_ << ")" << std::endl;
            }
            break;
        }

        case 5: {
            std::cout << "=== Change name ===" << std::endl;
            try {
                str new_name;
                std::cout << "Enter new name for " << current_country->get_name() << ": ";
                std::cin >> new_name;
                current_country->set_name(new_name);
                std::cout << "Name successfully changed!" << std::endl;
            }
            catch (const str& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }

        case 6: {
            std::cout << "=== Change capital ===" << std::endl;
            try {
                str new_capital;
                std::cout << "Enter new capital for " << current_country->get_name() << ": ";
                std::cin >> new_capital;
                current_country->set_capital(new_capital);
                std::cout << "Capital successfully changed!" << std::endl;
            }
            catch (const str& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }

        case 7: {
            std::cout << "=== Change foundation date ===" << std::endl;
            try {
                int new_date;
                std::cout << "Enter new foundation date: ";
                std::cin >> new_date;
                current_country->set_foundation_date(new_date);
                std::cout << "Foundation date successfully changed!" << std::endl;
            }
            catch (const str& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }

        case 8: {
            std::cout << "=== Change area ===" << std::endl;
            try {
                double new_area;
                std::cout << "Enter new area for " << current_country->get_name() << ": ";
                std::cin >> new_area;
                current_country->set_area(new_area);
                std::cout << "Area successfully changed!" << std::endl;
            }
            catch (const str& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }

        case 9: {
            std::cout << "=== Change total population ===" << std::endl;
            try {
                int new_population;
                std::cout << "Enter new population for " << current_country->get_name() << ": ";
                std::cin >> new_population;
                current_country->set_population(new_population);
                std::cout << "Population successfully changed!" << std::endl;
            }
            catch (const str& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }

        case 10: {
            std::cout << "=== Change city population ===" << std::endl;
            try {
                const std::vector<City>& cities = current_country->get_cities();

                if (cities.empty()) {
                    std::cout << "No cities to change!" << std::endl;
                    break;
                }

                std::cout << "Cities of " << current_country->get_name() << ":" << std::endl;
                for (size_t i = 0; i < cities.size(); i++) {
                    std::cout << i + 1 << ". " << cities[i].name_
                        << " (population: " << cities[i].population_ << ")" << std::endl;
                }

                std::cout << "Select city number: ";
                size_t city_num;
                std::cin >> city_num;

                if (city_num < 1 || city_num > cities.size()) {
                    std::cout << "Invalid city number!" << std::endl;
                    break;
                }

                int new_population;
                std::cout << "Enter new population for city " << cities[city_num - 1].name_ << ": ";
                std::cin >> new_population;

                current_country->set_city_population(cities[city_num - 1].name_, new_population);
                std::cout << "City population successfully changed!" << std::endl;
            }
            catch (const str& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }

        case 11: {
            std::cout << "=== Country information ===" << std::endl;
            current_country->print_info();
            break;
        }

        case 12: {
            std::cout << "=== City information ===" << std::endl;
            try {
                const std::vector<City>& cities = current_country->get_cities();

                if (cities.empty()) {
                    std::cout << "No cities to display!" << std::endl;
                    break;
                }

                std::cout << "Cities of " << current_country->get_name() << ":" << std::endl;
                for (size_t i = 0; i < cities.size(); i++) {
                    std::cout << i + 1 << ". " << cities[i].name_ << std::endl;
                }

                std::cout << "Select city number: ";
                size_t city_num;
                std::cin >> city_num;

                if (city_num < 1 || city_num > cities.size()) {
                    std::cout << "Invalid city number!" << std::endl;
                    break;
                }

                City city = current_country->get_city_by_name(cities[city_num - 1].name_);
                city.print_info();
            }
            catch (const str& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }

        case 13: {
            std::cout << "=== Budget demonstration ===" << std::endl;
            std::cout << "Current budget: ";
            state_budget.print_info();
            break;
        }

        case 14: {
            std::cout << "=== Change budget ===" << std::endl;
            try {
                std::string new_money_str;
                std::cout << "Enter new budget amount (only digits and one dot allowed): ";
                std::cin >> new_money_str;
                state_budget.set_money(new_money_str);

                std::string new_coeff_str;
                std::cout << "Enter new capital coefficient (only digits and one dot allowed): ";
                std::cin >> new_coeff_str;
                state_budget.set_capital_coefficient(new_coeff_str);

                std::cout << "Budget successfully changed!" << std::endl;
                state_budget.print_info();
            }
            catch (const std::string& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }

        case 15: {
            std::cout << "=== Distribute budget ===" << std::endl;
            std::cout << "Select country for budget distribution:" << std::endl;
            std::cout << "1. Russia" << std::endl;
            std::cout << "2. Belarus" << std::endl;
            int distr_choice;
            std::cin >> distr_choice;

            try {
                if (distr_choice == 1) {
                    std::cout << "Budget distribution to Russian cities:" << std::endl;
                    russia.distribute_budget(state_budget);
                    russia.print_info();
                }
                else if (distr_choice == 2) {
                    std::cout << "Budget distribution to Belarusian cities:" << std::endl;
                    belarus.distribute_budget(state_budget);
                    belarus.print_info();
                }
            }
            catch (const str& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }
        case 16: {
            print_lab_rating();
            break;
        }

        case 17: {
            std::cout << "=== Increase budget by 10000 ===" << std::endl;
            state_budget.change_money(); 
            state_budget.print_info();
            break;
        }

        case 0: {
            std::cout << "Exiting program. Goodbye!" << std::endl;
            break;
        }

        default: {
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
        }

    } while (choice != 0);

    return 0;
}