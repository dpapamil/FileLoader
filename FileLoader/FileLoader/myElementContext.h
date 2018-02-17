// Class representing the context information needed to create an element
//
// 


#ifndef myElementContext_H
#define myElementContext_H

#include "FileLoader/myEnums.h"

#include <vector>
#include "FileLoader/myPoint3D.h"

class myElementContext
{
public:
  myElementContext();

  myCTechType curve_tech_type() const;
  void set_curve_tech_type(myCTechType type);

  double c_parm() const;
  void set_c_parm(double c_parm);

  myElementType element_type() const;
  void set_element_type(myElementType type);

  unsigned int degree() const;
  void set_degree(unsigned int degree);

  double start_range() const;
  void set_start_range(double start_range);

  double end_range() const;
  void set_end_range(double end_range);

  const std::vector<double>& u_params() const;
  void add_u_param(double u_param);

  const std::vector<myPoint3D>& points() const;
  void add_point(myPoint3D point);

  bool finished_building() const;
  void finish_building();

  ~myElementContext();

private:
  myCTechType m_ctech_type;
  myElementType m_element_type;
  unsigned int m_degree;
  double m_start_range;
  double m_end_range;
  double m_c_parm;
  std::vector<double> m_u_params;
  std::vector<myPoint3D> m_points;
  bool m_finished_building;
}; 

#endif