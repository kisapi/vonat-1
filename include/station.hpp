#ifndef STATION_HPP
#define STATION_HPP

#include <string>
#include <set>
#include <vector>

#include "package.hpp"
#include "train.hpp"
#include "wagon.hpp"

/*
class Train;
class Wagon;
class Package;
*/
class Station{
public:
    Station(const std::string& name)
        : name(name){}
	virtual ~Station();
	virtual const std::string& getName() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void addTrain(Train* newTrain) = 0;
    virtual void addWagon(Wagon* newWagon) = 0;
    virtual void addPackage(Package* newPackage) = 0; //this should determine where to put the package
    virtual const std::set<Train*>::iterator findTrain(Train * const name) const = 0;
    virtual void removeTrain(const std::set<Train*>::iterator trainToRemove) = 0;
    virtual const std::set<Wagon*>::iterator findWagon(Wagon * const name) const = 0;
    virtual void removeWagon(const std::set<Wagon*>::iterator wagonToRemove) = 0;
    virtual const std::set<Package*>::iterator findPackage(Package * const name) const = 0;
    virtual void removePackage(const std::set<Package*>::iterator which) = 0;
protected:
	const std::string name;
    std::set<Train*> stationingTrains;
    std::set<Package*> unDeliveredPackages;
    std::vector<Package*> deliveredPackages;
    std::set<Wagon*> unMountedWagons;
};

#endif // STATION_HPP
