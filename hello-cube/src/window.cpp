#include "include/public.hpp"
#include "include/draw.hpp"
#include <iostream>

const char * vertShaderFileName = "cube.vert";
const char * fragShaderFileName = "cube.frag";
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
  GLFWwindow* window = glfwCreateWindow(480, 480, "The Perspective Projection Program", NULL, NULL);
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

  initBuffers();
  initShader(vertShaderFileName,fragShaderFileName);

  createAndSendMVP();
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    /* Render here */
    drawCube();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
