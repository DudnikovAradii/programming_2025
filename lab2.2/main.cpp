#include <iostream>
#include <string>
#include <vector>
#include "Country.hpp"
#include <cstdlib> 
#include <ctime> 

using str = std::string;
using strVec = std::vector<std::string>;

int main() {
    using namespace mt;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "Constructor calls at the start of main " << std::endl;

    strVec russiaCities = { "SaintPetersburg", "Novosibirsk", "Yekaterinburg" };
    Country russia{ "Russia", "Moscow", 171251.0, russiaCities };

    Country russia1{ russia };

    Country russia2{};


    strVec citiesA = { "a", "b", "r" };
    Country A("A", "a", 150.0, citiesA);

    strVec citiesB = { "v", "b", "m" };
    Country B("B", "v", 100.0, citiesB);

    Country* current_country = nullptr;
    int country_choice;
    int choice = -1; 

    do {
        std::cout << "         COUNTRY DEMONSTRATION MENU" << std::endl;
        std::cout << "1.  Demonstrate operator + (A + B)" << std::endl;
        std::cout << "2.  Demonstrate operator * (A * B)" << std::endl;
        std::cout << "3.  Change country name" << std::endl;
        std::cout << "4.  Change capital" << std::endl;
        std::cout << "5.  Demonstrate operator += (A += B or B += A)" << std::endl;
        std::cout << "6.  Change area" << std::endl;
        std::cout << "7.  Change cities list" << std::endl;
        std::cout << "8.  Show all getters" << std::endl;
        std::cout << "9.  Show country information" << std::endl;
        std::cout << "0.  Exit" << std::endl;
        std::cout << "Current state:" << std::endl;
        std::cout << "  Country A: " << A.get_name() << " (capital: " << A.get_capital()
            << ", area: " << A.get_area() << ")" << std::endl;
        std::cout << "  Country B: " << B.get_name() << " (capital: " << B.get_capital()
            << ", area: " << B.get_area() << ")" << std::endl;
        std::cout << "Enter choice: ";

        std::cin >> choice;

        if (choice >= 3 && choice <= 9) {
            std::cout << "Select country to modify:" << std::endl;
            std::cout << "1. Country A" << std::endl;
            std::cout << "2. Country B" << std::endl;
            std::cin >> country_choice;

            if (country_choice == 1) {
                current_country = &A;
                std::cout << "Selected country: A" << std::endl;
            }
            else if (country_choice == 2) {
                current_country = &B;
                std::cout << "Selected country: B" << std::endl;
            }
            else {
                std::cout << "Invalid country choice!" << std::endl;
                continue;
            }
        }

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
                std::cout << "Select country to modify with += operation:" << std::endl;
                std::cout << "1. Country A (will do A += B)" << std::endl;
                std::cout << "2. Country B (will do B += A)" << std::endl;

                if (country_choice == 1) {
                    std::cout << " Before A += B " << std::endl;
                    A.print_info();

                    A += B;

                    std::cout << " After A += B " << std::endl;
                    A.print_info();
                }
                else if (country_choice == 2) {
                    std::cout << " Before B += A =" << std::endl;
                    B.print_info();

                    B += A;

                    std::cout << " After B += A " << std::endl;
                    B.print_info();
                }
                else {
                    std::cout << "Invalid choice!" << std::endl;
                }
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
                const strVec& current_cities = current_country->get_cities();

                if (current_cities.empty()) {
                    std::cout << "No cities available. You need to add cities first." << std::endl;
                    break;
                }

                std::cout << "Current cities of " << current_country->get_name() << ":" << std::endl;
                for (size_t i = 0; i < current_cities.size(); i++) {
                    std::cout << i + 1 << ". " << current_cities[i] << std::endl;
                }

                std::cout << "Select city number to change: ";
                size_t city_num;
                std::cin >> city_num;

                if (city_num < 1 || city_num > current_cities.size()) {
                    std::cout << "Invalid city number!" << std::endl;
                    break;
                }

                str new_city;
                std::cout << "Enter new name for city " << city_num << ": ";
                std::cin >> new_city;

                current_country->set_city_at_index(city_num - 1, new_city);

                std::cout << "City " << city_num << " changed successfully to '" << new_city << "'." << std::endl;

                std::cout << "Updated cities list:" << std::endl;
                const strVec& updated_cities = current_country->get_cities();
                for (size_t i = 0; i < updated_cities.size(); i++) {
                    std::cout << i + 1 << ". " << updated_cities[i] << std::endl;
                }
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

    return 0;
}