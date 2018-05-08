#include "include/public.hpp"
#include "include/draw.hpp"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
static const GLfloat g_vertex_buffer_data[] = {
  -1.0f,-1.0f,-1.0f, 
  -1.0f, 1.0f,-1.0f, 
   1.0f,-1.0f,-1.0f, 
   1.0f, 1.0f,-1.0f, 
  -1.0f,-1.0f, 1.0f,
  -1.0f, 1.0f, 1.0f, 
   1.0f,-1.0f, 1.0f, 
   1.0f, 1.0f, 1.0f, 
};

static const GLfloat g_color_buffer_data[] = {
  0.583f,  0.771f,  0.014f,
  0.609f,  0.115f,  0.436f,
  0.327f,  0.483f,  0.844f,
  0.822f,  0.569f,  0.201f,
  0.435f,  0.602f,  0.223f,
  0.310f,  0.747f,  0.185f,
  0.597f,  0.770f,  0.761f,
  0.559f,  0.436f,  0.730f,
};

unsigned short indices[] = {
  0,1, 0,2, 1,3, 2,3,
  0,4, 1,5, 2,6, 3,7,
  4,5, 4,6, 5,7, 6,7
};

GLuint vShader, fShader, shaderProgram;
GLuint vaoHandle, vboHandle, cboHandle, eboHandle;


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

void initCBO(){
  glGenBuffers(1, &cboHandle);
  glBindBuffer(GL_ARRAY_BUFFER, cboHandle);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
  // 2nd attribute buffer : colors
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(
      1,                 // attribute. No particular reason for 1, but must match the layout in the shader.
      3,                 // size
      GL_FLOAT,          // type
      GL_FALSE,          // normalized?
      0,                 // stride
      (void*)0           // array buffer offset
  );

}

void initBuffers(){
  initVAO(); // vertex array object
  initVBO(); // vertex buffer object
  initEBO(); //
  initCBO(); // 
}


void createAndSendMVP(){
  glm::mat4 projectionMat = glm::perspective(
    glm::radians(45.f),
    4.0f/3.0f,
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
  glBindVertexArray(vaoHandle);
  // draw points 0-4 from the currently bound vao with current in-use shader
  glDrawElements(GL_LINES, sizeof(indices)/sizeof(unsigned short), GL_UNSIGNED_SHORT, 0); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares
}
