#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <fstream>
#include <chrono>
#include <boost/program_options.hpp>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

#include "mypackage.hpp"
#include "mystation.hpp"
#include "mytrain.hpp"
#include "mywagon.hpp"

namespace pt = boost::property_tree;
namespace po = boost::program_options;

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

    if(1 == trainSize){//No need to search for connection
        bitMap[0][0] = true;
    }else{
        //Search for connection between trains's schedules
        for(size_t i = 0; i < (trains.size()-1); ++i){ // iterate through all trains
            for(size_t k = i; k < trains.size();++k){ //iterate through others
                if(i == k){
                    bitMap[i][k] = true;
                    break;
                }
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
            if(!fine){ //we can't reach the destination
                return false;
            }
        }
    }

    return true;
}


int main(int argc,  char* argv[])
{
    std::cout << "The program strated" << std::endl;
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    std::string fileName;
    bool statistics(false);
    //Initializing program options
    po::options_description desc("Program options:");
    desc.add_options()
            ("input,i",po::value<std::string>(&fileName)->default_value("./input.json"),
             "Specify in what directory does the program search for the input.json")
            ("help,h","Produce this help message and quit.")
            ("time,t","Write out time statistics while running.");
    po::variables_map vmap;
    po::positional_options_description p;
    p.add("input", -1);
    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vmap);
    po::notify(vmap);


    //Handling program options
    if (vmap.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }else {
        if (vmap.count("time")) {
            statistics = true;
            std::cout << "Time statistics are on." << std::endl;
        }//sztem itt valami define kell
        if(vmap.count("input")){
            fileName = vmap["input"].as<std::string>();
        }
    }

    //Checking if the file exist and isn't damaged
    if(!testInput(fileName)){
        std::cerr << "The program could not find the given json file." << std::endl;
        return -1;
    }

    //Load the data into these vectors
    std::vector<MyPackage> packages;
    std::vector<MyStation> stations;
    std::vector<MyTrain> trains;
    std::vector<MyWagon> wagons;
    load(fileName,packages,stations,trains,wagons);
    std::chrono::system_clock::time_point parsed = std::chrono::system_clock::now();

    //Check whether the current problem has a solution
    if(!isDeployable(trains,stations)){
        std::cerr << "This problem has no solutions since some packages can't be shipped."
                  << std::endl;
        return -1;
    }
    std::chrono::system_clock::time_point tested = std::chrono::system_clock::now();


    //TODO: write optimization algorythm
    std::chrono::system_clock::time_point optimized = std::chrono::system_clock::now();
    //TODO: write code output
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

    if(statistics){
    //Writing out time statistics
    std::cout << "Program worked for "
              << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
              << " seconds total." << std::endl
              << "The loading and parsing of the data took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(parsed - start).count()
              << " miliseconds." << std::endl
              << "The validation of the date took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(tested - parsed).count()
              << " miliseconds" << std::endl
              << "The calculation of the optimal shiping took "
              << std::chrono::duration_cast<std::chrono::seconds>(optimized - parsed).count()
              << " seconds." << std::endl
              << "Writing out the solution took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - optimized).count()
              << " miliseconds" << std::endl;
    }
    return 0;
}
