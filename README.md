# Simulator for Methods of Indoor Localization

[![Build Status](https://travis-ci.org/goofacz/smile.svg?branch=master)](https://travis-ci.org/goofacz/smile)

SMILe allows analyzing and evaluating arbitrary indoor localization methods based on time measurements. Project is a framework built on top of [OMNeT++](https://omnetpp.org/) and heavily utilizes [INET](https://github.com/inet-framework/inet).

## Installation

1. Make sure you have C++ compiler supporting C++14 installed on your platform.
2. Install OMNeT++ 5.2 (or newer). After extracting tarball remember to edit file `configure.user`. Open it and uncomment variable `CXXFLAGS` and assign it with value `-std=c++14`.
3. Install INET 3.6.2 (or newer).
4. Install Python 3.6 and required packages (listed in pip's `requirements.txt`)
5. Checkout SMILe. **Important note:** Remember to checkout SMILe next to INET.
6. Add path to SMILe's `python` directory to `PYTHONPATH` environment variable

## Authors

Tomasz Jankowski, MSc

Maciej Nikodem, PhD


SMILe is developed at [Wrocław University of Science and Technology](http://pwr.edu.pl/).
