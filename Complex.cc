#include <math.h>
#include "Complex.h"
#include <iostream>

/*** CONSTRUCTORS ***/

// Constructor (by components)
Complex::Complex(double x1, double x2){
  re_ = x1;
  im_ = x2;
}

// Copy constructor
Complex::Complex(const Complex& complex){
  re_ = complex.re_;
  im_ = complex.im_;
}

// Cartesian constructor
Complex Complex::Cartesian(double re, double im){
  return Complex(re, im);
}

// Polar constructor
Complex Complex::Polar(double rho, double phase){
  return Complex(rho*cos(phase), rho*sin(phase));
}



/*** METHODS ***/

// returns magnitude
double Complex::r() const {
  return sqrt(re_*re_ + im_ * im_);
}

// returns phase
double Complex::phi() const {
  return atan2(im_, re_);
}

/*** OPERATORS ***/

// sum
Complex Complex::operator+(const Complex& complex) const {
  return Complex::Cartesian(re_ + complex.re_, im_ + complex.im_);
}

Complex Complex::operator+(const double& rhs) const {
  return Complex::Cartesian(re_ + rhs, im_);
}

// difference
Complex Complex::operator-(const Complex& complex) const {
  return Complex::Cartesian(re_ - complex.re_, im_ - complex.im_);
}

Complex Complex::operator-(const double& rhs) const {
  return Complex::Cartesian(re_ - rhs, im_);
}

// multiplication
Complex Complex::operator*(const Complex& complex) const {
  double theta = phi() + complex.phi();
  if(theta > M_PI){
    theta -= 2*M_PI;
  }
  if(theta < -M_PI){
    theta += 2*M_PI;
  }
  
  return Complex::Polar(r()*complex.r(), theta);
}

Complex Complex::operator*(const double& rhs) const {
  return Complex::Cartesian(re_*rhs, im_*rhs);
}

// division
Complex Complex::operator/(const Complex& complex) const {
  double theta = phi() - complex.phi();

  if(theta > M_PI){
    theta -= 2*M_PI;
  }
  if(theta < -M_PI){
    theta += 2*M_PI;
  }
  
  return Complex::Polar(r()/complex.r(), theta);
}

Complex Complex::operator/(const double& rhs) const {
  return Complex::Polar(re_/rhs, im_/rhs);
}

/*** GLOBAL OVERLOADS ***/

// pretty print
ostream& operator<< (ostream& os, const Complex& z){
  using namespace std;
  os << z.re_ << " + " << z.im_ << "i";
  return os;
}

Complex operator+(const double& lhs, const Complex& rhs){
  return Complex::Cartesian(lhs + rhs.re_, rhs.im_);  
}

Complex operator-(const double& lhs, const Complex& rhs){
  return Complex::Cartesian(lhs - rhs.re_, rhs.im_);
}

Complex operator*(const double& lhs, const Complex& rhs){
  return Complex::Cartesian(rhs.re_ * lhs, rhs.im_ * lhs);
}

Complex operator/(const double& lhs, const Complex& rhs){
  return Complex::Polar(lhs / rhs.r(), - rhs.phi());
}
