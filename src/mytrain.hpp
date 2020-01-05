#ifndef MYTRAIN_HPP
#define MYTRAIN_HPP

#include "train.hpp"
#include "mywagon.hpp"


class MyTrain : public Train{
public:
     MyTrain(const std::string name, const unsigned int maxWagonNumber, const std::vector<std::string>& schedule)
         : Train(name,maxWagonNumber,schedule){}
     const std::string& getName() const;
     unsigned int getMaxWagonNumber() const;
     bool isEmpty() const;
     bool isFull() const;
     const std::set<Wagon*>* getWagons() const;
     bool isWagonMounted(Wagon &wagon) const;
     const std::set<Wagon*>::iterator findWagon(Wagon* const wagonToFind) const;
     void mountWagon(Wagon* newWagon);
     void disMountWagon(const std::set<Wagon*>::iterator which);
};

#endif // MYTRAIN_HPP
