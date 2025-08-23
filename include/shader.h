#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char *ReadFileToString(FILE*);

struct ShaderObject {
  unsigned int ID;
  const char *vShaderCode;
  const char *fShaderCode;
};

typedef struct ShaderObject Shader;

Shader ConstructShaders(const char *, const char *);

void use(unsigned int id);
void setBool(unsigned int id, const char *, _Bool*, size_t);
void setInt(unsigned int id, const char *, int*, size_t);
void setFloat(unsigned int id, const char *, float*, size_t);

#endif