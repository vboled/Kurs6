#include "..\includes\Kursach.h"

using namespace std;

void setSystemForPols(vector<double> &a, vector<double> &b,
               vector<double> &c, vector<double> &r) {
        for (int i = 0; i < a.size(); i++) {
            a[i] = 1;
            b[i] = 2;
            c[i] = 3;
            r[i] = 4;
        }
}

void outPutRes(vector<double> &res, ofstream &out) {
    out << 0 << " ";
    for (int i = 0; i < res.size(); i++) {
        out << res[i] << " ";
    }
    out << endl;
}

void Kursach::setPolsuchestSystem(vector<double> &a, vector<double> &b,
               vector<double> &c, vector<double> &r, vector<double> &eps_pols) {
    double h = 1.0 / n;
    double a_i = -1 / h, b_i = 2 / h, c_i = -1 / h;
    for (int i = 0; i < a.size(); i++) {
        if (i != 0)
            a[i] = a_i;
        b[i] = b_i;
        if (i != a.size() - 1)
            c[i] = c_i;
        if (i == a.size() - 1)
            r[i] = p / e + eps_pols[i];
    }
}

void Kursach::polsuchest() {
    double tau = (t - t0) / m; // steps for mathematica
    double h = 1.0 / n;
    ofstream out("polsOut.txt");
    for (int i = 0; i < n + 1; i++) {
        out << h << " ";
    }
    out << endl;
    for (int i = 0; i < n + 1; i++) {
        out << tau << " ";
    }
    out << endl;

    vector<double> a(n), b(n), c(n), r(n), eps_pols(n), res; // create vectors

    for (int i = 0; i < m; i++) {

        setPolsuchestSystem(a, b, c, r, eps_pols); // init & solve system
        res = progonka(a, b, c, r);
        outPutRes(res, out);

        double k = -1;

        for (int j = 1; j < eps_pols.size(); j++) { // eps_pols j -> eps_pols j + 1
            eps_pols[j] = 9.0 / 4.0 * omega * tau * pow(2.0 * e / 3.0 * ((res[j] - res[j - 1]) / h - eps_pols[j]), 3) + eps_pols[j];
        }

    }
    outPutRes(res, out);
    out.close();
}