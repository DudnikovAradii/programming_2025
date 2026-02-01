#include <iostream>
#include <string>
#include <limits>
#include <random> 
#include <ctime>   

// Поля: название, столица, дата основания, площадь, население.
// Методы: геттеры на все, сеттер на столицу, вывод всей информации, присоединение новой территории, рост населения.
using str = std::string;

class Country {
private:
    str name_;                  //
    str capital_;               //
    double area_;               //
    long long population_;
protected:
    str date_;                  //
public:
    Country() {
        name_ = "unknown";
        capital_ = "unknown";
        date_ = "unknown";
        area_ = 0;
        population_ = 0;
        std::cerr << "ctor default" << std::endl;
    }

    Country(str name, str capital, str date, double area, long long population) : 
        name_(name), capital_(capital), date_(date), area_(area), population_(population) {
        std::cerr << "ctor param" << std::endl;
    }
    Country(const Country &c) : name_(c.name_), capital_(c.capital_), date_(c.date_), area_(c.area_), population_(c.population_) {
        std::cerr << "ctor copy" << std::endl;
    }
    ~Country() {
        std::cerr << "dtor" << std::endl;
    }

    void set_capital(str capital) {
        if (capital.empty()) {
            str error = "The capital's name cannot be empty";
            throw error;
        }
        str uppercase_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        str allowed_chars = "abcdefghijklmnopqrstuvwxyz";

        if (uppercase_letters.find(capital[0]) == std::string::npos) {
            str error = "Capital name must start with an uppercase letter";
            throw error;
        }

        for (int i = 1; i < capital.length(); i++) {
            char c = capital[i];
            if (allowed_chars.find(c) == std::string::npos) {
                str error = "The capital should be without numbers, spaces, punctuation marks and capital letters.";
                throw error;
            }
        }

        capital_ = capital;
        std::cerr << "Capital changed to: " << capital_ << std::endl;

    }

    str get_name() const { return name_; }
    str get_capital() const { return capital_; }
    str get_date() const { return date_; }
    double get_area_() const { return area_; }
    long long get_population() const { return population_; }

    void add_territory(double add_area) {
        if (add_area <= 0) {
            str error = "The added area must be > 0";
            throw error;
        }
        double old_area = area_;
        area_ += add_area;
        std::cerr << "The territory is annexed!" << std::endl;
        std::cerr << "Old Square: " << old_area << std::endl;
        std::cerr << "Added: " << add_area << std::endl;
        std::cerr << "New area: " << area_ << std::endl;
    }

    void gros_population() {
        // std::srand(std::time(NULL));  
        long long old_population = population_;
        size_t random = 1000;
        population_ += random;
        std::cout << "The population grew by: " << random  << std::endl;
        std::cout << "Old population: " << old_population << std::endl;
        std::cout << "Current Population: " << population_ << std::endl;
    }

    void print_info() {
        std::cout << "Country information: " << std::endl;
        std::cerr << "Name: " << name_ << std::endl;
        std::cerr << "Capital: " << capital_ << std::endl;
        std::cerr << "Date: " << date_ << std::endl;
        std::cerr << "Area: " << area_ << std::endl;
        std::cerr << "Population: " << population_ << std::endl;
    }
// Setteri kotorie ne vhodiat v zadanie varianta
    void set_name(str name) {
        if (name.empty()) {
            str error = "The name cannot be empty.";
            throw error;
        }
        str uppercase_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        str allowed_chars = "abcdefghijklmnopqrstuvwxyz";

        if (uppercase_letters.find(name[0]) == std::string::npos) {
            str error = "Name must start with an uppercase letter";
            throw error;
        }

        for (int i = 1; i < name.length(); i++) {
            char c = name[i];
            if (allowed_chars.find(c) == std::string::npos) {
                str error = "The name should be without numbers, spaces, punctuation marks and capital letters.";
                throw error;
            }
        }

        name_ = name;
        std::cerr << "Name changed to: " << name_ << std::endl;

    }

