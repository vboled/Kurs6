#include "../includes/Kursach.h"

using namespace std;

int main() {
   Kursach k = Kursach("settings.txt");
   k.setSystem();
   k.printSystem();
   k.progonka();
   cout.precision(10);
   cout << "residual: " << k.residual() << endl;
   cout << "relativeError: " << k.relativeError() << endl;
   return 0;
}