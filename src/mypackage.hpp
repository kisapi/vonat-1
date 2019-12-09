#ifndef MYPACKGE_HPP
#define MYPACKGE_HPP

#include "package.hpp"

class MyPackage : public Package{
public:
    MyPackage(const std::string& name, const unsigned int amount, const Station* destination);
    const std::string& getName()const;
     unsigned int getAmount() const;
     const Station* getDestination() const;
     void addAmount(const int _amount);
     void removeAmount(const int _amount);

     bool operator==(MyPackage& other)const;
};

#endif // MYPACKAGE_HPP
