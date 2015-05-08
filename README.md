
## Synopsis
LibLocator is a Linux API for locating shared-library files and their parent directories in the filesystem.
Optionally, a specific library version can be speicified

## Motivation
The use case that led to its development is as follows:
A library needs to locate various supporting data files, either those that it defined or those
used by the libraries it is linked with, such as a time-zone databased used by boost_date_time
or a definitions file for a protocol parser. Since it's a library it cannot assume to have access to
argv[0]. Instead of making the library's user inform it where the files are placed, I prefer to make them
part of its deployment, and place them known file-system paths relative to the library's on shared-object
file. The library provides a simple API that accomplishes this on Linux.

Specifically, when the application is dynamically linked with multiple versions of the same library (a real
use-case I have to deal with), it's possible to to request the path of a specific version.

## Building
Pre-requisites:
* boost_system and boost_filesystem libraries.
  on Ubuntu Linux they can be installed using:
  sudo apt-get install libboost-filesystem-dev libboost-system-dev
* g++ that supports C++ 11, such as g++ 4.8.2 that comes with Ubuntu 14.04.
  Alternatively the code can be trivially ported to C++ 03.

the inclided build.sh will compile the code and produce a binary named 'demo'
