#ifndef DRAW_HPP
#define DRAW_HPP
void drawCube();
void initVAO();
void initVBO();
void initCBO();
void initShader(const char *&VShaderFile,
                const char *&FShaderFile);
void createAndSendMVP();
extern GLuint vShader, fShader, shaderProgram;
#endif
