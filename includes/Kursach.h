# pragma once

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <fstream>
#include <iomanip>  
#define LOW 1e-6

typedef double(*func) (double x);

class Kursach {
private:
	double omega = 10e-22;
	int n, m;
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
	std::vector<double> progonka(std::vector<double> a, std::vector<double> b,
								std::vector<double> c, std::vector<double> r);
	void setPolsuchestSystem(std::vector<double> &a, std::vector<double> &b,
               std::vector<double> &c, std::vector<double> &r, std::vector<double> &eps_pols);

	void polsuchest();

    Kursach(std::string inputfile);
	void printSystem();
	void progonka();
	void progonka1();
	void setSystem();
	void setSystem1();

	void kvasi();
	void setSystemKvasi(double time);
	void kvasiProgonka();
	double kvasiRelativeError(double time);
	double kvasiResidual(double time);
	double kvasiExactSolution(double x, double t);

	void pols();
	void setSystemPols();
	void setSystemPols(double time, const std::vector<double> &e);
	void polsProgonka(std::vector<double> &u);
	double polsResidual(double time);
	double polsExactSolution(double x, double t);
	double polsRelativeError(double time);

	double residual();
	double relativeError();
	double p_t(double t);
};
