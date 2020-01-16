#include "status.hpp"


Status::Status(const std::vector<MyPackage>& packages, const std::vector<MyStation> &stations,
       const std::vector<MyTrain> &trains, const std::vector<MyWagon> &wagons,
       const unsigned int iterationCounter, const Status* parent)
:
    packages(packages),
    stations(stations),
    trains(trains),
    wagons(wagons),
    iterationCounter(iterationCounter),
    parent(parent)
{}


const Status* Status::getParent() const{
    return parent;
}

std::vector<Staus>& Status::getChildren() const{
    //TODO: write algorythm
}

bool Status::isEnd() const{
    //TODO: write algorythm
}
