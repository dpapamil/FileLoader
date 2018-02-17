// Class representing a drawing
// 
// myElement objects can be added to a drawing by calling
// draw(drawing)
//
// You have to add the drawing to a printer, which will call
// draw(shader) on the drawing.

#ifndef myDrawing_H
#define myDrawing_H


#include <GL/glew.h>
#include <vector>
#include <memory>

class myElement;
class myPoint3D;
class myBezierCurve;

class myDrawing
{
public:
  myDrawing();

  // Draw the drawing using the provided shader program
  void draw(GLuint shader_program);

  // Visit a bezier curve
  void visit(myBezierCurve& curve);

  // Visit a point
  void visit(myPoint3D& point);

  ~myDrawing();

private:
  // normalise the given points
  void normalise_points(std::vector<myPoint3D>& points);


  // variable
  GLuint m_vao;
  GLuint m_vbo;
  GLuint m_ebo;

  std::unique_ptr<GLfloat> m_vertices;
  GLuint* m_indices;

  unsigned int m_indices_size;
};

#endif