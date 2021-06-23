//interpolateTemps.cpp

#include "interpolateTemps.h"

void linear_Interpolation(std::vector<double> times, 
     std::vector<double> temps, std::vector<Line>& comp_Lines)
{
    const unsigned int num_lines = times.size() - 1;
    for (unsigned int i = 0; i < num_lines; ++i)
    {
        double mx = slope(temps[i+1], temps[i], times[i+1], times[i]);
        double x_inter = times[i];
        double y_inter = y_intercept(temps[i] , mx, x_inter);
        comp_Lines.push_back({mx, y_inter});
    }
}

void least_Squares(std::vector<double> times_X, 
    std::vector<double> temps_Y, Line &least_square_calculations)
{
    using std::setw;

    std::vector<double> y_fit;

    const unsigned int num_line = times_X.size() - 1;
    double xsum=0, x2sum=0, ysum=0, xysum=0;
    double total_slope, total_intercept, y_fitnum;

    for(unsigned int i=0; i < num_line; ++i )
    {
        xsum = xsum + times_X[i];
        ysum = ysum + temps_Y[i];
        x2sum = x2sum + pow(times_X[i], 2);
        xysum = xysum + times_X[i] * temps_Y[i];
    }

    // (num_line * xysum - xsum * ysum)/(num_line * x2sum - xsum * xsum);
    total_slope = slope((num_line * xysum), (xsum * ysum), (num_line * x2sum), pow(xsum, 2));
    total_intercept = (x2sum * ysum - xsum * xysum)/(x2sum * num_line - xsum * xsum);
    least_square_calculations = {total_slope, total_intercept};

    for(unsigned int i = 0; i < num_line; ++i)
    {
        y_fitnum = total_slope * times_X[i] + total_intercept;
        y_fit.push_back(y_fitnum);
    }
}

void print_Least_Squares(const std::vector<double> times_X,  
    const Line least_square_calculations, std::ostream& outs)
{
    using std::setw;

    const unsigned int num_line = times_X.size() -1;
    outs <<  std::left << setw(5) <<  times_X[0] << setw(8) << " <= x <= "
        << std::right <<  setw(6) << times_X[num_line] << "; "
        << "y = " << setw(8) << least_square_calculations.first << "x + " 
        << setw(8) << least_square_calculations.second <<";"
        << setw(38)  <<  " Least Squares Approximation";
}

void print_Interpolation(const std::vector<double> times,  
    const std::vector<Line> comp_Lines, std::ostream& outs)
{
    using std::setw;
    const unsigned int num_line = times.size() -1;
    for (unsigned int i = 0; i < num_line; ++i)
    {
        outs <<  std::left << setw(6) <<  times[i] << setw(8) << "<= x <="
            << std::right << setw(6) << times[i+1] << "; "
            << std::left << setw(2) << "y_" << i << setw(3) <<" = " 
            << std::right << setw(6) << comp_Lines[i].second 
            << " + "  << setw(10) 
            << comp_Lines[i].first << "x;"
            << setw(38)  << " Piecewise Linear Interpolation" << std::endl;
    }
}