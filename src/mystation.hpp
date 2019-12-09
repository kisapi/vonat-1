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
     void addPackage(Package *newPackage); //this should determine where to put the package
     void addTrain(Train *newTrain);
     void addWagon(Wagon* newWagon);
     const std::set<Train*>::iterator findTrain(Train * const name) const; //reconsider taking string as argument
     void removeTrain(const std::set<Train*>::iterator trainToRemove);
     const std::set<Wagon*>::iterator findWagon(Wagon * const name) const;//reconsider taking string as argument
     void removeWagon(const std::set<Wagon*>::iterator wagonToRemove);
     const std::set<Package*>::iterator findPackage(Package * const name) const;//reconsider taking string as argument
     void removePackage(const std::set<Package*>::iterator packageToRemove);
};

#endif // MYSTATION_HPP
