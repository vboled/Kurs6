#include "../includes/Kursach.h"

using namespace std;

void Kursach::progonka() {
    ofstream out(outputFile);
	if (!out.is_open()) {
        cout << "Output file doesn't open!!!";
        exit(0);
    }
    double step = (t - t0) / n;
    double m = b[0];
    vector<double> alpha(n + 1), beta(n + 1);
    res.resize(n - 1);
    alpha[0] = -c[0] / m;
    beta[0] = right[0] / m;
	for (int i = 1; i <= n; i++)
	{
		m = b[i] + a[i] * alpha[i - 1];
        alpha[i] = -c[i] / m;
        beta[i] = (right[i] - a[i] * beta[i - 1]) / m;
	}

	res[n - 2] = beta[n];

	for (int i = n - 3; i >= 0; i--)
    {
		res[i] = alpha[i] * res[i + 1] + beta[i];
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