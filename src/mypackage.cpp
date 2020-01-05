#include "mypackage.hpp"

MyPackage::MyPackage(const std::string& name, const unsigned int amount, const Station *destination)
    :
      Package(name,amount,destination)
{}

const std::string& MyPackage::getName() const{
    return name;
}

unsigned int MyPackage::getAmount() const {
    return amount;
}

const Station* MyPackage::getDestination() const{
    return destination;
}

void MyPackage::addAmount(const int _amount){
    amount += _amount;
}

void MyPackage::removeAmount(const int _amount){
    amount -= _amount;
}

bool MyPackage::operator ==(MyPackage& other) const{
    return (this->name == other.getName());
}
