#include <iostream>
#include "Complex.h"
#include <math.h>

using namespace std;

int main(){

  Complex z = Complex::Polar(1, M_PI/4);
  Complex z2 = Complex::Polar(2, -M_PI);

  cout << "z = " << z << endl;
  cout << "z2 = " << z2 << endl;

  Complex z3 =  z / z2;

  cout << "z3 = " << z3 << endl;

  Complex z4 = 3. / z;

  cout << "z4 = " << z4 << endl;
  cout << "magn(z4) = " << z4.r() << endl;

  Complex z5 = Complex::Cartesian(1,1);
  cout << "z5 = " << z5 << endl;
  z5 /= Complex::Cartesian(1,1);
  cout << "z5 /= (1 + 1i) \t-> z5 = " << z5 << endl;
  z5 += Complex::Cartesian(1,1);
  cout << "z5 += (1 + 1i) \t-> z5 = " << z5 << endl;
  z5 -= 1;
  cout << "z5 -= 1 \t-> z5 = " << z5 << endl;
  
  
  return 0;
}
