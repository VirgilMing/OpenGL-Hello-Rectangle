#include "include/public.hpp"
#include "include/draw.hpp"

float points[] = {
   0.5f,  0.5f,  0.0f,
   0.5f, -0.5f,  0.0f,
  -0.5f, -0.5f,  0.0f,
  -0.5f,  0.5f,  0.0f
};
GLuint vShader, fShader, shaderProgram;
GLuint vaoHandle, vboHandle;
void initVBO(){
  vboHandle = 0;
  glGenBuffers(1, &vboHandle);
  glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
  glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), points, GL_STATIC_DRAW);
  vaoHandle = 0;
  glGenVertexArrays(1, &vaoHandle);
  glBindVertexArray(vaoHandle);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
  glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void drawCube(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(shaderProgram);
  glBindVertexArray(vaoHandle);
  // draw points 0-4 from the currently bound vao with current in-use shader
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
