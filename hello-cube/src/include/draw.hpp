#ifndef DRAW_HPP
#define DRAW_HPP
void drawCube();
void initBuffers();

void initShader(const char *&VShaderFile,
                const char *&FShaderFile);
void createAndSendMVP();
extern GLuint vShader, fShader, shaderProgram;
#endif
