#include "FileLoader/myBezierCurve.h"

#include "assert.h"
#include "FileLoader/myDrawing.h"
#include "FileLoader/myMathUtils.h"

//============================================================================
// Creates a bezier curve with its control points, degree, resolution
// and parameters
myBezierCurve::myBezierCurve(
  std::vector<myPoint3D> points,
  unsigned int degree,
  double resolution,
  std::vector<double> params
)
  : m_control_points(points),
    m_degree(degree),
    m_resolution(resolution),
    m_params(params)
{
  assert(points.size() > 1);
  assert(resolution > 0);
  assert(m_params.size() == m_control_points.size()/m_degree + 1);
}

//============================================================================
// Get the drawing points of the curve
std::vector<myPoint3D> myBezierCurve::get_drawing_points()
{
  std::vector<myPoint3D> drawing_points;
  double step = 1 / (m_control_points.size() * m_resolution);
  for (double t = m_params[0]; t <= 1; t += step) {
    myPoint3D new_p = find_bezier_point(t);
    drawing_points.push_back(new_p);
  }
  return drawing_points;
}

//============================================================================
// Finds the curve point for the given parameter t
// It uses the Bernstein polynomial
myPoint3D myBezierCurve::find_bezier_point(double t)
{
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;

  int count = m_control_points.size();
  for (int i = 0; i < count; ++i) {
    // TODO: export to one function
    x += myMathUtils::binomial_coeff(count-1,i) * pow(t,i) * pow((1-t),(count-1-i)) * m_control_points[i].x();
    y += myMathUtils::binomial_coeff(count-1,i) * pow(t,i) * pow((1-t),(count-1-i)) * m_control_points[i].y();
    z += myMathUtils::binomial_coeff(count-1,i) * pow(t,i) * pow((1-t),(count-1-i)) * m_control_points[i].z();
  }
  return myPoint3D(x, y, z);
}

//============================================================================
// Draw the curve onto a drawing
void myBezierCurve::draw(myDrawing& drawing)
{
  drawing.visit(*this);
}

//============================================================================
myBezierCurve::~myBezierCurve()
{
}

