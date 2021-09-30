#include "../includes/Kursach.h"

using namespace std;

double Kursach::polsResidual(double time) {
    double step = (t - t0) / n, max = 0, tmp_t = t0;
    int maxi = 0;
    // for (size_t i = 0; i < res.size(); i++) {
    //     tmp_t += step;
    //     double tmp = fabs(kvasiExactSolution(tmp_t, time) - res[i]);
    //     if (tmp > max) {
    //         max = tmp;
    //     }
    // }
    return max;
}

double Kursach::polsExactSolution(double x, double t) {
    // if (x == 0)
    //     return 0;
    // return p_t(t) / e * x;
    return 0;
}

double Kursach::polsRelativeError(double time) {
    double step = (t - t0) / n, max = 0, tmp_t = t0;
    // for (size_t i = 0; i < res.size(); i++) {
    //     if (kvasiExactSolution(tmp_t, time) != 0.0) {
    //         double tmp = fabs(kvasiExactSolution(tmp_t, time) - res[i]) / fabs(kvasiExactSolution(tmp_t, time));
    //         if (tmp > max)
    //             max = tmp;
    //     }
    //     tmp_t += step;
    // }
    return max;
}

void Kursach::setSystemPols(double time, const vector<double> &pols) {
    double step = (t - t0) / n;
    b.resize(n + 1);
    c.resize(n + 1);
    a.resize(n + 1);
    right.resize(n + 1);
    double xi = t0;
    for (size_t i = 0; i < n + 1; i++) {
        if (i == 0) {
            b[0] = 2.0 / step;
            c[0] = -1.0 / step;
        }
        else if (i == n) {
            b[i] = 1.0 / step;
            a[i] = -1.0 / step;
            right[i] = pols[i] + p / e;
        }
        else {
            a[i] = -1.0 / step;
            b[i] = 2.0 / step;
            c[i] = -1.0 / step;
        }
    }
}


void Kursach::polsProgonka(vector<double> &u) {
    ofstream out("polsOut.txt", std::ios::app);
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
        u[i] = res[i];
        out << res[i] << " ";
        tmp_t += step;
    }
    out << endl;
	out.close();
}

void Kursach::pols() {
    double tau = (t - t0) / m;
    double h = 1.0 / n;
    vector<double> u(n + 1), pols(n + 1);
    ofstream out("polsOut.txt");
    for (int i = 0; i < n + 1; i++) {
        out << h << " ";
    }
    out << endl;
    for (int i = 0; i < n + 1; i++) {
        out << tau << " ";
    }
    out << endl;
    out.close();
    setSystemPols(0, pols);
    polsProgonka(u);
    for (int i = 0; i <= m; i++) {
        cout << "time: " << tau * i << endl;
        for (int j = 0; j <= n; j++) {
            double eps_j = 0;
            if (j == n)
                eps_j = u[j] / h;
            cout << "eps_j: " << eps_j << " "; 
            double sigma = e * (eps_j - pols[j]);
            cout << "sigma: " << sigma << " ";
            pols[j] += 9.0 * tau / 4.0 * omega * pow(2.0 / 3.0 * sigma, 3);
            cout << "u: " << u[j] << endl;
        }
        setSystemPols(tau * i, pols);
        polsProgonka(u);
        cout << endl;
        cout << endl;
    }
}