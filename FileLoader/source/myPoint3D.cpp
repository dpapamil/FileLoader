
#include "FileLoader/myPoint3D.h"
#include "assert.h"
#include "FileLoader/myDrawing.h"


//============================================================================
myPoint3D::myPoint3D(double x, double y, double z)
  : m_x(x), 
	m_y(y),
	m_z(z)
{

}

//============================================================================
myPoint3D::~myPoint3D()
{

}

//============================================================================
myPoint3D myPoint3D::operator*(double value) const 
{
  return myPoint3D(m_x*value, m_y*value, m_z*value);
}

//============================================================================
myPoint3D myPoint3D::operator+(const myPoint3D& point) const 
{
  return myPoint3D(m_x+point.x(), m_y+point.y(), m_z+point.z());
}

//============================================================================
double myPoint3D::x() const
{
  return m_x;
}

//============================================================================
double myPoint3D::y() const
{
  return m_y;
}

//============================================================================
double myPoint3D::z() const
{
  return m_z;
}

//============================================================================
void myPoint3D::draw(myDrawing& drawing)
{
  drawing.visit(*this);
}


