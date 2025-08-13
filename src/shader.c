#include <shader.h>

char *ReadFileToString(FILE *fp) {
  int c;
  int nch = 0;
  int size = 50;
  char *buf = malloc(size);
  if (buf == NULL) {
    fprintf(stderr, "out of memory\n");
    exit(1);
  }

  while ((c = fgetc(fp)) != EOF) {
    if (nch >= size - 1) {
      /* time to make it bigger */
      size += 50;
      buf = realloc(buf, size);
      if (buf == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
      }
    }

    buf[nch++] = c;
  }

  buf[nch++] = '\0';
  return buf;
}

Shader ConstructShaders(const char *vertex_path, const char *fragment_path) {
  // Initialize shader struct
  Shader s;

  // Initialize file object
  FILE *vfptr = fopen(vertex_path, "r");
  FILE *ffptr = fopen(fragment_path, "r");

  // Collect Shader code
  s.vShaderCode = ReadFileToString(vfptr);
  s.fShaderCode = ReadFileToString(ffptr);

  fclose(vfptr);
  fclose(ffptr);
  
  // Compile shaders
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  // Vertex Shaders
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &s.vShaderCode, NULL);
  glCompileShader(vertex);
  // print compile errors if any
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n", infoLog);
  };

  // Fragment Shaders
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &s.fShaderCode, NULL);
  glCompileShader(fragment);
  // print compile errors if any
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n", infoLog);
  };

  // Compile Shaders
  s.ID = glCreateProgram();
  glAttachShader(s.ID, vertex);
  glAttachShader(s.ID, fragment);
  glLinkProgram(s.ID);
  // print linking errors if any
  glGetProgramiv(s.ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(s.ID, 512, NULL, infoLog);
    printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", infoLog);
  }

  // delete the linked shaders
  glDeleteShader(vertex);
  glDeleteShader(fragment);

  return s;
}

void use(unsigned int id) {
  glUseProgram(id);
}

void setBool(unsigned int id, const char * name, _Bool value) {
  glUniform1i(glGetUniformLocation(id, name), (int)value);
}

void setInt(unsigned int id, const char* name, int value) {
  glUniform1i(glGetUniformLocation(id, name), value);
}

void setFloat(unsigned int id, const char* name, float value) {
  glUniform1f(glGetUniformLocation(id, name), value);
}