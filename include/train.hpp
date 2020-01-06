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
	virtual const std::string& getName() const = 0;
    virtual unsigned int getMaxWagonNumber() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual const std::set<Wagon*>* getWagons() const = 0;
    virtual bool isWagonMounted(Wagon& wagon) const = 0;
    virtual const std::set<Wagon*>::iterator findWagon(Wagon* const wagonToFind) const = 0;
    virtual void mountWagon(Wagon* newWagon) = 0;
    virtual void disMountWagon(const std::set<Wagon*>::iterator which) = 0;
    virtual const std::vector<std::pair<std::string,unsigned int> >& getSchedule() const = 0;
protected:
    const std::string name;
    const unsigned int maxWagonNumber;
    std::set<Wagon*> wagons;
    const std::vector<std::pair<std::string,unsigned int>> schedule;
};

#endif // TRAIN_HPP
