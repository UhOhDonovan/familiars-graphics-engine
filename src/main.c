#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <stdio.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);

struct Triangle {
  float vertex_a_x;
  float vertex_a_y;
  float vertex_b_x;
  float vertex_b_y;
  float vertex_c_x;
  float vertex_c_y;
};

const char *vertex_shader_source = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragment_shader_source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
const char *fragment_shader_source_2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n\0";

int main()
{
  // Initialize GLFW
  if (!glfwInit())
  {
    return -1;
  }

  // Create a window
  GLFWwindow *window = glfwCreateWindow(800, 600, "Familiars", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    printf("Failed to initialize GLAD");
    return -1;
  }
  
  // Build and Compile Shader Programs
  // ---------------------------------
  // vertex shader
  unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);
  int success;
  char info_log[512];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
    printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n", info_log);
  }
  // fragment shader
  unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);
  // check for shader compile errors
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
    printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n", info_log);
  }
  // fragment shader 2
  unsigned int fragment_shader_2 = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader_2, 1, &fragment_shader_source_2, NULL);
  glCompileShader(fragment_shader_2);
  // check for shader compile errors
  glGetShaderiv(fragment_shader_2, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragment_shader_2, 512, NULL, info_log);
    printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n", info_log);
  }
  // link shaders
  unsigned int shader_program = glCreateProgram();
  unsigned int shader_program_2 = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glAttachShader(shader_program_2, vertex_shader);
  glAttachShader(shader_program_2, fragment_shader_2);
  glLinkProgram(shader_program);
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program, 512, NULL, info_log);
    printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n", info_log);
  }
  glLinkProgram(shader_program_2);
  glGetProgramiv(shader_program_2, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program_2, 512, NULL, info_log);
    printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n", info_log);
  }
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  glDeleteShader(fragment_shader_2);

  // set up vertex data and buffers
  float vertices[] = {
    -0.1f,  0.5f, 0.0f,  // top right
    -0.1f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
  };
  
  float vertices_1[] = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    0.1f, -0.5f, 0.0f,  // bottom left
    0.1f,  0.5f, 0.0f   // top left 
  };
  
  unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
  };

  unsigned int VBOs[2], VAOs[2], EBOs[2];
  glGenVertexArrays(2, VAOs);
  glGenBuffers(2, VBOs);
  glGenBuffers(2, EBOs);
  
  glBindVertexArray(VAOs[0]);

  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAOs[1]);

  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // glBindBuffer(GL_ARRAY_BUFFER, 0);

  // glBindVertexArray(0);

  // Main game loop
  while (!glfwWindowShouldClose(window))
  { 
    // Input handling
    glfwPollEvents();
    process_input(window);

    // Rendering code goes here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);
    glBindVertexArray(VAOs[0]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glUseProgram(shader_program_2);
    glBindVertexArray(VAOs[1]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Swap buffers
    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(2, VAOs);
  glDeleteBuffers(2, VBOs);
  glDeleteBuffers(2, EBOs);
  glDeleteProgram(shader_program);

  // Clean up
  glfwTerminate();

  return 0;
}

void process_input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, 1);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}