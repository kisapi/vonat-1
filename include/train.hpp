#ifndef TRAIN_HPP
#define TRAIN_HPP

#include <string>
#include <set>

#include "wagon.hpp"


//class Wagon;

class Train{
public:
    Train(const std::string name, const unsigned int maxWagonNumber)
        :name(name), maxWagonNumber(maxWagonNumber){}
	virtual ~Train();
	virtual const std::string& getName() const = 0;
    virtual unsigned int getMaxWagonNumber() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual const std::set<Wagon*>* getWagons() const = 0;
    virtual bool isWagonMounted(const std::string name) const = 0;
    virtual const std::set<Wagon*>::iterator findWagon(Wagon* const wagonToFind) const = 0;
    virtual void mountWagon(Wagon* newWagon) = 0;
    virtual void disMountWagon(const std::set<Wagon*>::iterator which) = 0;
protected:
    const std::string name;
    const unsigned int maxWagonNumber;
    std::set<Wagon*> wagons;
};

#endif // TRAIN_HPP
