# pragma once

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <fstream>
#define LOW 1e-6

typedef double(*func) (double x);

class Kursach {
private:
	double step;
	double t0;
	double t;
	std::string outputFile;
	double initCond;
	double boardCond;
	std::vector<std::vector<double> > system;
	std::vector<double> right;
	std::vector<double> res;
	double exactSolution(double x);
	func f;

public:
    Kursach(std::string inputfile);
	void printSystem();
	void progonka();
	void setSystem();
	double residual();
	double relativeError();
};
