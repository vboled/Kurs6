#include "..\includes\Kursach.h"

using namespace std;

int main() {
   Kursach k = Kursach("settings.txt");
   // k.setSystem1();
   // k.printSystem();
   // k.progonka1();
   // cout.precision(10);
   // cout << "residual: " << k.residual() << endl;
   // cout << "relativeError: " << k.relativeError() << endl;
   // k.kvasi();
   k.polsuchest();
   // k.printSystem();
   return 0;
}