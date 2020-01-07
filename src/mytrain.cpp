#include "mytrain.hpp"

const std::string& MyTrain::getName() const{
    return name;
}

unsigned int MyTrain::getMaxWagonNumber() const{
    return maxWagonNumber;
}

bool MyTrain::isEmpty() const{
    return wagons.empty();
}

bool MyTrain::isFull() const{
    return (maxWagonNumber == wagons.size());
}

const std::set<Wagon> &MyTrain::getWagons() const{
    return wagons;
}

const std::set<Wagon>::iterator MyTrain::findWagon(const Wagon & wagonToFind) const{
    return wagons.find(wagonToFind);
}

void MyTrain::mountWagon(Wagon &newWagon){
    wagons.insert(newWagon);
}

void MyTrain::disMountWagon(const std::set<Wagon>::iterator which){
    wagons.erase(which);
}

bool MyTrain::isWagonMounted(const Wagon &  wagon) const{
    if(wagons.find(wagon) == wagons.end()){
        return false;
    }
    return true;
}
