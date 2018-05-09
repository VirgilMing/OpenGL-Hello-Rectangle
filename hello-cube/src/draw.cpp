#include "include/public.hpp"
#include "include/draw.hpp"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
static const GLfloat g_vertex_buffer_data[] = {
  -1.0f,-1.0f, 1.0f,
   1.0f,-1.0f, 1.0f, 
   1.0f, 1.0f, 1.0f, 
  -1.0f, 1.0f, 1.0f, 
  -1.0f,-1.0f,-1.0f, 
   1.0f,-1.0f,-1.0f, 
   1.0f, 1.0f,-1.0f, 
  -1.0f, 1.0f,-1.0f, 
};

// static const GLfloat g_color_buffer_data[] = {
//   1.0f, 0.5f, 0.2f,
//   0.2f, 1.0f, 0.5f

// };

unsigned short indices[] = {
  0,1, 1,2, 0,3, 2,3,
  0,4, 1,5, 2,6, 3,7,
  4,5, 5,6, 4,7, 6,7,

  0, 1, 2,
  2, 3, 0,
  // top
  3, 2, 6,
  6, 7, 3,
  // back
  7, 6, 5,
  5, 4, 7,
  // bottom
  4, 5, 1,
  1, 0, 4,
  // left
  4, 0, 3,
  3, 7, 4,
  // right
  1, 5, 6,
  6, 2, 1,
  1, 3, 4,
  1, 2, 3


};


GLuint vShader, fShader, shaderProgram;
GLuint vaoHandle;
GLuint vboHandle;
// GLuint cboHandle;
GLuint eboHandle;


void initVAO(){
  glGenVertexArrays(1, &vaoHandle);
  glBindVertexArray(vaoHandle);
}
void initVBO(){
  glGenBuffers(1, &vboHandle);
  glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
  glBufferData(GL_ARRAY_BUFFER, 
               sizeof(g_vertex_buffer_data), 
               g_vertex_buffer_data, 
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
  );

}
void initEBO(){
  glGenBuffers(1, &eboHandle);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboHandle);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}


void initBuffers(){
  initVAO(); // vertex array object
  initVBO(); // vertex buffer object
  initEBO(); //
}


void createAndSendMVP(){
  glm::mat4 projectionMat = glm::perspective(
    glm::radians(45.f),
    1.0f,
    0.1f,
    100.0f
  );

  glm::mat4 viewMat = glm::lookAt(
    glm::vec3(4,3,3), 
    glm::vec3(0,0,0),
    glm::vec3(0,1,0)
  );

  glm::mat4 modelMat = glm::mat4(1.0f);

  glm::mat4 mvp = projectionMat * viewMat * modelMat;

  GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");

  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
}

void drawCube(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(shaderProgram);

  GLint vertexColorLocation;

  glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
  vertexColorLocation = glGetUniformLocation(shaderProgram, "uColor");
  glUseProgram(shaderProgram);
  glUniform4f(vertexColorLocation, 0.2f, 1.0f, 0.2f, 1.0f);
  glBindVertexArray(vaoHandle);


  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned short) - 24, GL_UNSIGNED_SHORT, (void*)24);
  glBindVertexArray(0);

  glClear(GL_DEPTH_BUFFER_BIT);

  glDepthFunc(GL_ALWAYS); // depth-testing interprets a smaller value as "closer"
  vertexColorLocation = glGetUniformLocation(shaderProgram, "uColor");
  glUseProgram(shaderProgram);
  glUniform4f(vertexColorLocation, 0.f, 0.f, 0.f,1.0f);
  glBindVertexArray(vaoHandle);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glDrawElements(GL_LINES, 24, GL_UNSIGNED_SHORT, 0);
  glBindVertexArray(0);

}
