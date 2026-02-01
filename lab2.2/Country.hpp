#pragma once
#include <string>
#include <vector>

using str = std::string;
using strVec = std::vector<std::string>;

namespace mt {

class Country {
private:
    str name_;
    str capital_;
    double area_;
    strVec cities_;
protected:
    str date_;
public:
    Country();

    Country(str name, str capital, str date, double area, const strVec& cities = {});

    Country(const Country& c);

    ~Country();

    Country& operator=(const Country& other);

    str get_name() const;
    str get_capital() const;
    str get_date() const;
    double get_area() const;
    const strVec& get_cities() const;

    Country operator+(const Country& other) const;
    Country operator*(const Country& other) const;

    void set_capital(str capital);
    void set_name(str name);
    void set_date(str date);
    void set_area(double area);
    void set_cities(const strVec& cities);

    void print_info() const;
};
} // namespace mt