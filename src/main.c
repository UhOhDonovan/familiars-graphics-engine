#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <shader.h>
#include <stb_image.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);

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
  
  //-------------------------------------------------------------------------
  //----------------- Build and Compile Shader Programs ---------------------
  //-------------------------------------------------------------------------
  Shader shader_program =
      ConstructShaders("../"
                       "src/shaders/shader.vs",
                       "../"
                       "src/shaders/shader.fs");
  // glDeleteShader(fragment_shader_2);

  // set up vertex data and buffers
  float vertices[] = {
    -0.1f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.55f, 0.55f, // top right
    -0.1f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.55f, 0.45f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.45f, 0.45f, // bottom left
    -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.45f, 0.55f  // top left 
  };
  
  float vertices_1[] = {
    0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top right
    0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    0.1f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left
    0.1f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // top left 
  };
  
  unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
  };

  //-------------------------------------------------------------------------
  //-------------------------- Load Textures --------------------------------
  //-------------------------------------------------------------------------
  
  unsigned int textures[2];
  glGenTextures(2, textures);

  // Texture One
  //-------------------------------------------------------------------------

  glBindTexture(GL_TEXTURE_2D, textures[0]);
  
  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
  int width, height, nrChannels;
  unsigned char *data = stbi_load("../assets/container.jpg", &width, &height, &nrChannels, 0);

  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    printf("Failed to load texture\n");
  }
  stbi_image_free(data);

  // Texture Two
  //-------------------------------------------------------------------------
  
  glBindTexture(GL_TEXTURE_2D, textures[1]);
  
  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  data = stbi_load("../assets/awesomeface.png", &width, &height, &nrChannels, 0);
  
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    printf("Failed to load texture\n");
  }

  stbi_image_free(data);

  //-------------------------------------------------------------------------
  // ------------------------ Initialize Buffers ----------------------------
  //-------------------------------------------------------------------------
  unsigned int VBOs[2], VAOs[2], EBOs[2];
  glGenVertexArrays(2, VAOs);
  glGenBuffers(2, VBOs);
  glGenBuffers(2, EBOs);
  
  // Object One
  //-------------------------------------------------------------------------
  glBindVertexArray(VAOs[0]);

  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // Object Two
  //-------------------------------------------------------------------------
  glBindVertexArray(VAOs[1]);

  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // glBindBuffer(GL_ARRAY_BUFFER, 0);

  // glBindVertexArray(0);

  use(shader_program.ID);
  glUniform1i(glGetUniformLocation(shader_program.ID, "texture1"), 0);
  glUniform1i(glGetUniformLocation(shader_program.ID, "texture2"), 1);

  //-------------------------------------------------------------------------
  //------------------------- Main game loop --------------------------------
  //-------------------------------------------------------------------------
  while (!glfwWindowShouldClose(window))
  { 
    // Input handling
    glfwPollEvents();
    process_input(window);

    // Rendering code goes here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);

    glUseProgram(shader_program.ID);
    glBindVertexArray(VAOs[0]);
    float xOffset0 = 0;
    setFloat(shader_program.ID, "xOffset", &xOffset0, 1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    float timeValue = glfwGetTime();
    float xOffset1 = (sin(timeValue) / 2.0f);
    // int vertexColorLocation = glGetUniformLocation(shader_program.ID, "ourColor");
    // glUseProgram(shader_program.ID);
    // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    glBindVertexArray(VAOs[1]);
    setFloat(shader_program.ID, "xOffset", &xOffset1, 1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Swap buffers
    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(2, VAOs);
  glDeleteBuffers(2, VBOs);
  glDeleteBuffers(2, EBOs);
  glDeleteProgram(shader_program.ID);

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