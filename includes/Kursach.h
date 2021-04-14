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
	int n;
	double t0;
	double t;
	double e, p;
	std::string outputFile;
	double initCond;
	double boardCond;
	std::vector<double> b; // главная диагональ
	std::vector<double> a; // диагональ над главной
	std::vector<double> c; // диагональ под главной
	std::vector<std::vector<double> > system;
	std::vector<double> right;
	std::vector<double> res;
	double exactSolution(double x);

public:
    Kursach(std::string inputfile);
	void printSystem();
	void progonka();
	void setSystem();
	void setSystem1();
	double residual();
	double relativeError();
};
