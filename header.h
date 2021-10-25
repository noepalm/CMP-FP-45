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
  ~Vector();

  //getters
  double x();
  double y();
  double z();
  double r();
  double theta();
  double phi();

  //Methods
  double mag(double x,double y,double z);
  double scalarDot();
  double vectorialDot();
  double angle();

  //setters
  void setX(double x);
  void setY(double y);
  void setZ(double z);
  void setR(double r);
  void setTheta(double theta);
  void setPhi(double phi);
  void print();


};

#endif
