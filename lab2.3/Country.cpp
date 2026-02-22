#include "Country.hpp"
#include <iostream>
#include <exception>
#include <algorithm>
#include <cstdlib> 
#include <ctime> 

namespace mt {


Country::Country() :
    name_("unknown"),
    capital_("unknown"),
    foundation_date_(2000),
    area_(0.0),
    population_(0) {
    std::cerr << "Country default ctor" << std::endl;
}

Country::Country(str name, str capital, int date, double area, int population, const std::vector<City>& cities) :
    name_(name),
    capital_(capital),
    foundation_date_(date),
    area_(area),
    population_(population),
    cities_(cities) {
    std::cerr << "Country param ctor" << std::endl;
}

Country::Country(const Country& other) :
    name_(other.name_),
    capital_(other.capital_),
    foundation_date_(other.foundation_date_),
    area_(other.area_),
    population_(other.population_),
    cities_(other.cities_) {
    std::cerr << "Country copy ctor" << std::endl;
}

Country::~Country() {
    cities_.clear();
    std::cerr << "Country dtor" << std::endl;
}

Country& Country::operator=(const Country& other) {
    if (this != &other) {
        name_ = other.name_;
        capital_ = other.capital_;
        foundation_date_ = other.foundation_date_;
        area_ = other.area_;
        population_ = other.population_;
        cities_ = other.cities_;
        std::cerr << "Country operator= called" << std::endl;
    }
    return *this;
}

str Country::get_name() const { return name_; }
str Country::get_capital() const { return capital_; }
int Country::get_foundation_date() const { return foundation_date_; }
double Country::get_area() const { return area_; }
int Country::get_population() const { return population_; }
const std::vector<City>& Country::get_cities() const { return cities_; }

int Country::get_total_population() const {
    int total = 0;
    for (size_t i = 0; i < cities_.size(); ++i) {
        total += cities_[i].population_;
    }
    return total;
}

City Country::get_city_by_name(const str& city_name) const {
    for (size_t i = 0; i < cities_.size(); ++i) {
        if (cities_[i].name_ == city_name) {
            return cities_[i];
        }
    }
    str error = "City not found";
    throw error;
}

void Country::set_name(str name) {
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

void Country::set_capital(str capital) {
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

void Country::set_foundation_date(int date) {  
    if (date < 0 || date > 2025) {
        str error = "Year must be between 0 and 2025";
        throw error;
    }

    foundation_date_ = date;
    std::cerr << "Foundation year changed to: " << foundation_date_ << std::endl;
}

void Country::set_area(double area) {
    if (area < 0) {
        str error = "Area cannot be negative";
        throw error;
    }
    area_ = area;
    std::cerr << "Area after change: " << area_ << std::endl;
}

void Country::set_population(int population) {
    if (population < 0) {
        str error = "Population cannot be negative";
        throw error;
    }
    population_ = population;
    std::cerr << "Population changed to: " << population_ << std::endl;
}

void Country::set_city_population(const str& city_name, int new_population) {
    if (new_population < 0) {
        str error = "Population cannot be negative";
        throw error;
    }

    for (size_t i = 0; i < cities_.size(); ++i) {
        if (cities_[i].name_ == city_name) {
            int old_pop = cities_[i].population_;
            cities_[i].population_ = new_population;
            std::cerr << "Population of " << city_name << " changed from " << old_pop
                << " to " << new_population << std::endl;
            return;
        }
    }
    str error = "City not found";
    throw error;
}

void Country::set_city_budget(const str& city_name, double new_budget) {
    if (new_budget < 0) {
        str error = "Budget cannot be negative";
        throw error;
    }

    for (size_t i = 0; i < cities_.size(); ++i) {
        if (cities_[i].name_ == city_name) {
            cities_[i].budget_ = new_budget;
            std::cerr << "Budget of " << city_name << " changed to " << new_budget << std::endl;
            return;
        }
    }
    str error = "City not found";
    throw error;
}

void Country::distribute_budget(const Budget& budget) {
    if (cities_.empty()) {
        std::cerr << "No cities to distribute budget to" << std::endl;
        return;
    }

    City* capital_city = nullptr;
    for (size_t i = 0; i < cities_.size(); ++i) {
        if (cities_[i].name_ == capital_) {
            capital_city = &cities_[i];
            break;
        }
    }

    if (!capital_city) {
        str error = "Capital city not found in cities list";
        throw error;
    }

    int total_population = 0;
    for (size_t i = 0; i < cities_.size(); ++i) {
        total_population += cities_[i].population_;
    }

    if (total_population == 0) {
        std::cerr << "Total population is zero, cannot distribute budget" << std::endl;
        return;
    }

    double total_money = budget.get_money();
    double coeff = budget.get_capital_coefficient();

    for (size_t i = 0; i < cities_.size(); ++i) {
        double share = static_cast<double>(cities_[i].population_) / total_population;

        if (cities_[i].name_ == capital_) {
            cities_[i].budget_ = total_money * share * coeff;
            std::cout << "  " << cities_[i].name_ << " (capital, pop=" << cities_[i].population_
                << "): " << cities_[i].budget_ << " (with coefficient)" << std::endl;
        }
        else {
            cities_[i].budget_ = total_money * share;
            std::cout << "  " << cities_[i].name_ << " (pop=" << cities_[i].population_
                << "): " << cities_[i].budget_ << std::endl;
        }
    }
    std::cout << "Budget distributed successfully" << std::endl;
}

void Country::annex_territory(const Country& territory) {
    name_ = name_ + "-" + territory.name_;

    // Выбираем столицу (большей территории)
    if (area_ < territory.area_) {
        capital_ = territory.capital_;
    }

    // Складываем площади
    area_ += territory.area_;

    // Складываем общее население
    population_ += territory.population_;

    // Добавляем новые города
    for (size_t i = 0; i < territory.cities_.size(); ++i) {
        const City& city = territory.cities_[i];
        bool found = false;
        for (size_t j = 0; j < cities_.size(); ++j) {
            if (cities_[j].name_ == city.name_) {
                found = true;
                break;
            }
        }

        if (found) {
            // Если город с таким именем уже есть, добавляем с пометкой
            City new_city = city;
            new_city.name_ = city.name_ + " (new)";
            cities_.push_back(new_city);
        }
        else {
            // Иначе добавляем как есть
            cities_.push_back(city);
        }
    }

    std::cerr << "Territory annexed. New name: " << name_ << std::endl;
}

// Изменение населения конкретного города

void Country::change_population(const str& city_name, int delta) {
    for (size_t i = 0; i < cities_.size(); ++i) {
        if (cities_[i].name_ == city_name) {
            int new_pop = cities_[i].population_ + delta;
            if (new_pop < 0) {
                str error = "Population cannot become negative";
                throw error;
            }
            cities_[i].population_ = new_pop;
            std::cerr << "Population of " << city_name << " changed by " << delta
                << ", new population: " << new_pop << std::endl;
            return;
        }
    }
    str error = "City not found";
    throw error;
}

// Изменение общего населения страны

void Country::change_total_population(int delta) {
    int new_pop = population_ + delta;
    if (new_pop < 0) {
        str error = "Total population cannot become negative";
        throw error;
    }
    population_ = new_pop;
    std::cerr << "Total population changed by " << delta
        << ", new total population: " << population_ << std::endl;
}

// ==================== Операторы ====================

Country Country::operator+(const Country& other) const {
    Country result;

    result.name_ = this->name_ + "-" + other.name_;

    if (this->area_ >= other.area_) {
        result.capital_ = this->capital_;
    }
    else {
        result.capital_ = other.capital_;
    }

    result.area_ = this->area_ + other.area_;
    result.population_ = this->population_ + other.population_;
    result.foundation_date_ = 0;

    result.cities_ = this->cities_;

    for (int i = 0; i < other.cities_.size(); i++) {
        const City& city = other.cities_[i];
        bool found = false;

        for (int j = 0; j < result.cities_.size(); j++) {
            if (result.cities_[j].name_ == city.name_) {
                found = true;
                break;
            }
        }

        if (found) {
            City new_city = city;
            new_city.name_ = city.name_ + " new";
            result.cities_.push_back(new_city);
        }
        else {
            result.cities_.push_back(city);
        }
    }

    return result;
}

// Оператор умножения двух стран (в стиле вашего кода)

Country Country::operator*(const Country& other) const {
    Country result;

    result.name_ = "path " + this->name_ + "->" + other.name_;
    result.capital_ = "No";
    result.foundation_date_ = 0;

    if (this->area_ < other.area_) {
        result.area_ = this->area_;
    }
    else {
        result.area_ = other.area_;
    }

    if (this->population_ < other.population_) {
        result.population_ = this->population_;
    }
    else {
        result.population_ = other.population_;
    }

    result.cities_.clear();
    result.cities_.push_back(City(this->capital_, 0, 0));
    result.cities_.push_back(City(other.capital_, 0, 0));

    std::vector<City> first_candidates;
    for (size_t i = 0; i < this->cities_.size(); i++) {
        if (this->cities_[i].name_ != this->capital_) {
            first_candidates.push_back(this->cities_[i]);
        }
    }

    if (!first_candidates.empty()) {
        int random_index = 0;
        if (first_candidates.size() > 1) {
            random_index = std::rand() % static_cast<int>(first_candidates.size());
        }
        City random_city = first_candidates[random_index];

        bool duplicate = false;
        for (size_t i = 0; i < result.cities_.size(); i++) {
            if (result.cities_[i].name_ == random_city.name_) {
                duplicate = true;
                break;
            }
        }

        if (duplicate) {
            random_city.name_ = random_city.name_ + " new";
            result.cities_.push_back(random_city);
        }
        else {
            result.cities_.push_back(random_city);
        }
    }

    std::vector<City> second_candidates;
    for (size_t i = 0; i < other.cities_.size(); i++) {
        if (other.cities_[i].name_ != other.capital_) {
            second_candidates.push_back(other.cities_[i]);
        }
    }

    if (!second_candidates.empty()) {
        int random_index = 0;
        if (second_candidates.size() > 1) {
            random_index = std::rand() % static_cast<int>(second_candidates.size());
        }
        City random_city = second_candidates[random_index];

        bool duplicate = false;
        for (size_t i = 0; i < result.cities_.size(); i++) {
            if (result.cities_[i].name_ == random_city.name_) {
                duplicate = true;
                break;
            }
        }

        if (duplicate) {
            random_city.name_ = random_city.name_ + " new";
            result.cities_.push_back(random_city);
        }
        else {
            result.cities_.push_back(random_city);
        }
    }

    return result;
}

Country& Country::operator+=(const Country& other) {
    this->name_ = this->name_ + "-" + other.name_;

    if (this->area_ < other.area_) {
        this->capital_ = other.capital_;
    }

    this->area_ += other.area_;
    this->population_ += other.population_;

    std::vector<City> result_cities = this->cities_;

    for (size_t i = 0; i < other.cities_.size(); i++) {
        const City& city = other.cities_[i];
        bool found = false;

        for (size_t j = 0; j < this->cities_.size(); j++) {
            if (this->cities_[j].name_ == city.name_) {
                found = true;
                break;
            }
        }

        if (found) {
            City new_city = city;
            new_city.name_ = city.name_ + " new";
            result_cities.push_back(new_city);
        }
        else {
            result_cities.push_back(city);
        }
    }

    this->cities_ = result_cities;

    return *this;
}

void Country::print_info() const {
    std::cout << " Country Information:" << std::endl;
    std::cout << "Name: " << name_ << std::endl;
    std::cout << "Capital: " << capital_ << std::endl;
    std::cout << "Foundation date: " << foundation_date_ << std::endl;
    std::cout << "Area: " << area_ << " sq. km" << std::endl;
    std::cout << "Total population: " << population_ << std::endl;
    std::cout << "Cities (" << cities_.size() << "):" << std::endl;

    if (cities_.empty()) {
        std::cout << "  none" << std::endl;
    }
    else {
        for (size_t i = 0; i < cities_.size(); ++i) {
            const City& city = cities_[i];
            std::cout << "  - " << city.name_ << " (pop: " << city.population_
                << ", budget: " << city.budget_ << ")" << std::endl;
        }
    }
}

} // namespace mt