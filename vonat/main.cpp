#include <boost/chrono.hpp>
#include <boost/program_options.hpp>
#include <iostream>

#include "mypackage.hpp"
#include "mystation.hpp"
#include "mytrain.hpp"
#include "mywagon.hpp"

namespace po = boost::program_options;

int main(int argc,  char* argv[])
{
    po::options_description desc("Program options:");
    desc.add_options()
            ("input","Specify in what directory does the program search for the input.json")
            ("help","Produce this help message and quit.")
            ("time","Write out time statistics while running.");

    po::variables_map vmap;
    po::store(po::parse_command_line(argc, argv, desc), vmap);


    if (vmap.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }else {
        if (vmap.count("time")) {
            std::cout << "Time statistics are on." << std::endl;
            return 0;
        }//sztem itt valami define kell
        if(vmap.count("input")){
            //TODO: write algorythm
        }

    }

    std::cout << "Hello World!" << std::endl;
    return 0;
}
