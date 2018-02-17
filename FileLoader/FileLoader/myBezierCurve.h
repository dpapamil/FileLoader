// Representation of a bezier curve.
// Create the object using the control points, the curve's degree
// and the resolution you want to draw it with
// 
// You can draw the curve to a myDrawing object by calling
// curve.draw(drawing);


#ifndef myBezierCurve_H
#define myBezierCurve_H

#include "FileLoader/myElement.h"

#include <vector>
#include "FileLoader/myPoint3D.h"

class myBezierCurve : public myElement
{
public:
  // Precondition: points.size() > 1 && resolution > 0
  myBezierCurve(
    std::vector<myPoint3D> points, // the control points
    unsigned int degree,           // degree of the curve
    double resolution,              // the resolution
    std::vector<double> params
  );

  // Get the points we need to draw the curve
  std::vector<myPoint3D> get_drawing_points();

  // Draw the curve on the given drawing
  virtual void draw(myDrawing& drawing) override;

  virtual ~myBezierCurve() override;

private:

  // Find the bezier point for the given parameter value
  myPoint3D find_bezier_point(double t);

  // variables
  std::vector<myPoint3D> m_control_points;
  unsigned int m_degree;
  double m_resolution;
  std::vector<double> m_params;
};

#endif