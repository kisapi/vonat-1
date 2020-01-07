#ifndef WAGON_HPP
#define WAGON_HPP

#include <set>

#include "package.hpp"

class Wagon{
public:
    Wagon(const std::string& name, const unsigned int maxPackageNumber)
        : name(name), maxPackageNumber(maxPackageNumber){}
    virtual ~Wagon(){}
    virtual const std::string& getName() const{return name;}
    friend bool operator<(const Wagon& first, const Wagon& second){
        return first.getName() < second.getName();
    }
protected:
	const std::string name;
	const unsigned int maxPackageNumber;
    std::set<Package> packages;
};




#endif //WAGON_HPP
