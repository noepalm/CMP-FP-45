#ifndef Complex_h
#define Complex_h

#include <iostream>
using namespace std;

class Complex {
 private:
  double re_;
  double im_;
  double r_;
  double phi_;
  
  // constructor (by components)
  Complex(double x1, double x2);
  
 public:
  // copy constructor
  Complex(const Complex& complex);
  
  // constructor when providing real and imaginary part
  static Complex Cartesian(double re, double im);

  // constructor when providing radius and phase
  static Complex Polar(double rho, double phase);

  // getters
  double re() const {return re_;}
  double im() const {return im_;}
  double r() const {return r_;};
  double phi() const {return phi_;};
  
  // setters
  void setRe(double re) {re_ = re;}
  void setIm(double im) {im_ = im;}
  void setR(double r) {r_ = r;}
  void setPhi(double phi) {phi_ = phi;}

  // overloaded operators
  Complex operator+(const Complex& complex) const;
  Complex operator-(const Complex& complex) const;
  Complex operator*(const Complex& complex) const;
  Complex operator/(const Complex& complex) const;

  Complex operator+(const double& rhs) const;
  Complex operator-(const double& rhs) const;
  Complex operator*(const double& rhs) const;
  Complex operator/(const double& rhs) const;

  Complex operator=(const Complex& rhs);
  Complex operator+=(const Complex& rhs);
  Complex operator-=(const Complex& rhs);
  Complex operator*=(const Complex& rhs);
  Complex operator/=(const Complex& rhs);
  
  Complex operator=(const double& rhs);
  Complex operator+=(const double& rhs);
  Complex operator-=(const double& rhs);
  Complex operator*=(const double& rhs);
  Complex operator/=(const double& rhs);

  // global overloads
  friend ostream& operator<< (ostream& os, const Complex& rhs);
  friend Complex operator+(const double& lhs, const Complex& rhs);
  friend Complex operator-(const double& lhs, const Complex& rhs);  
  friend Complex operator*(const double& lhs, const Complex& rhs);
  friend Complex operator/(const double& lhs, const Complex& rhs);
};

#endif
