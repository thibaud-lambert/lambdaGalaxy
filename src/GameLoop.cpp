#include "GameLoop.h"

#include <cstdlib>

GameLoop::GameLoop()
:window(NULL)
{
}

void GameLoop::init()
{
  /* Initialize glfw */
  if (!glfwInit())
  {
    exit(1);
  }
  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "lambdaGalaxy", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    exit(1);
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
}

void GameLoop::run()
{
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    /* Update the game state */
    update();

    /* Render the game */
    render();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);
  }
}

void GameLoop::terminate()
{
  /* Terminate glfw */
  glfwTerminate();
}

void GameLoop::render()
{
  glClear(GL_COLOR_BUFFER_BIT); 
}

void GameLoop::update()
{
  /* Poll for and process events */
  glfwPollEvents();
}
