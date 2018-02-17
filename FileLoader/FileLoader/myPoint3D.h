// Class to represent a 3D point

#ifndef myPoint3D_H
#define myPoint3D_H

#include "FileLoader/myElement.h"


class myPoint3D : public myElement {
public:
  myPoint3D(double x, double y, double z);

  myPoint3D(const myPoint3D&) = default;
  myPoint3D& operator=(const myPoint3D&) = default;

  myPoint3D operator*(double value) const;
  myPoint3D operator+(const myPoint3D& point) const;

  double x() const;
  double y() const;
  double z() const;

  virtual void draw(myDrawing& drawing) override;

  virtual ~myPoint3D() override;
private:

  // variables
  double m_x;
  double m_y;
  double m_z;
};

#endif