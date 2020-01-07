#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

#include "mypackage.hpp"
#include "mystation.hpp"
#include "mytrain.hpp"
#include "mywagon.hpp"

namespace pt = boost::property_tree;

bool testInput(const std::string fileName){
    std::ifstream f(fileName.c_str());
    return f.good();
}



void load (const std::string fileName, std::vector<MyPackage>& packages, std::vector<MyStation>& stations,
           std::vector<MyTrain>& trains, std::vector<MyWagon>& wagons){
    pt::ptree tree;
    pt::read_json(fileName, tree);

    //Stations
    pt::ptree& stationTree = tree.get_child("shipping.stations");
    for( pt::ptree::value_type& newStation : stationTree){
        stations.push_back(MyStation(newStation.second.data()));
    }

    //Packages
    pt::ptree& packageTree = tree.get_child("shipping.packages");
    for(pt::ptree::value_type& newPackage : packageTree){
        const std::string packageName (newPackage.second.get_child("name").get_value<std::string>());
        const int amount (newPackage.second.get_child("amount").get_value<int>());
        const std::string destination (newPackage.second.get_child("destination").get_value<std::string>());
        const std::string location (newPackage.second.get_child("location").get_value<std::string>());

        MyStation* destinationStation;
        for(MyStation& station : stations){
            if(station.getName() == destination){
                destinationStation = &station;
                break;
            }
        }

        MyStation* locationStation;
        for(MyStation& station : stations){
            if(station.getName() == location){
                locationStation = &station;
                break;
            }
        }

        MyPackage tmp (packageName,amount,destinationStation);
        packages.push_back(tmp);
        locationStation->addPackage(tmp);
    }


    //Trains
    pt::ptree& trainTree = tree.get_child("shipping.trains");
    for( pt::ptree::value_type newTrain : trainTree){
        //const std::string packageName (newPackage.second.get_child("name").get_value<std::string>());
        const std::string trainName  (newTrain.second.get_child("name").get_value<std::string>());
        const unsigned int maxWagonNumber (newTrain.second.get_child("maxWagonNumber").get_value<unsigned int>());
        std::vector<std::pair<std::string,unsigned int>> schedule;

        for( pt::ptree::value_type& stop : newTrain.second.get_child("schedule")){
            std::string name (stop.second.get_child("name").get_value<std::string>());
            unsigned int time (stop.second.get_child("time").get_value<unsigned int>());

            schedule.push_back(std::make_pair(name,time));
        }

        MyTrain tmp (trainName,maxWagonNumber,schedule);
        trains.push_back(tmp);
    }

    //Wagons
    pt::ptree& wagonTree = tree.get_child("shipping.wagons");
    for( pt::ptree::value_type newWagon : wagonTree){
        const std::string name(newWagon.second.get_child("name").get_value<std::string>());
        const unsigned int maxPackageNumber (newWagon.second.get_child("maxPackageNumber").get_value<unsigned int>());
        const std::string location(newWagon.second.get_child("location").get_value<std::string>());

        MyStation* locationStation;
        for(MyStation& station : stations){
            if(station.getName() == location){
                locationStation = &station;
            }
        }

        MyWagon tmp(name,maxPackageNumber);
        locationStation->addWagon(tmp);
        wagons.push_back(tmp);
    }
}

bool scheduleContains(const MyTrain& train, const std::string stop){
    const std::vector<std::pair<std::string, unsigned int>>& schedule = train.getSchedule();
    for(size_t i = 0; i < schedule.size(); ++i){
        if(schedule[i].first == stop){
            return true;
        }
    }
    return false;
}

bool isDeployable(const std::vector<MyTrain>& trains, const std::vector<MyStation>& stations){
    const size_t trainSize(trains.size());
    std::vector<std::vector<bool>> bitMap(trainSize, std::vector<bool>(trainSize,false));
    for(size_t i = 0; i < (trains.size()-1); ++i){ // iterate through all trains
        for(size_t k = (i+1); k < trains.size();++k){ //iterate through others
            const std::vector<std::pair<std::string, unsigned int> >& baseSchedule = trains[i].getSchedule();
            const std::vector<std::pair<std::string, unsigned int> >& otherSchedule = trains[k].getSchedule();

            for(const std::pair<std::string, unsigned int >& baseTrainItem : baseSchedule){ // base schedule
                for(const std::pair<std::string, unsigned int >& otherTrainItem : otherSchedule){ //other schedule
                    if(baseTrainItem == otherTrainItem){
                        bitMap[i][k] = true;
                    }
                }
            }
        }
    }


    for(const MyStation& station : stations){ //through stations-> we now the location
        for(const Package& package : station.getUndeliveredPackages()){ // through packages in that station
            bool fine(false);
            package.getDestination();
            for(size_t i = 0; i < trainSize; ++i){ //through trains, we find the first which contains the location
                if(scheduleContains(trains[i],station.getName())){
                    //now we want ot find whether we can reach the destination of the package from here?
                    for(size_t k = i; k < trainSize; ++k){
                        if(bitMap[i][k]){
                            if(scheduleContains(trains[k],package.getDestination()->getName())){
                                //we can reach the destination
                                fine = true;
                            }
                        }
                    }
                }
            }
            if(!fine){
                return false;
            }
        }
    }

    return true;
}


int main (){

    const std::string filename("./");
    //Checking if the file exist and isn't damaged
    if(!testInput(filename)){
        std::cerr << "The program could not find the given json file." << std::endl;
        return -1;
    }
    //Load the data into these vectors
    std::vector<MyPackage> packages;
    std::vector<MyStation> stations;
    std::vector<MyTrain> trains;
    std::vector<MyWagon> wagons;

    load(filename,packages,stations,trains,wagons);

    //Check whether the current problem has a solution
    if(!isDeployable(trains,stations)){
        std::cerr << "This problem has no solutions since some packages can't be shipped"
                  << std::endl;
        return -1;
    }



    std::cout << "Hello World!" << std::endl;
    return 0;
}
