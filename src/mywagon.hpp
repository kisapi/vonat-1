#ifndef MYWAGON_HPP
#define MYWAGON_HPP

#include "wagon.hpp"
#include "mypackage.hpp"


class MyWagon : public Wagon{
public:
    MyWagon(const std::string& name, const unsigned int maxPackageNumber)
        :Wagon(name,maxPackageNumber){}
    const std::string& getName() const;
    unsigned int getMaxPackageNumber() const;
    bool isEmpty() const;
    bool isFull() const;
    void addPackage(Package & newPackage);
    const std::set<Package>::iterator findPackage(const Package & packageToFind) const;
    //Package &getPackage(const Package & packageToGet) const;
    void removePackage(const std::set<Package>::iterator packageToRemove);
};



#endif // MYWAGON_HPP
