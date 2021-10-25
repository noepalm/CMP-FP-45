#include <stdio.h>
#include <iostream>
#include "header.h"
#include <cmath>

using namespace std;
//using std::cout;
//using std::endl;

//Constructors

Vector::Vector(){
  x_=0;
  y_=0;
  z_=0;
}
Vector::Vector(double x,double y,double z){
  x_=x;
  y_=y;
  z_=z;
}

Vector Vector::Cartesian(double x,double y,double z){
  return Vector(x,y,z);
}

Vector Vector::Polar(double r,double theta,double phi){
  return Vector(r*sin(theta)*cos(phi),r*sin(theta)*sin(phi),r*cos(theta));
}

//Deconstructor



//getters
double Vector::x(){
  return x_;
}
double Vector::y(){
  return y_;
}
double Vector::z(){
  return z_;
}

double Vector::r(){
  return sqrt(pow(x_,2)+pow(y_,2)+pow(z_,2));
}

double Vector::theta(){
  double rho=sqrt(pow(x_,2)+pow(y_,2)+pow(z_,2));
  if(y_/rho <-1 || y_/rho > 1){
    cout<<"**NON E POSSIBILE CALCOLARE THETA PER QUESTI VALORI DI X E Y**"<<endl;
    return -1;
      }
  else{
    return acos(y_/rho);//radians
  }
}
double Vector::phi(){
  double Phi=0;

  if(x_==0 && y_>0){Phi=M_PI_2;}
  else if(x_==0 && y_<0){Phi=-M_PI_2;}
  else if(x_==0 && y_==0){
    cout<<"PHI non definita per questi valori di x_ ed y_"<<endl;
  }
  else if(x_>0){Phi=atan(y_/x_);}
  else if(x_<0 && y_>=0){Phi=atan(y_/x_)+M_PI;}
  else if(x_<0 && y_<0){Phi=atan(y_/x_)-M_PI;}

  return Phi;
}
//Methods


//double mag(Vector& vector){
//return sqrt(pow(Vector::vector.x,2)+pow(Vector::vector.y,2)+pow(Vector::vector.z,2));
//}

//setters
void Vector::setX(double x){
  x_=x;
}
void Vector::setY(double y){
  y_=y;
}
void Vector::setZ(double z){
  z_=z;
}

			  

