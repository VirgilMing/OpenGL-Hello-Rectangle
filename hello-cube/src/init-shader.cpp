#include "include/public.hpp"
#include "include/draw.hpp"
#include <cstdarg>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cstring>

const char *textFileRead(const char *filename){
  std::ifstream shaderFile(filename);
  std::ostringstream shaderBuffer;
  shaderBuffer << shaderFile.rdbuf();
  std::string shaderBufferStr = shaderBuffer.str();
  // Warning: safe only until shaderBufferStr is destroyed or modified
  char * ret = new char[shaderBufferStr.size()];
  std::strcpy(ret, shaderBufferStr.c_str());
  return ret;
}

GLuint compileShader(const char* &shaderFile, GLenum type)
{
  // creation
  GLuint shader = glCreateShader(type);
  // error check
  if (0 == shader) {
    std::cerr << "shader creation failed\n";
    exit(1);
  }

  const char *shaderCode = textFileRead(shaderFile);
  const char *codeArr[1] = {shaderCode};

  glShaderSource(shader, 1, codeArr, nullptr);

  glCompileShader(shader);
  GLint compileResult;
  // check compilation
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
  if(GL_FALSE == compileResult){
    std::cerr << "Error: shader created but compilation failed.\n";
    exit(1);
  }
  delete []shaderCode;
  return shader;
}

void linkShader(GLuint &shaderProgHandle, int num, ...) 
// variadic convention dictates that # must be given somehow
{
  shaderProgHandle = glCreateProgram();
  if (!shaderProgHandle) {
    std::cerr << "Error: create program failed\n";
    exit(1);  
  }  
  va_list args;
  va_start(args, num);
  for (int i = 0; i < num; ++i) {
    glAttachShader(shaderProgHandle, va_arg(args, GLuint));
  }
  va_end(args);
  glLinkProgram(shaderProgHandle);
  // check link
  GLint linkStatus;
  glGetProgramiv(shaderProgHandle, GL_LINK_STATUS, &linkStatus);
  if(GL_FALSE == linkStatus)
  {
    std::cerr << "Error: link failed\n";
        exit(1);
  }
  else{
    glUseProgram(shaderProgHandle);
  }
}

void initShader(const char *&VShaderFile,
                const char *&FShaderFile)
{
  vShader = compileShader(VShaderFile, GL_VERTEX_SHADER);
  fShader = compileShader(FShaderFile, GL_FRAGMENT_SHADER);
  linkShader(shaderProgram, 2, vShader, fShader);
}
