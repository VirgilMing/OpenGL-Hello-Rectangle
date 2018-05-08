#ifndef DRAW_HPP
#define DRAW_HPP
void drawCube();
void initVAO();
void initShader(const char *&VShaderFile,
                const char *&FShaderFile);

extern GLuint vShader, fShader, shaderProgram;
extern GLuint vaoHandle;
#endif
