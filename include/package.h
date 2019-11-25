#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>

class Station;

class Package{
public:
	Package(const std::string name, const unsigned int amount, const Station* destination);
	virtual ~Package();
	virtual const std::string& getName() const = 0;
    virtual unsigned int getAmount() const = 0;
	virtual const Station* getDestination() const = 0;
	virtual void removeAmount(int _amount) = 0;
	virtual void addAmount(int _amount) = 0;
private:
	const std::string name;
	unsigned int amount;
	const Station* destination;
};


#endif //PACKAGE_H
