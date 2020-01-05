#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include <string>

class Station;

class Package{
public:
    Package(const std::string& name, const unsigned int amount, const Station* destination)
        :name(name), amount(amount), destination(destination){}
    virtual ~Package(){}
    virtual const std::string& getName() const = 0;
    virtual unsigned int getAmount() const = 0;
	virtual const Station* getDestination() const = 0;
    virtual void removeAmount(const int _amount) = 0;
    virtual void addAmount(const int _amount) = 0;
protected:
    const std::string name;
	unsigned int amount;
	const Station* destination;
};


#endif //PACKAGE_HPP
