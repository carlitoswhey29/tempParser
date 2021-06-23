#ifndef PARSE_TEMPS_H_INCLUDED
#define PARSE_TEMPS_H_INCLUDED

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm>
#include <utility>
#include <array>

static const int STEP_SIZE = 30;
const int MAX_CORES = 4;

using Tempearature = double;
/**
* A pair of values where the
* - _first_ attribute represents the time at which the reading was taken
* - _second is a vector with _n_ temperature readings, where _n_ is the
* number of CPU Cores.
*/
using CoreTempReading = std::pair<int, std::vector<Tempearature>>;
using TempReadingList = std::vector<CoreTempReading>;
/**
* Take an input text file and time-step size and parse all core temps.
*
* @param original_temps an input file
*
* @return a vector of 2-tuples (pairs) containing time step and core
* temperature readings.
*/
TempReadingList readTemperatureList(std::istream& ins);

/**
* Take an input readings taken from the input file and disseminates
* the data collected (temperature readings) to each core along with 
* a time slot. 
*
* @param TempReadingList vector<std::pair<int, std::vector<Tempearature>>>
* @param cored array<vector<Tempearature>, MAX_CORES>
* @param times vector<double>
*
*/
void processTemperatureReadings(const TempReadingList, std::array<std::vector<Tempearature>, MAX_CORES>&, std::vector<double>& );

#endif //PARSE_TEMPS_H_INCLUDED