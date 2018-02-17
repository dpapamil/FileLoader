// This class is used to receive a drawing and render it.
// TODO: can draw multiple drawings

#ifndef myPrinter_H
#define myPrinter_H

#include <GL/glew.h>
#include <memory>

class myDrawing;

class myPrinter
{
public:
  myPrinter();

  // Set the drawing we want to render
  void set(std::unique_ptr<myDrawing> drawing);

  // Render the drawing
  void render();

  ~myPrinter();

private:
  GLuint m_shader_program;

  std::unique_ptr<myDrawing> m_drawing;
};

#endif