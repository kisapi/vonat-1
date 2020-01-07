#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <queue>
#include <vector>

#include "mypackage.hpp"
#include "mystation.hpp"
#include "mytrain.hpp"
#include "mywagon.hpp"

namespace pt = boost::property_tree;

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



int main (){

    const std::string filename("/home/filbe/ws/vonat/input.json");
    std::vector<MyPackage> packages;
    std::vector<MyStation> stations;
    std::vector<MyTrain> trains;
    std::vector<MyWagon> wagons;

    load(filename,packages,stations,trains,wagons);
    std::cout << "Hello World!" << std::endl;
    return 0;
}
