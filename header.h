#ifndef header_h
#define header_h

class Vector{
 private:
  double x_;
  double y_;
  double z_;

 public:
  //Constructor
  Vector();
  Vector(double x,double y,double z);
  //Constructor -- Cartesian
  static Vector Cartesian(double x,double y,double z);
  //Constructor -- Polar
  static Vector Polar(double r,double theta,double phi);

  //Deconstructor
  // ~Vector();

  //getters
  double x();
  double y();
  double z();
  double r();
  double theta();
  double phi();
  double mag();

  //Methods
  double mag(double x,double y,double z);
  double scalarDot();
  double angle();
  
  static double scalarProduct(const Vector& vector1,const Vector& vector2);
  static double angle(Vector& vector1,Vector& vector2);
  static Vector vectorProduct(Vector v1, Vector v2);
  

  //setters
  void setX(double x);
  void setY(double y);
  void setZ(double z);
  void setR(double r);
  void setTheta(double theta);
  void setPhi(double phi);
  void print();

  // OVERLOADED OPERATORS
  Vector operator+(Vector rhs) const;
  Vector operator-(Vector rhs) const;
  
  //Overload operators * / multiply and divide by a float
  Vector operator*(const float& rhs) const;
  Vector operator/(const float& rhs) const;
  Vector operator=(Vector rhs);
  
  friend std::ostream& operator<< (std::ostream& os, const Vector& v);

};

#endif
