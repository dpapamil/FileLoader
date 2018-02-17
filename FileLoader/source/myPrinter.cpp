#include "FileLoader/myPrinter.h"

#include <iostream>
#include "FileLoader/myDrawing.h"

// Shader
const GLchar* vertex_shader_source = 
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main() {\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

//============================================================================
// Initialise the printer
myPrinter::myPrinter()
  : m_drawing(nullptr)
{
  // Build and compile our shader program
  // Vertex shader
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);
  // Check for compile time errors
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
    std::cout << "Compilation of the shader failed: " << infoLog << std::endl;
  }
  // Link shader
  GLuint m_shader_program = glCreateProgram();
  glAttachShader(m_shader_program, vertex_shader);
  glLinkProgram(m_shader_program);
  // Check for linking errors
  glGetProgramiv(m_shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(m_shader_program, 512, NULL, infoLog);
    std::cout << "Linking of the shader failed: " << infoLog << std::endl;
  }
  glDeleteShader(vertex_shader);
}

//============================================================================
// Set the drawing we will render
void myPrinter::set(std::unique_ptr<myDrawing> drawing)
{
  m_drawing = std::move(drawing);
}

//============================================================================
// Render the drawing
void myPrinter::render()
{
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  if (m_drawing) {
    m_drawing->draw(m_shader_program);
  }
}

//============================================================================
myPrinter::~myPrinter()
{
}
