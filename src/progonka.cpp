#include "../includes/Kursach.h"

using namespace std;

void Kursach::progonka() {
    ofstream out(outputFile);
	if (!out.is_open()) {
        cout << "Output file doesn't open!!!";
        exit(0);
    }
    double step = (t - t0) / n;
    double tmp;
    vector<double> a, b;
    a.resize(n + 1);
    b.resize(n + 1);
    tmp = system[0][0];
    a[0] = -system[0][1] / tmp;
    b[0] = right[0] / tmp;
    // прямой ход
    for (size_t i = 0; i <= n; i++) {
        tmp = system[i][i] + system[i][i - 1] * a[i - 1];
        a[i] = -system[i][i + 1] / tmp;
        b[i] = (right[i] - system[i][i - 1] * b[i - 1]) / tmp;
    }
	// обратный ход
    res.resize(n - 1);
    res[n - 2] = b[n];
    for (int i = n - 3; i >= 0; i--) {
        res[i] = a[i] * res[i + 1] + b[i];
    }
    res.insert(res.begin(), initCond);
    res.push_back(boardCond);
    double tmp_t = t0;
    for (int i = 0; i < n + 1; i++) {
        out << tmp_t << " " << res[i] << endl;
        tmp_t += step;
    }
	out.close();
}