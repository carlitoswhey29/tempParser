// parseTemps.cpp

#include "parseTemps.h"

TempReadingList readTemperatureList(std::istream& ins)
{
    TempReadingList readings;

    // Input Parsing Variables
    int step = 0;
    std::string line;

    while (getline(ins, line)) {
      
        std::istringstream input(line);
        std::vector<Tempearature> next_temperature_set;

        std::transform(
            std::istream_iterator<std::string>(input),
            std::istream_iterator<std::string>(),
            std::back_inserter(next_temperature_set),
        
            [](const std::string& raw_reading) -> Tempearature {
            return stod(raw_reading);
            });

        readings.emplace_back(step, next_temperature_set);
        step += STEP_SIZE;
    }
    return readings;
}

void processTemperatureReadings(const TempReadingList readings, std::array<std::vector<Tempearature>, MAX_CORES>& t_core_n, std::vector<double>& t_times)
{
    for(const CoreTempReading& TempReading : readings)
    {
        const std::vector<Tempearature>& coreTemps = TempReading.second;
        t_times.push_back(TempReading.first);
        t_core_n[0].push_back(coreTemps[0]);
        t_core_n[1].push_back(coreTemps[1]);
        t_core_n[2].push_back(coreTemps[2]);
        t_core_n[3].push_back(coreTemps[3]);
    }
}