## yconfig ##
A simple YAML configuration wrapper for C++.

yconfig is a configuration wrapper built around the [yaml-cpp](http://code.google.com/p/yaml-cpp/) library and is distributed under the MIT license.<br />
It is a companion project to the chapter "_YAML for C++: Applied Data-Driven Design_" of the book [Game Development Tools](http://gamedevelopmenttools.com/).

### Building yconfig ###

yconfig requires [CMake](http://cmake.org) and the [yaml-cpp](http://code.google.com/p/yaml-cpp/) library (auto-detected by CMake) to be built.

    $ cd yconfig
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

You should now have the yconfig headers and library files, directly integrable into your C++ project.<br />
To run the test examples described in the book chapter, you can type the following:

    $ cd ..
    $ build/configtest

### Using yconfig ###

    #include "Config.h"

    std::ifstream file("configfile.yaml");
    Config cfg(file); // throws an exception if the stream is unreadable

    unsigned int width = cfg["screen/width"];
    unsigned int width = cfg["screen/height"];
    // use width and height to initialize the screen...

    std::vector<Player> players = cfg["players"];
    // iterate over the players list here...
