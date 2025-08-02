#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <stdio.h>

struct Triangle {
  float vertex_a_x;
  float vertex_a_y;
  float vertex_b_x;
  float vertex_b_y;
  float vertex_c_x;
  float vertex_c_y;
};

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


  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    printf("Failed to initialize GLAD");
    return -1;
  }   

  glViewport(0, 0, 800, 600);

  struct Triangle t1;
  t1.vertex_a_x = -0.5f;
  t1.vertex_a_y = -0.5f;
  t1.vertex_b_x = 0.5f;
  t1.vertex_b_y = -0.5f;
  t1.vertex_c_x = 0.0f;
  t1.vertex_c_y = 0.5f;

  // Main game loop
  while (!glfwWindowShouldClose(window))
  { 
    // Input handling
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
      t1.vertex_a_x -= 0.1f;
      t1.vertex_b_x -= 0.1f;
      t1.vertex_c_x -= 0.1f;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
      t1.vertex_a_x += 0.1f;
      t1.vertex_b_x += 0.1f;
      t1.vertex_c_x += 0.1f;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
      t1.vertex_a_y += 0.1f;
      t1.vertex_b_y += 0.1f;
      t1.vertex_c_y += 0.1f;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
      t1.vertex_a_y -= 0.1f;
      t1.vertex_b_y -= 0.1f;
      t1.vertex_c_y -= 0.1f;
    }

    // Rendering code goes here
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glVertex2f(t1.vertex_a_x, t1.vertex_a_y);
    glVertex2f(t1.vertex_b_x, t1.vertex_b_y);
    glVertex2f(t1.vertex_c_x, t1.vertex_c_y);
    glEnd();

    // Swap buffers
    glfwSwapBuffers(window);
  }

  // Clean up
  glfwTerminate();

  return 0;
}