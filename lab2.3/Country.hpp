#pragma once
#include <string>
#include <vector>
#include <cstdlib> 
#include <ctime> 
#include "include/country_lib.hpp"

using str = std::string;
using strVec = std::vector<std::string>;


namespace mt {

class Country {
private:
    str name_;              
    str capital_;           
    int foundation_date_;   
    double area_;           
    int population_;       
    std::vector<City> cities_;  

public:

    Country();                                                   
    Country(str name, str capital, int date, double area,        
        int population, const std::vector<City>& cities = {});
    Country(const Country& other);                               
    ~Country();                                                  


    Country& operator=(const Country& other);     
    Country operator+(const Country& other) const; 
    Country operator*(const Country& other) const; 
    Country& operator+=(const Country& other);     


    str get_name() const;
    str get_capital() const;
    int get_foundation_date() const;    
    double get_area() const;
    int get_population() const;           
    const std::vector<City>& get_cities() const;    
    City get_city_by_name(const str& city_name) const; 
    int get_total_population() const;     

    void set_name(str name);
    void set_capital(str capital);
    void set_foundation_date(int date);   
    void set_area(double area);
    void set_population(int population);   
    void set_city_population(const str& city_name, int new_population);  
    void set_city_budget(const str& city_name, double new_budget);      

    void annex_territory(const Country& territory);

    void change_population(const str& city_name, int delta);  
    void change_total_population(int delta);                  

    void distribute_budget(const Budget& budget);

    void print_info() const;
};

} // namespace mt