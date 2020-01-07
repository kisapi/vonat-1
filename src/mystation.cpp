#include "mystation.hpp"
#include "train.hpp"

#include <algorithm>

MyStation::MyStation(const std::string &name):
    Station(name){}

const std::string& MyStation::getName() const{
    return name;
}

bool MyStation::isEmpty() const{
    return stationingTrains.empty();
}

void MyStation::addPackage(MyPackage & newPackage){
    if(newPackage.getDestination() == this){
        deliveredPackages.push_back(newPackage);
    }else{
        unDeliveredPackages.insert(newPackage);
    }
}

void MyStation::addTrain(Train & newTrain){
    stationingTrains.insert(newTrain);
}

void MyStation::addWagon(Wagon & newWagon){
    unMountedWagons.insert(newWagon);
}

const std::set<Train>::iterator MyStation::findTrain(const Train & trainToFind) const{
    return stationingTrains.find(trainToFind);
}

void MyStation::removeTrain(const std::set<Train>::iterator trainToRemove){
    stationingTrains.erase(trainToRemove);
}

const std::set<Wagon>::iterator MyStation::findWagon(const Wagon & wagonToFind) const{
    return unMountedWagons.find(wagonToFind);
}

void MyStation::removeWagon(const std::set<Wagon>::iterator wagonToRemove){
    unMountedWagons.erase(wagonToRemove);
}

const std::set<Package>::iterator MyStation::findPackage(const Package & packageToFind) const{
    return unDeliveredPackages.find(packageToFind);
}

void MyStation::removePackage(const std::set<Package>::iterator packageToRemove){
    unDeliveredPackages.erase(packageToRemove);
}
const std::set<Package>& MyStation::getUndeliveredPackages() const{
    return unDeliveredPackages;
}

