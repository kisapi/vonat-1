#ifndef MYSTATION_HPP
#define MYSTATION_HPP

#include "station.hpp"
#include "mypackage.hpp"
#include "mytrain.hpp"
#include "mywagon.hpp"

class MyStation : public Station
{
public:
    MyStation(const std::string& name);
     const std::string& getName() const;
     bool isEmpty() const;
     void addPackage(MyPackage & newPackage); //this should determine where to put the package
     void addTrain(Train & newTrain);
     void addWagon(Wagon & newWagon);
     const std::set<Train>::iterator findTrain(const Train & name) const; //reconsider taking string as argument
     void removeTrain(const std::set<Train>::iterator trainToRemove);
     const std::set<Wagon>::iterator findWagon(const Wagon & name) const;//reconsider taking string as argument
     void removeWagon(const std::set<Wagon>::iterator wagonToRemove);
     const std::set<Package>::iterator findPackage(const Package & name) const;//reconsider taking string as argument
     void removePackage(const std::set<Package>::iterator packageToRemove);
};

#endif // MYSTATION_HPP
