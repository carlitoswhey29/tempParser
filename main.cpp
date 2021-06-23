#include <iostream>
#include <fstream>
#include <vector>
#include <array>

#include "parseTemps.h"
#include "interpolateTemps.h"

/**
 * //Semester Project: CPU Temperature Reading Parser
 *  Takes the temperature readings and generate for each core:
 *  -_A piecewise linear interpolation.
 *  -_A global linear least squares approximation.
 *
 * @param argv[0] - Application name
 * @param argv[1] CPU Temperatures text filename
 */
 // ./tempParser temps.txt 
int main(int argc, char** argv)
{
    // Check Command Line Arguments
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " input_file_name.txt" << "\n";
        return 1;
    }

    // Create the input stream
    std::ifstream tempFile(argv[1]);
    if (!tempFile) {
        std::cerr << "ERROR: " << argv[1] << " could not be opened" << "\n";
        return 2;
    }
    
    std::vector<double> t_times;
    std::array<std::vector<Tempearature>, MAX_CORES> t_core_n;

    // Core (i.e., main) program logic
    TempReadingList readings = readTemperatureList(tempFile);
    processTemperatureReadings(readings, t_core_n, t_times);

    // Cores 0 to 3
    for(int core_idx = 0; core_idx < MAX_CORES; core_idx++)
    {
        // Create the output stream
	    std::ofstream fout("core_" + std::to_string(core_idx) + ".txt");

        // Declare a std::pair<slope, y_inter> collection
        std::vector<Line> comp_Lines;
        
        // Compute linear interpolation
        linear_Interpolation(t_times, t_core_n[core_idx], comp_Lines);
        print_Interpolation(t_times, comp_Lines, fout );

        // Declare a std::pair<total_slope, total_y_inter>
        Line least_square_calculations;

        // compute least squares
        least_Squares(t_times, t_core_n[core_idx], least_square_calculations);
        print_Least_Squares(t_times, least_square_calculations, fout);
    }

    std::cerr<< "Task Complete ..." << std::endl;
    return 0;
}
