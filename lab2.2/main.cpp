#include <iostream>
#include <string>
#include <vector>
#include "Country.hpp"

using str = std::string;
using strVec = std::vector<std::string>;


int main() {
    using namespace mt;
    std::cout << "Constructor calls at the start of main" << std::endl;
    strVec russiaCities = { "SaintPetersburg", "Novosibirsk", "Yekaterinburg" };
    Country russia{ "Russia", "Moscow", "826", 171251.0, russiaCities };
    Country russia1{ russia };
    Country russia2{};

    strVec citiesA = { "a", "b", "r" };
    Country A("A", "a", "1500", 150.0, citiesA);

    strVec citiesB = { "v", "b", "m" };
    Country B("B", "v", "1600", 100.0, citiesB);

    Country* current_country = &russia;
    Country* temp_country = nullptr;

    int choice;

    do {
        std::cout << "           COUNTRY DEMONSTRATION MENU" << std::endl;
        std::cout << "1.  Demonstrate operator + " << std::endl;
        std::cout << "2.  Demonstrate operator * " << std::endl;
        std::cout << "3.  Change country name" << std::endl;
        std::cout << "4.  Change capital" << std::endl;
        std::cout << "5.  Change date" << std::endl;
        std::cout << "6.  Change area" << std::endl;
        std::cout << "7.  Change cities list" << std::endl;
        std::cout << "8.  Show all getters" << std::endl;
        std::cout << "9.  Show country information" << std::endl;
        std::cout << "0.  Exit" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << "Enter your choice: ";

        std::cin >> choice;

        switch (choice) {
        case 1: {
            try {
                Country C = A + B;
                C.print_info();
            }
            catch (const str& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }

        case 2: {
            try {
                Country D = A * B;
                D.print_info();
            }
            catch (const str& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }

        case 3: {
            try {
                str new_name;
                std::cout << "Enter new name for " << current_country->get_name() << ": ";
                std::cin >> new_name;
                current_country->set_name(new_name);
                std::cout << "Name changed!" << std::endl;
            }
            catch (const str& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }

        case 4: {
            try {
                str new_capital;
                std::cout << "Enter new capital for " << current_country->get_name() << ": ";
                std::cin >> new_capital;
                current_country->set_capital(new_capital);
            }
            catch (const str& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }

        case 5: {
            try {
                str new_date;
                std::cout << "Enter new date for " << current_country->get_name() << ": ";
                std::cin >> new_date;
                current_country->set_date(new_date);
            }
            catch (const str& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }

        case 6: {
            try {
                double new_area;
                std::cout << "Enter new area for " << current_country->get_name() << ": ";
                std::cin >> new_area;
                current_country->set_area(new_area);
            }
            catch (const str& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }

        case 7: {
            try {
                strVec new_cities;
                std::cout << "Enter 3 city names:" << std::endl;

                for (int i = 0; i < 3; i++) {
                    str city;
                    std::cout << "Enter city " << (i + 1) << ": ";
                    std::cin >> city;
                    new_cities.push_back(city);
                }

                current_country->set_cities(new_cities);
                std::cout << "Cities list updated!" << std::endl;
            }
            catch (const str& error) {
                std::cerr << "Error: " << error << std::endl;
            }
            break;
        }

        case 8: {
            std::cout << "All getters for " << current_country->get_name() << std::endl;
            std::cout << "Name: " << current_country->get_name() << std::endl;
            std::cout << "Capital: " << current_country->get_capital() << std::endl;
            std::cout << "Date: " << current_country->get_date() << std::endl;
            std::cout << "Area: " << current_country->get_area() << std::endl;

            const strVec& cities = current_country->get_cities();
            std::cout << "Cities (" << cities.size() << "): ";
            if (cities.empty()) {
                std::cout << "none";
            }
            else {
                for (size_t i = 0; i < cities.size(); i++) {
                    std::cout << cities[i];
                    if (i < cities.size() - 1) std::cout << ", ";
                }
            }
            std::cout << std::endl;
            break;
        }

        case 9: {
            current_country->print_info();
            break;
        }

        case 0: {
            std::cout << "Exiting program" << std::endl;
            break;
        }

        default: {
            std::cout << "Invalid choice" << std::endl;
            break;
        }
        }

    } while (choice != 0);

    delete temp_country;

    return 0;
}

