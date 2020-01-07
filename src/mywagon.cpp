#include "mywagon.hpp"

const std::string& MyWagon::getName() const{
    return name;
}

unsigned int MyWagon::getMaxPackageNumber() const{
    return maxPackageNumber;
}

bool MyWagon::isEmpty() const{
    return packages.empty();
}

bool MyWagon::isFull() const{
    return (maxPackageNumber == packages.size());
}

void MyWagon::addPackage(Package& newPackage){
    packages.insert(newPackage);
}

const std::set<Package>::iterator MyWagon::findPackage(const Package & packageToFind) const{
    return packages.find(packageToFind);
}
/*
Package& MyWagon::getPackage(const std) const{
    return packages.find(packageToGet);
}*/

void MyWagon::removePackage(const std::set<Package>::iterator packageToRemove){
    packages.erase(packageToRemove);
}
