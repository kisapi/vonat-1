#ifndef STATUS_HPP
#define STATUS_HPP

#include <vector>


#include "mypackage.hpp"
#include "mystation.hpp"
#include "mytrain.hpp"
#include "mywagon.hpp"

class Status
{
public:
    Status(const std::vector<MyPackage>& packages, const std::vector<MyStation>& stations,
           const std::vector<MyTrain>& trains, const std::vector<MyWagon>& wagons,
           const unsigned int iterationCounter, const Status* parent);
    const Status* getParent() const;
    std::vector<Status>& getChildren() const;
    bool isEnd() const;

private:
    const std::vector<MyPackage> packages;
    const std::vector<MyStation> stations;
    const std::vector<MyTrain> trains;
    const std::vector<MyWagon> wagons;
    const unsigned int iterationCounter;
    const Status* parent;

};

#endif // STATUS_HPP
