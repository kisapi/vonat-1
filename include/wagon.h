#ifndef WAGON_H
#define WAGON_H

#include <string>
#include <set>

class Package;

class Wagon{
public:
	Wagon(const std::string& name, const unsigned int maxPackageNumber);
	virtual ~Wagon();
	virtual const std::string& getName() const = 0;
    virtual unsigned int getMaxPackageNumber() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
	virtual void addPackage(const Package* newPackage) = 0; 
    virtual bool isPackageExisting(const std::string& name) = 0;
	virtual const std::set<Package>::iterator findPackage(const std::string& packageName) const = 0;
	virtual const Package* getPackage(const std::set<Package*>::iterator which) const = 0;
	virtual const std::set<Package>& getPackages() const = 0;
	virtual void removePackage(const std::set<Package*>::iterator which) = 0;
private:
	const std::string name;
	const unsigned int maxPackageNumber;
	std::set<Package*> packages;
};


#endif //WAGON_H
