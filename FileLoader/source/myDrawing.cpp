#include "FileLoader/myDrawing.h"
#include "FileLoader/myBezierCurve.h"


//============================================================================
myDrawing::myDrawing()
{
}

//============================================================================
// Draw the drawing using the provided shader
void myDrawing::draw(GLuint shader_program)
{
  glUseProgram(shader_program);
  glBindVertexArray(m_vao);

  glDrawArrays(GL_LINES, 0, m_indices_size);
  glDrawElements(GL_LINES, m_indices_size, GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
}

//============================================================================
// Draw a bezier curve
void myDrawing::visit(myBezierCurve& curve)
{
  // Get the drawing points of the curve and normalise them
  std::vector<myPoint3D> drawing_points = curve.get_drawing_points();
  normalise_points(drawing_points);

  // Create the vertices array
  const int vertices_size = drawing_points.size() * 3;
  m_vertices = std::unique_ptr<GLfloat>(new GLfloat[vertices_size]);
  for (int i = 0; i < drawing_points.size(); ++i) {
    int vert_index = i * 3;
    m_vertices.get()[vert_index] = drawing_points[i].x();
    m_vertices.get()[vert_index + 1] = drawing_points[i].y();
    m_vertices.get()[vert_index + 2] = drawing_points[i].z();
  }

  // Now the indices array to draw the lines between the indices
  m_indices_size = 2 * (drawing_points.size() - 1);
  m_indices = new GLuint[m_indices_size];
  for (int i = 0; i < drawing_points.size(); ++i) {
    int index = i * 2;
    m_indices[index] = i;
    m_indices[index + 1] = i + 1;
  }

  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_vbo);
  glGenBuffers(1, &m_ebo);
  // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
  glBindVertexArray(m_vao);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices_size * sizeof(GLfloat), m_vertices.get(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices_size * sizeof(GLuint), m_indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
}

//============================================================================
// Draw a point
void myDrawing::visit(myPoint3D& point)
{
  // TODO: add implementation
}

//============================================================================
// Normalise the given points
void myDrawing::normalise_points(std::vector<myPoint3D>& points)
{
  // Get the max in every coordinate first
  double x_max = 0;
  double y_max = 0;
  double z_max = 0;
  for (const myPoint3D& point : points) {
    if (std::abs(point.x()) > x_max) {
      x_max = std::abs(point.x());
    }
    if (std::abs(point.y()) > y_max) {
      y_max = std::abs(point.y());
    }
    if (std::abs(point.z()) > z_max) {
      z_max = std::abs(point.z());
    }
  }

  // Make sure we don't have a zero
  x_max = x_max == 0 ? 1 : x_max;
  y_max = y_max == 0 ? 1 : y_max;
  z_max = z_max == 0 ? 1 : z_max;

  // Now normalise the points
  for (myPoint3D& point : points) {
    point = myPoint3D(
      point.x()/x_max,
      point.y()/y_max,
      point.z()/z_max
    );
  }
}

//============================================================================
myDrawing::~myDrawing()
{
  // Properly de-allocate all resources once they've outlived their purpose
  glDeleteVertexArrays(1, &m_vao);
  glDeleteBuffers(1, &m_vbo);
  glDeleteBuffers(1, &m_ebo);
}