    void set_date(str date) {
        str digits = "0123456789";
        for (int i = 0; i < date.length(); i++) {
            if (digits.find(date[i]) == std::string::npos) {
                str error = "The date can contain only numbers.";
                throw error;
            }
        }
        date_ = date;
        std::cerr << "Date after change: " << date_ << std::endl;
        
    }

    void set_area(double area) {
        if (area < 0) {
            str error = "Area cannot be negative";
            throw error;
        }
        area_ = area;
        std::cerr << "Area after change: " << area_ << std::endl;
    }

    void set_population(long long population) {
        if (population < 0) {
            str error = "Population cannot be negative";
            throw error;
        }
        population_ = population;
        std::cerr << "Population after change: " << population_ << std::endl;
    }

};
int main() {
    Country russia{ "Russia", "Moscow", "826 year", 171251.0, 1464472 };
    Country russia1{ russia };
    Country russia2{};
    russia2.print_info();
    int choice;
    do {
        std::cout << "\n=============" << std::endl;
        std::cout << "Country management menu:" << std::endl;
        std::cout << "1. Get a name" << std::endl;
        std::cout << "2. Get the capital" << std::endl;
        std::cout << "3. Get the founding date" << std::endl;
        std::cout << "4. Get the area" << std::endl;
        std::cout << "5. Get the population" << std::endl;
        std::cout << "6. Change the capital" << std::endl;
        std::cout << "7. Annex the territory" << std::endl;
        std::cout << "8. Increase the population" << std::endl;
        std::cout << "9. Display all information" << std::endl;
        std::cout << "10. Set name" << std::endl;
        std::cout << "11. Set date" << std::endl;
        std::cout << "12. Set area" << std::endl;
        std::cout << "13. Set population" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "=============" << std::endl;
        std::cout << "Select action: ";
        std::cin >> choice;
        str capital;
        str name;
        str date;
        double area;
        long long population;
        int add_area;
switch (choice) {
        case 1:
            std::cout << "Country name: " << russia.get_name() << std::endl;
            break;

        case 2:
            std::cout << "Capital: " << russia.get_capital() << std::endl;
            break;

        case 3:
            std::cout << "Date of foundation: " << russia.get_date() << std::endl;
            break;

        case 4:
            std::cout << "Square: " << russia.get_area_() << std::endl;
            break;

        case 5:
            std::cout << "Population: " << russia.get_population() << std::endl;
            break;

        case 6:
            std::cerr << "Enter name capital: " << std::endl;
            std::cin >> capital;
            try {
                russia.set_capital(capital);
            } catch (str error) {
                std::cerr << "error: " << error << std::endl;
            }
            break;

        case 7:
            std::cerr << "Enter the area to be added: " << std::endl;
            std::cin >> add_area;
            try {
                russia.add_territory(add_area);
            }
            catch (str error) {
                std::cerr << "error: " << error << std::endl;
            }
            break;

        case 8:
            try {
                russia.gros_population();
            }
            catch (str error) {
                std::cerr << "error: " << error << std::endl;
            }
            break;

        case 9:
            russia.print_info();
            break;

        case 10:
            std::cerr << "Enter name: " << std::endl;
            std::cin >> name;
            try {
                russia.set_name(name);
            }
            catch (str error) {
                std::cerr << "error: " << error << std::endl;
            }
            break;

        case 11:
            std::cerr << "Enter date: " << std::endl;
            std::cin >> date;
            try {
                russia.set_date(date);
            }
            catch (str error) {
                std::cerr << "error: " << error << std::endl;
            }
            break;

        case 12:
            std::cerr << "Enter area: " << std::endl;
            std::cin >> area;
            try {
                russia.set_area(area);
            }
            catch (str error) {
                std::cerr << "error: " << error << std::endl;
            }
            break;

        case 13:
            std::cerr << "Enter population: " << std::endl;
            std::cin >> population;
            try {
                russia.set_population(population);
            }
            catch (str error) {
                std::cerr << "error: " << error << std::endl;
            }
            break;

        case 0:
            std::cout << "Выход из программы..." << std::endl;
            break;

        default:
            std::cout << "Неверный выбор!" << std::endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
