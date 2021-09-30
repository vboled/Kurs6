#include "..\includes\Kursach.h"

using namespace std;

void printS(const std::vector<double> &a,
                                 const std::vector<double> &b,
                                 const std::vector<double> &c,
                                 const std::vector<double> &r) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < i; j++) {
            cout << setw(2) << "0 ";
        }
        if (i != 0)
            cout << a[i] << " ";
        cout << b[i] ;
        if (i != a.size() - 1)
            cout <<" " << c[i] << " ";
        for (int j = a.size() - i - 1; j > 0; j--) {
            cout << setw(2) << "0 ";
        }
        cout << " = " << r[i] << endl;
    }
}

vector<double> Kursach::progonka(std::vector<double> a,
                                 std::vector<double> b,
                                 std::vector<double> c,
                                 std::vector<double> f) {
    vector<double> res(a.size());
    double m;
	for (int i = 1; i < n; i++)
	{
		m = a[i]/b[i-1];
		b[i] = b[i] - m*c[i-1];
		f[i] = f[i] - m*f[i-1];
	}

	res[n-1] = f[n-1]/b[n-1];

	for (int i = n - 2; i >= 0; i--)
    {
		res[i]=(f[i]-c[i]*res[i+1])/b[i];
    }        
    
    return res;
}