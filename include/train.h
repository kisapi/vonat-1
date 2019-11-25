#ifndef TRAIN_H
#define TRAIN_H

#include <string>
#include <set>

class Wagon;

class Train{
public:
	Train(const std::string& name, const unsigned int maxWagonNumber);
	virtual ~Train();
	virtual const std::string& getName() const = 0;
    virtual unsigned int getMaxWagonNumber() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
	virtual const std::set<Wagon*>& getWagons() const = 0;
    virtual bool isWagonMounted(const std::string name) const = 0;
	virtual const std::set<Wagon*>::iterator findWagon(std::string name) const = 0;
	virtual void mountWagon(Wagon* newWagon) = 0;
	virtual void disMountWagon(std::set<Wagon*>::iterator which) = 0;
private:
    const std::string name;
    const unsigned int maxWagonNumber;
    std::set<Wagon*> wagons;
};

#endif // TRAIN_H
