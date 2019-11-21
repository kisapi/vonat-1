#ifndef STATION_H
#define STATION_H

#include <string>
#include <set>
#include <vector>

class Train;
class Wagon;
class Package;

class Station{
public:
	Station(const std::string name);
	virtual ~Station();
	virtual const std::string& getName() const = 0;
	virtual const bool isEmpty() const = 0;
	virtual void addTrain(const Train* newTrain) = 0;
	virtual void addWagon(const Wagon* newWagon) = 0;
	virtual void addPackage(const Package* newPackage) = 0; //this should determine where to put the package
	virtual const std::set<Train*>::iterator findTrain(const std::string& name) const = 0;
	virtual void removeTrain(const std::set<Train*>::iterator trainToRemove) = 0;
	virtual const std::set<Wagon*>::iterator findWagon(const std::string& name) const = 0;
	virtual void removeWagon(const std::set<Wagon*>::iterator wagonToRemove) = 0;
	virtual const std::set<Package*> findPackage(const std::string& name) const = 0;
	virtual void removePackage(const std::set<Package*>::iterator which) = 0;
private:
	const std::string name;
	std::set<Train*> stationingTrains;
	std::set<Package*> unDeliveredPackages;
	std::vector<Package*> deliveredPackages;	
	std::set<Wagon*> unMountedWagons;
}

#endif // STATION_H
