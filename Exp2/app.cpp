#include <stdio.h>
#include <iostream>
#include "header.h"

using namespace std;

int main(){

  // Vector v1 = Vector::Cartesian(1,0,0);
  // Vector v2 = Vector::Cartesian(0,1,0);
  
  // Vector v3 = Vector::vectorProduct(v1, v2);

  // cout << "v1 = " << v1 << endl;
  // cout << "v2 = " << v2 << endl;
  // cout << "v3 = " << v3 << endl;

  Vector v1(1,1,1);
  Vector v2(3,0,0);
  double cdot=0;
  cdot=Vector::scalarProduct(v1,v2);
  cout<<cdot<<endl;
  double angle=Vector::angle(v1,v2);
  cout<<angle<<endl;
  float rhs=1;
  Vector v3=v1*2.4;
  cout<<v3.x()<<v3.y()<<v3.z()<<endl;
  
  return 0;

}
