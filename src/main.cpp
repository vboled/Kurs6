#include "../includes/Kursach.h"

using namespace std;


int main() {
   Kursach k = Kursach("settings.txt");
   k.setSystem();
   k.progonka();
   cout.precision(10);
   cout << "residual " << k.residual();
   return 0;
}