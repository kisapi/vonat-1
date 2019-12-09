#ifndef WAGON_HPP
#define WAGON_HPP

//#include <string>
#include <set>

#include "package.hpp"

//class Package;

class Wagon{
public:
    Wagon(const std::string& name, const unsigned int maxPackageNumber)
        : name(name), maxPackageNumber(maxPackageNumber){}
	virtual ~Wagon();
	virtual const std::string& getName() const = 0;
    virtual unsigned int getMaxPackageNumber() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual void addPackage(Package* newPackage) = 0;
    virtual bool isPackageExisting(const std::string* name) = 0;
    virtual const std::set<Package*>::iterator findPackage(Package * const packageToFind) const = 0;
    virtual Package* getPackage(Package * const packageToGet) const = 0;
    //virtual const std::set<Package*>* getPackages() const = 0;
    virtual void removePackage(const std::set<Package*>::iterator packageToRemove) = 0;
protected:
	const std::string name;
	const unsigned int maxPackageNumber;
    std::set<Package*> packages;
};


#endif //WAGON_HPP
