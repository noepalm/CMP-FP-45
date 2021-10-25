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

/*** METHODS ***/

double Vector::mag(){
  return this->r();
}

double Vector::scalarProduct(const Vector& vector1, const Vector& vector2){
  return vector1.x_*vector2.x_+vector1.y_*vector2.y_+vector1.z_*vector2.z_;
}
double Vector::angle( Vector& vector1, Vector& vector2){
  return acos(scalarProduct(vector1,vector2)/(vector1.r()*vector2.r()));
}

// vector product
// (calculated as (y1*z2 - z1*y2, z1*x2 - x1*z2, x1*y2 - y1*x2))
Vector Vector::vectorProduct(Vector v1, Vector v2){
  return Vector::Cartesian(v1.y_*v2.z_ - v1.z_*v2.y_, v1.z_*v2.x_ - v1.x_*v2.z_, v1.x_*v2.y_ - v1.y_*v2.x_);
}

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

/*** OVERLOADED OPERATORS ***/
Vector Vector::operator+(Vector rhs) const{
  return Vector::Cartesian(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_);
}

Vector Vector::operator-(Vector rhs) const{
  return Vector::Cartesian(x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_);
}

Vector Vector::operator*(const float& rhs)const{
  return Vector::Cartesian(x_*rhs,y_*rhs,z_*rhs);
}
Vector Vector::operator/(const float& rhs)const{
  return Vector::Cartesian(x_/rhs,y_/rhs,z_/rhs);
}
			  
Vector Vector::operator=(Vector rhs){
  x_ = rhs.x_;
  y_ = rhs.y_;
  z_ = rhs.z_;

  return *this;
}

/*** GLOBAL OVERLOAD ***/

ostream& operator<<(ostream& os, const Vector& v){
  os << "(" << v.x_ << ", " << v.y_ << ", " << v.z_ << ")";
  return os;
}