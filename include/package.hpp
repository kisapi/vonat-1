#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include <string>

class Station;

class Package{
public:
    Package(const std::string& name, const unsigned int amount, const Station* destination)
        :name(name), amount(amount), destination(destination){}
    virtual ~Package(){}

    virtual const std::string& getName() const{
        return name;
    }
    friend bool operator< (const Package& first, const Package& second){
        return first.getName() < second.getName();
    }
protected:
    const std::string name;
	unsigned int amount;
	const Station* destination;
};


#endif //PACKAGE_HPP
