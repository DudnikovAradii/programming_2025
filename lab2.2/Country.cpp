#include "Country.hpp"
#include <iostream>
#include <exception>
#include <algorithm>
#include <cstdlib> 
#include <ctime> 

namespace mt {
Country::Country() {
    name_ = "unknown";
    capital_ = "unknown";
    area_ = 0;
    std::cerr << "ctor default" << std::endl;
}

Country::Country(str name, str capital, double area, const strVec& cities) :
    name_(name), capital_(capital), area_(area), cities_(cities) {
    std::cerr << "ctor param" << std::endl;
}
Country::Country(const Country& c) : name_(c.name_), capital_(c.capital_), area_(c.area_), cities_(c.cities_) {
    std::cerr << "ctor copy" << std::endl;
}
Country::~Country() {
    cities_.clear(); 
    std::cerr << "dtor" << std::endl;
}
Country& Country::operator=(const Country& other) {
    if (this != &other) {
        name_ = other.name_;
        capital_ = other.capital_;
        area_ = other.area_;
        cities_ = other.cities_;
        std::cerr << "operator= called" << std::endl;
    }
    return *this;
}

str Country::get_name() const { return name_; }
str Country::get_capital() const { return capital_; }
double Country::get_area() const { return area_; }
const strVec& Country::get_cities() const { return cities_; }

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

    result.cities_ = this->cities_;

    for (int i = 0; i < other.cities_.size(); i++) {
        const str& city = other.cities_[i];
        bool found = false;

        for (int j = 0; j < result.cities_.size(); j++) {
            if (result.cities_[j] == city) {
                found = true;
                break;
            }
        }

        if (found) {
            result.cities_.push_back(city + " new");
        }
        else {
            result.cities_.push_back(city);
        }
    }

    return result;
}

Country Country::operator*(const Country& other) const {
    Country result;

    result.name_ = "path " + this->name_ + "->" + other.name_;
    result.capital_ = "No";

    if (this->area_ < other.area_) {
        result.area_ = this->area_;
    }
    else {
        result.area_ = other.area_;
    }

    result.cities_.clear();
    result.cities_.push_back(this->capital_);
    result.cities_.push_back(other.capital_);

    strVec first_candidates;
    for (size_t i = 0; i < this->cities_.size(); i++) {
        if (this->cities_[i] != this->capital_) {
            first_candidates.push_back(this->cities_[i]);
        }
    }

    if (!first_candidates.empty()) {
        int random_index = 0;
        if (first_candidates.size() > 1) {
            random_index = std::rand() % static_cast<int>(first_candidates.size());
        }
        str random_city = first_candidates[random_index];

        bool duplicate = false;
        for (size_t i = 0; i < result.cities_.size(); i++) {
            if (result.cities_[i] == random_city) {
                duplicate = true;
                break;
            }
        }

        if (duplicate) {
            result.cities_.push_back(random_city + " new");
        }
        else {
            result.cities_.push_back(random_city);
        }
    }

    strVec second_candidates;
    for (size_t i = 0; i < other.cities_.size(); i++) {
        if (other.cities_[i] != other.capital_) {
            second_candidates.push_back(other.cities_[i]);
        }
    }

    if (!second_candidates.empty()) {
        int random_index = 0;
        if (second_candidates.size() > 1) {
            random_index = std::rand() % static_cast<int>(second_candidates.size());
        }
        str random_city = second_candidates[random_index];

        bool duplicate = false;
        for (size_t i = 0; i < result.cities_.size(); i++) {
            if (result.cities_[i] == random_city) {
                duplicate = true;
                break;
            }
        }

        if (duplicate) {
            result.cities_.push_back(random_city + " new");
        }
        else {
            result.cities_.push_back(random_city);
        }
    }

    return result;
}

Country& Country::operator+=(const Country& other) {

    name_ = name_ + "-" + other.name_;

    if (area_ < other.area_) {
        capital_ = other.capital_;
    }

    area_ += other.area_;

    strVec result_cities = cities_;  

    for (size_t i = 0; i < other.cities_.size(); i++) {
        const str& city = other.cities_[i];
        bool found = false;

        for (size_t j = 0; j < cities_.size(); j++) {
            if (cities_[j] == city) {
                found = true;
                break;
            }
        }

        if (found) {
            result_cities.push_back(city + " new");
        }
        else {
            result_cities.push_back(city);
        }
    }

    cities_ = result_cities;

    return *this;
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

void Country::set_area(double area) {
    if (area < 0) {
        str error = "Area cannot be negative";
        throw error;
    }
    area_ = area;
    std::cerr << "Area after change: " << area_ << std::endl;
}

void Country::set_city_at_index(size_t index, const str& new_city_name) {
    if (index >= cities_.size()) {
        str error = "Invalid city index";
        throw error;
    }

    if (new_city_name.empty()) {
        str error = "City name cannot be empty";
        throw error;
    }

    str uppercase_letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    str allowed_chars = "abcdefghijklmnopqrstuvwxyz";

    if (uppercase_letters.find(new_city_name[0]) == std::string::npos) {
        str error = "City name must start with an uppercase letter";
        throw error;
    }

    for (size_t i = 1; i < new_city_name.length(); i++) {
        char c = new_city_name[i];
        if (allowed_chars.find(c) == std::string::npos) {
            str error = "City name should be without numbers, spaces, punctuation marks and capital letters";
            throw error;
        }
    }

    cities_[index] = new_city_name;
}

void Country::print_info() const {
    std::cout << "Country information: " << std::endl;
    std::cout << "Name: " << name_ << std::endl;
    std::cout << "Capital: " << capital_ << std::endl;
    std::cout << "Area: " << area_ << std::endl;
    std::cout << "Cities: ";

    if (cities_.empty()) {
        std::cout << "none";
    }
    else {
        for (size_t i = 0; i < cities_.size(); i++) {
            std::cout << cities_[i];
            if (i < cities_.size() - 1) std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

} // namespace mt