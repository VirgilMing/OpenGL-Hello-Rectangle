#ifndef DRAW_HPP
#define DRAW_HPP
void drawRect();
void initVBO();
void initShader(const char *&VShaderFile,
                const char *&FShaderFile);

extern GLuint vShader, fShader, shaderProgram;
extern GLuint vaoHandle;
#endif
