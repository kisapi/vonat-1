#ifndef STATION_HPP
#define STATION_HPP

#include <string>
#include <set>
#include <vector>

#include "package.hpp"
#include "train.hpp"
#include "wagon.hpp"

class Station{
public:
    Station(const std::string& name)
        : name(name){}
    virtual ~Station(){}
    virtual const std::string& getName()const{
        return name;
    }

protected:
	const std::string name;
    std::set<Train> stationingTrains;
    std::set<Package> unDeliveredPackages;
    std::vector<Package> deliveredPackages;
    std::set<Wagon> unMountedWagons;
};

#endif // STATION_HPP
