#ifndef TRAIN_HPP
#define TRAIN_HPP

#include <string>
#include <set>
#include <vector>

#include "wagon.hpp"


//class Wagon;

class Train{
public:
    Train(const std::string name, const unsigned int maxWagonNumber,
          const std::vector<std::pair<std::string,unsigned int>>& schedule)
        :name(name), maxWagonNumber(maxWagonNumber), schedule(schedule){}
    virtual ~Train(){}

    friend bool operator<(const Train& first, const Train& second){
        return first.getName() < second.getName();
    }
    virtual const std::string& getName() const{
      return name;
    }

protected:
    const std::string name;
    const unsigned int maxWagonNumber;
    std::set<Wagon> wagons;
    const std::vector<std::pair<std::string,unsigned int>> schedule;
};

#endif // TRAIN_HPP
