#include "..\includes\Kursach.h"

using namespace std;

double Kursach::p_t(double t) {
    return p * t;
}

double Kursach::kvasiExactSolution(double x, double t) {
    if (x == 0)
        return 0;
    return p_t(t) / e * x;
}

void Kursach::setSystemKvasi(double time) {
    double step = (t - t0) / n;
    b.resize(n + 1);
    c.resize(n + 1);
    a.resize(n + 1);
    right.resize(n + 1);
    right[n] = p_t(time) / e;
    double xi = t0;
    for (size_t i = 0; i < n + 1; i++) {
        if (i == 0) {
            b[0] = 2 / step;
            c[0] = -1 / step;
        }
        else if (i == n) {
            b[i] = 1 / step;
            a[i] = -1 / step;
        }
        else {
            a[i] = -1 / step;
            b[i] = 2 / step;
            c[i] = -1 / step;
        }
    }
}

void Kursach::kvasiProgonka() {
    ofstream out("kvasiOut.txt", std::ios::app);
	if (!out.is_open()) {
        cout << "Output file doesn't open!!!";
        exit(0);
    }
    double step = (t - t0) / n;
    double m = b[0];
    vector<double> alpha(n + 1), beta(n + 1);
    res.resize(n + 1);
    alpha[0] = -c[0] / m;
    beta[0] = right[0] / m;
	for (int i = 1; i <= n; i++)
	{
		m = b[i] + a[i] * alpha[i - 1];
        alpha[i] = -c[i] / m;
        beta[i] = (right[i] - a[i] * beta[i - 1]) / m;
	}

	res[n] = beta[n];

	for (int i = n; i >= 0; i--)
    {
		res[i] = alpha[i] * res[i + 1] + beta[i];
    }

    res.insert(res.begin(), initCond);

    double tmp_t = t0;
    for (int i = 0; i < n + 1; i++) {
        out << res[i] << " ";
        tmp_t += step;
    }
    out << endl;
	out.close();
}

double Kursach::kvasiResidual(double time) {
    double step = (t - t0) / n, max = 0, tmp_t = t0;
    int maxi = 0;
    for (size_t i = 0; i < res.size(); i++) {
        tmp_t += step;
        double tmp = fabs(kvasiExactSolution(tmp_t, time) - res[i]);
        if (tmp > max) {
            max = tmp;
        }
    }
    return max;
}

double Kursach::kvasiRelativeError(double time) {
    double step = (t - t0) / n, max = 0, tmp_t = t0;
    for (size_t i = 0; i < res.size(); i++) {
        if (kvasiExactSolution(tmp_t, time) != 0.0) {
            double tmp = fabs(kvasiExactSolution(tmp_t, time) - res[i]) / fabs(kvasiExactSolution(tmp_t, time));
            if (tmp > max)
                max = tmp;
        }
        tmp_t += step;
    }
    return max;
}

void Kursach::kvasi() {
    double tau = (t - t0) / m;
    double h = 1.0 / n;
    ofstream out("kvasiOut.txt");
    for (int i = 0; i < n + 1; i++) {
        out << h << " ";
    }
    out << endl;
    for (int i = 0; i < n + 1; i++) {
        out << tau << " ";
    }
    out << endl;
    out.close();
    for (int i = 0; i <= m; i++) {
        cout << "time = " << setw(3) << tau * i;
        setSystemKvasi(tau * i);
        kvasiProgonka();
        cout << ", absoluteError: " << setw(9) << kvasiResidual(tau * i);
        cout << ", relativeError: " << kvasiRelativeError(tau * i);
        cout << endl;
    }
}