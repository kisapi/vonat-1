#ifndef MYTRAIN_HPP
#define MYTRAIN_HPP

#include "train.hpp"
#include "mywagon.hpp"


class MyTrain : public Train{
public:
     const std::string& getName() const;
     unsigned int getMaxWagonNumber() const;
     bool isEmpty() const;
     bool isFull() const;
     const std::set<Wagon*>* getWagons() const;
     bool isWagonMounted(const std::string name) const;
     const std::set<Wagon*>::iterator findWagon(Wagon* const wagonToFind) const;
     void mountWagon(Wagon* newWagon);
     void disMountWagon(const std::set<Wagon*>::iterator which);

     bool operator==(MyTrain& other) const;
};

#endif // MYTRAIN_HPP
