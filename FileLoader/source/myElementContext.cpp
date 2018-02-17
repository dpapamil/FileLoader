#include "FileLoader/myElementContext.h"


//============================================================================
// Initialise the context
myElementContext::myElementContext()
  : m_ctech_type(myCTechType::NONE),
    m_degree(0),
    m_element_type(myElementType::NONE),
    m_start_range(0),
    m_end_range(0),
    m_c_parm(0),
    m_finished_building(false)
{
}

//============================================================================
myCTechType myElementContext::curve_tech_type() const
{
  return m_ctech_type;
}

//============================================================================
void myElementContext::set_curve_tech_type(myCTechType type)
{
  m_ctech_type = type;
}

//============================================================================
double myElementContext::c_parm() const
{
  return m_c_parm;
}

//============================================================================
void myElementContext::set_c_parm(double c_parm)
{
  m_c_parm = c_parm;
}

//============================================================================
myElementType myElementContext::element_type() const
{
  return m_element_type;
}

//============================================================================
void myElementContext::set_element_type(myElementType type)
{
  m_element_type = type;
}

//============================================================================
unsigned int myElementContext::degree() const
{
  return m_degree;
}

//============================================================================
void myElementContext::set_degree(unsigned int degree)
{
  m_degree = degree;
}

//============================================================================
double myElementContext::start_range() const
{
  return m_start_range;
}

//============================================================================
void myElementContext::set_start_range(double start_range)
{
  m_start_range = start_range;
}

//============================================================================
double myElementContext::end_range() const
{
  return m_end_range;
}

//============================================================================
void myElementContext::set_end_range(double end_range)
{
  m_end_range = end_range;
}

//============================================================================
const std::vector<double>& myElementContext::u_params() const
{
  return m_u_params;
}

//============================================================================
void myElementContext::add_u_param(double u_param)
{
  m_u_params.push_back(u_param);
}

//============================================================================
const std::vector<myPoint3D>& myElementContext::points() const
{
  return m_points;
}

//============================================================================
void myElementContext::add_point(myPoint3D point)
{
  m_points.push_back(point);
}

//============================================================================
bool myElementContext::finished_building() const
{
  return m_finished_building;
}

//============================================================================
void myElementContext::finish_building()
{
  m_finished_building = true;
}

//============================================================================
myElementContext::~myElementContext()
{
}
