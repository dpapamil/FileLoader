#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <list>
#include <memory>
#include "FileLoader/myPoint3D.h"
#include "FileLoader/myFileReader.h"
#include "FileLoader/myBezierCurve.h"
#include <windows.h>
#include "FileLoader/myDrawing.h"
#include "FileLoader/myPrinter.h"
#include "FileLoader/myUtils.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 800;

// main function
//============================================================================
int main(int argc, const char* argv[]) {
  std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
  // Init GLFW
  glfwInit();
  // Set all the required options for GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Create a GLFWwindow object that we can use for GLFW's functions
  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "File Loader", nullptr, nullptr);
  glfwMakeContextCurrent(window);

  // Set the required callback functions
  glfwSetKeyCallback(window, key_callback);

  // Set this to true so GLEW knows to use a modern approach to 
  // retrieving function pointers and extensions
  glewExperimental = GL_TRUE;
  // Initialize GLEW to setup the OpenGL Function pointers
  glewInit();

  // Define the viewport dimensions
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  if (argc < 2) {
    MessageBox(0, "You have to specify a file to load", "Error!", MB_ICONSTOP | MB_OK);
    glfwTerminate();
    return 0;
  }

  // Create the printer and an empty drawing
  myPrinter printer;
  std::unique_ptr<myDrawing> drawing = std::make_unique<myDrawing>();

  // Try to read the file and create any elements that are described in it
  std::list<std::unique_ptr<myElement>> elements;
  myFileReader file_parser;
  myError err = file_parser.parse_file(argv[1], elements);
  if (err != myError::NONE) {
    MessageBox(0, myUtils::decode_error_type(err).c_str(), "Error!", MB_ICONSTOP | MB_OK);
    glfwTerminate();
    return 0;
  }

  if (!elements.empty()) {
    // Draw the created element in the drawing and pass it on to the printer
    elements.front()->draw(*drawing);
    printer.set(std::move(drawing));
  }

  while (!glfwWindowShouldClose(window)) {
	// Check if any events have been activated (key pressed, mouse moved etc.) 
    // and call corresponding response functions
	glfwPollEvents();

    // Render
    printer.render();

	// Swap the screen buffers
	glfwSwapBuffers(window);
  }
  glfwTerminate();
  return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
	glfwSetWindowShouldClose(window, GL_TRUE);
  }
}