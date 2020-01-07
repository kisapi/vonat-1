#ifndef MYTRAIN_HPP
#define MYTRAIN_HPP

#include "train.hpp"
#include "mywagon.hpp"


class MyTrain : public Train{
public:
     MyTrain(const std::string name, const unsigned int maxWagonNumber,
             const std::vector<std::pair<std::string,unsigned int>>& schedule)
         : Train(name,maxWagonNumber,schedule){}
     const std::string& getName() const;
     unsigned int getMaxWagonNumber() const;
     bool isEmpty() const;
     bool isFull() const;
     const std::set<Wagon>& getWagons() const;
     bool isWagonMounted(const Wagon &wagon) const;
     const std::set<Wagon>::iterator findWagon(const Wagon& wagonToFind) const;
     void mountWagon(Wagon& newWagon);
     void disMountWagon(const std::set<Wagon>::iterator which);
     const std::vector<std::pair<std::string, unsigned int > >& getSchedule() const;
};

#endif // MYTRAIN_HPP
