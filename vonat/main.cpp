#include <chrono>
#include <boost/program_options.hpp>
#include <iostream>

#include "mypackage.hpp"
#include "mystation.hpp"
#include "mytrain.hpp"
#include "mywagon.hpp"

namespace po = boost::program_options;

int main(int argc,  char* argv[])
{
    std::cout << "The program strated" << std::endl;
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    std::string fileName;

    //Initializing program options
    po::options_description desc("Program options:");
    desc.add_options()
            ("input,i",po::value<std::string>(&fileName)->default_value("~"),
             "Specify in what directory does the program search for the input.json")
            ("help,h","Produce this help message and quit.")
            ("time,t","Write out time statistics while running.");
    po::variables_map vmap;
    po::positional_options_description p;
    p.add("input ", -1);
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
            return 0;
        }//sztem itt valami define kell
        if(vmap.count("input")){
            fileName = vmap["input"].as<std::string>();
        }
    }


    std::chrono::system_clock::time_point parsed = std::chrono::system_clock::now();

    std::chrono::system_clock::time_point optimized = std::chrono::system_clock::now();

    std::chrono::system_clock::time_point wrote = std::chrono::system_clock::now();


    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

    //Writing out time statistics
    std::cout << "Program worked for "
              << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
              << " seconds total." << std::endl
              << "The loading and parsing of the data took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(parsed - start).count()
              << " miliseconds." << std::endl
              << "The calculation of the optimal shiping took "
              << std::chrono::duration_cast<std::chrono::seconds>(optimized - parsed).count()
              << " seconds." << std::endl
              << "Writing out the solution took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - wrote).count()
              << " miliseconds" << std::endl;

    return 0;
}
