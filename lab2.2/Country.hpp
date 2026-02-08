#pragma once
#include <string>
#include <vector>
#include <cstdlib> 
#include <ctime> 

using str = std::string;
using strVec = std::vector<std::string>;

namespace mt {

class Country {
private:
    str name_;
    str capital_;
    double area_;
    strVec cities_;
public:
    Country();

    Country(str name, str capital, double area, const strVec& cities = {});

    Country(const Country& c);

    ~Country();

    Country& operator=(const Country& other);

    str get_name() const;
    str get_capital() const;
    double get_area() const;
    const strVec& get_cities() const;

    Country operator+(const Country& other) const;
    Country operator*(const Country& other) const;
    Country& operator+=(const Country& other);

    void set_capital(str capital);
    void set_name(str name);
    void set_area(double area);
    void set_city_at_index(size_t index, const str& new_city_name);

    void print_info() const;
};
} // namespace mt