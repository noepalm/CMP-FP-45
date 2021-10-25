#include <math.h>
#include "Complex.h"
#include <iostream>


/*** CONSTRUCTORS ***/

// Constructor (by components)
Complex::Complex(double x1, double x2){
  re_ = x1;
  im_ = x2;
  r_ = sqrt(re_*re_ + im_ * im_);
  phi_ = atan2(im_, re_);
}

// Copy constructor
Complex::Complex(const Complex& complex){
  re_ = complex.re_;
  im_ = complex.im_;
  r_ = complex.r_;
  phi_ = complex.phi_;
}

// Cartesian constructor
Complex Complex::Cartesian(double re, double im){
  return Complex(re, im);
}

// Polar constructor
Complex Complex::Polar(double rho, double phase){
  return Complex(rho*cos(phase), rho*sin(phase));
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
  double theta = phi_ + complex.phi_;
  if(theta > M_PI){
    theta -= 2*M_PI;
  }
  if(theta < -M_PI){
    theta += 2*M_PI;
  }
  
  return Complex::Polar(r_*complex.r_, theta);
}

Complex Complex::operator*(const double& rhs) const {
  return Complex::Cartesian(re_*rhs, im_*rhs);
}

// division
Complex Complex::operator/(const Complex& complex) const {
  double theta = phi_ - complex.phi_;

  if(theta > M_PI){
    theta -= 2*M_PI;
  }
  if(theta < -M_PI){
    theta += 2*M_PI;
  }
  
  return Complex::Polar(r_/complex.r_, theta);
}

Complex Complex::operator/(const double& rhs) const {
  return Complex::Polar(re_/rhs, im_/rhs);
}

// assignment (=)
Complex Complex::operator=(const Complex& complex) {
  re_ = complex.re_;
  im_ = complex.im_;
  r_ = complex.r_;
  phi_ = complex.phi_;

  return *this;
}

Complex Complex::operator=(const double& rhs) {
  re_ = rhs;
  im_ = 0;
  r_ = rhs;
  phi_ = 0;

  return *this;
}

// sum + assignment (+=)
Complex Complex::operator+=(const Complex& complex) {
  re_ += complex.re_;
  im_ += complex.im_;
  r_ = sqrt(re_*re_ + im_ * im_);
  phi_ = atan2(im_, re_);

  return *this;
}

Complex Complex::operator+=(const double& rhs) {
  re_ += rhs;
  r_ = sqrt(re_*re_ + im_ * im_);
  phi_ = atan2(im_, re_);

  return *this;
}

// minus + assignment (-=)
Complex Complex::operator-=(const Complex& complex) {
  re_ -= complex.re_;
  im_ -= complex.im_;
  r_ = sqrt(re_*re_ + im_ * im_);
  phi_ = atan2(im_, re_);

  return *this;
}

Complex Complex::operator-=(const double& rhs) {
  re_ -= rhs;
  r_ = sqrt(re_*re_ + im_ * im_);
  phi_ = atan2(im_, re_);

  return *this;
}

// product + assignment (*=)
Complex Complex::operator*=(const Complex& complex){
  r_ *= complex.r_;

  double theta = phi_ + complex.phi_;
  if(theta > M_PI){
    theta -= 2*M_PI;
  }
  if(theta < -M_PI){
    theta += 2*M_PI;
  }

  phi_ = theta;

  re_ = r_*cos(phi_);
  im_ = r_*sin(phi_);

  return *this;
}

Complex Complex::operator*=(const double& rhs){
  r_ *= rhs;

  re_ *= rhs;
  im_ *= rhs;

  return *this;
}

// division + assignment (/=)
Complex Complex::operator/=(const Complex& complex){
  r_ /= complex.r_;

  double theta = phi_ - complex.phi_;
  if(theta > M_PI){
    theta -= 2*M_PI;
  }
  if(theta < -M_PI){
    theta += 2*M_PI;
  }
  
  phi_ = theta;

  re_ = r_*cos(phi_);
  im_ = r_*sin(phi_);

  return *this;
}

Complex Complex::operator/=(const double& rhs){
  r_ /= rhs;

  re_ /= rhs;
  im_ /= rhs;

  return *this;
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
  return Complex::Polar(lhs / rhs.r_, - rhs.phi_);
}
