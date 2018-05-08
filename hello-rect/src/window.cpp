#include "include/public.hpp"
#include "include/draw.hpp"
#include <iostream>

const char * vertShaderFileName = "rect.vert";
const char * fragShaderFileName = "rect.frag";
int main(void)
{
  /* Initialize the library */
  if (!glfwInit()){
    std::cerr << "GLFW init fail\n";
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
  // this line is needed on macOS


  /* Create a windowed mode window and its OpenGL context */
  GLFWwindow* window = glfwCreateWindow(640, 480, "The First OpenGL Program", NULL, NULL);
  if (!window) {
    std::cerr << "Window creation fail\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  /* Make the window's context current */
  glewExperimental = GL_TRUE;
  glewInit();

  // tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

  // fprintf(stderr, "&vertShaderFileName = %p\n", vertShaderFileName);

  initShader(vertShaderFileName,fragShaderFileName);
  initVBO();
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    /* Render here */
    drawRect();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
