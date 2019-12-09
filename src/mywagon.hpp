#ifndef MYWAGON_HPP
#define MYWAGON_HPP

#include "wagon.hpp"
#include "mypackage.hpp"


class MyWagon : public Wagon{
public:
     const std::string& getName() const;
     unsigned int getMaxPackageNumber() const;
     bool isEmpty() const;
     bool isFull() const;
     void addPackage(Package *newPackage);
     //bool isPackageExisting(const std::string* name);
     const std::set<Package*>::iterator findPackage(Package * const packageToFind) const;
     Package* getPackage(Package * const packageToGet) const;
     //const std::set<Package*>* getPackages() const;
     void removePackage(const std::set<Package*>::iterator packageToRemove);
};



#endif // MYWAGON_HPP
