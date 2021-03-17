#include "../includes/Kursach.h"

using namespace std;

void Kursach::progonka() {
    // ofstream out(outputFile);
	// if (!out.is_open()) {
    //     cout << "Output file doesn't open!!!";
    //     exit(0);
    // }
    double n = (t - t0) / step, tmp;
    vector<double> a, b;
    a.resize(n);
    b.resize(n);
    tmp = system[0][0];
    a[0] = -system[0][1] / tmp;
    b[0] = right[0] / tmp;
    // прямой ход
    for (size_t i = 0; i < n - 1; i++) {
        tmp = system[i][i] + system[i][i - 1] * a[i - 1];
        a[i] = -system[i][i + 1] / tmp;
        b[i] = (right[i] - system[i][i - 1] * b[i - 1]) / tmp;
    }
	// обратный ход
    res.resize(n);
    res[n - 1] = (right[n - 1] - system[n - 1][n - 1 - 1] * b[n - 1 - 1])
    / (system[n - 1][n - 1] + system[n - 1][n - 1 - 1] * a[n - 1 - 1]);
    // out << t << " " << res[n - 1] << endl;
    double tmp_t = t;
    for (int i = n - 2; i >= 0; i--) {
        tmp_t -= step;
        res[i] = a[i] * res[i + 1] + b[i];
        // out << tmp_t << " " << res[i] << endl;
    }
	// out.close();
}