#ifndef INTERPOLATE_TEMPS_H_INCLUDED
#define INTERPOLATE_TEMPS_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <iterator>
#include <cmath>
#include <sstream>

using Line = std::pair<double,double>;
using std::vector;
using std::ostream;

/**
 * Calculates a piecewise linear interpolation.
 *
 * @param argv[1] times vector<double>
 * @param argv[2] temps vector<double>
 * @param argv[3] Line Compare vector<double,double>
 */
void linear_Interpolation(vector<double>, vector<double>, vector<Line>&);

/**
 * Calculates exactly one least squares approximation line for each core.
 *
 * @param argv[1] times vector<double>
 * @param argv[2] temps vector<double>
 * @param argv[3] <total_slope,total_intercept>& std::pair<double,double>
 */
void least_Squares(vector<double>, vector<double>, std::pair<double,double>&);

/**
 * Print the total least Squares.
 *
 * @param argv[1] times vector<double>
 * @param argv[2] total_slope double
 * @param argv[3] total_intercept double
 * @param argv[4] Output File stream&
 */
void print_Least_Squares(const std::vector<double>,  const Line, std::ostream&);

/**
 * Print the linear Piecewise Interpolation.
 *
 * @param argv[1] times vector<double>
 * @param argv[2] Line Compare vector<double,double>
 * @param argv[3] Output File 
 */
void print_Interpolation(const std::vector<double>,  const std::vector<Line>, std::ostream&);

/**
 * Calculates slope.
 * @param argv[1] Y1 point
 * @param argv[2] Y0 point
 * @param argv[3] X1 point 
 * @param argv[4] X0 point
 */
template <class T>
T slope(T const& t1, T const& t2, T const& t3, T const& t4)
{
    return ((t1-t2)/(t3-t4));
}

/**
 * Calculates Y Intercept.
 * @param argv[1] Y1 point
 * @param argv[2] Y0 point
 * @param argv[3] X1 point 
 * @param argv[4] X0 point
 */
template <class T>
T y_intercept(T const& t1, T const& t2, T const& t3)
{
    return t1 - (t2 * t3);
}


#endif //INTERPOLATE_TEMPS_H_INCLUDED
