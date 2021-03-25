#include "../includes/Kursach.h" 

#include <sstream>
#include <iterator>

using namespace std;

double Kursach::exactSolution(double x) {
    if (x == 0)
        return 0;
    return boardCond * x;
}

void Kursach::setSystem() {
    double step = (t - t0) / n;
    system.resize(n + 1);
    right.resize(n + 1);
    right[n] = boardCond / step;
    double xi = t0;
    for (size_t i = 0; i < n + 1; i++) {
        system[i].resize(n + 1);
        if (i == 0) {
            system[i][0] = 2 / step;
            system[i][1] = -1 / step;
        }
        else if (i == n) {
            system[i][i - 1] = -1 / step;
            system[i][i] = 2 / step;
        }
        else {
            system[i][i - 1] = -1 / step;
            system[i][i] = 2 / step;
            system[i][i + 1] = -1 / step;
        }
    }
}

double Kursach::residual() {
    double step = (t - t0) / n, max = 0, tmp_t = t0;
    int maxi = 0;
    for (size_t i = 0; i < n; i++) {
        tmp_t += step;
        double tmp = fabs(exactSolution(tmp_t) - res[i]);
        if (tmp > max) {
            max = tmp;
        }
    }
    return max;
}

double Kursach::relativeError() {
    double step = (t - t0) / n, max = 0, tmp_t = t0;
    for (size_t i = 0; i < n + 1; i++) {
        if (exactSolution(tmp_t) != 0.0) {
            double tmp = fabs(exactSolution(tmp_t) - res[i]) / fabs(exactSolution(tmp_t));
            if (tmp > max)
                max = tmp;
        }
        tmp_t += step;
    }
    return max;
}

void Kursach::printSystem() {
    double step = (t - t0) / n;
    for (size_t i = 0; i < n + 1; i++) {
        for (size_t j = 0; j < n + 1; j++) {
            cout << system[i][j] << " ";
        }
        cout << " | " << right[i] << endl;
    }
}

Kursach::Kursach(string inputFile) {
    ifstream fin(inputFile);
	if (!fin.is_open()) {
		cout << "File doesn't open!!!";
		exit(0);
	}
	string word, value;
    while (fin >> word) {
		fin >> value;
		if (word == "t0:")
			t0 = stoi(value);
		else if (word == "t1:")
			t = stoi(value);
		else if (word == "initCond:")
			initCond = stod(value);
        else if (word == "boardCond:")
			boardCond = stod(value);
		else if (word == "outputFile:")
			outputFile = value;
		else if (word == "N:")
			n = stoi(value);
		else {
			cout << "I don't now such paramert as: \" " << word << "\"";
			fin.close();
			exit(0);
		}
	}
	fin.close();
}