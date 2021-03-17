#include "../includes/Kursach.h" 

#include <sstream>
#include <iterator>

using namespace std;

double Kursach::exactSolution(double x) {
    if (x == 0)
        return 0;
    return boardCond / x;
}

void Kursach::setSystem() {
    double n = (t - t0) / step;
    system.resize(n);
    right.resize(n);
    right[n - 1] = -boardCond / step;
    double xi = t0;
    for (size_t i = 0; i < n; i++) {
        system[i].resize(n);
        if (i == 0) {
            system[i][0] = 2 / step;
            system[i][1] = -1 / step;
        }
        else if (i == n - 1) {
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
    double n = (t - t0) / step, max = 0, tmp_t = t0;
    int maxi = 0;
    for (size_t i = 0; i < n; i++) {
        double tmp = fabs(exactSolution(tmp_t) - res[i]);
        if (tmp > max) {
            max = tmp;
            maxi = i;
        }
        tmp_t += step;
    }
    cout << maxi << endl;
    return max;
}

void Kursach::printSystem() {
    double n = (t - t0) / step;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
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
		else if (word == "step:")
			step = stod(value);
		else {
			cout << "I don't now such paramert as: \" " << word << "\"";
			fin.close();
			exit(0);
		}
	}
	fin.close();
}