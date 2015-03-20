#include "GameLoop.h"

#include <cstdlib>
#include <iostream>

GameLoop::GameLoop()
  : m_window(NULL), m_cam(NULL), m_starField(NULL)
{
}

void
GameLoop::init()
{
  /* Initialize glfw */
  if (!glfwInit())
  {
    exit(1);
  }
  /* Create a windowed mode window and its OpenGL context */
  m_window = glfwCreateWindow(640, 480, "lambdaGalaxy", NULL, NULL);
  if (!m_window)
  {
    glfwTerminate();
    exit(1);
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(m_window);

  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  /* Glew */
  glewExperimental = true;
  GLenum err = glewInit();
  if (err != GLEW_OK)
  {
    std::cout << "glewInit failed, aborting." << std::endl;
    glfwTerminate();
    exit(1);
  }

  glEnable(GL_DEPTH_TEST);
  initScene();
}

void
GameLoop::run()
{
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(m_window))
  {
    /* Update the game state */
    update();

    /* Render the game */
    render();

    /* Swap front and back buffers */
    glfwSwapBuffers(m_window);
  }
}

void
GameLoop::terminate()
{
  /* Terminate glfw */
  glfwTerminate();
}

void
GameLoop::initScene()
{
  m_cam = new Camera(640.0f, 480.0f);
  m_cam->setPosition(*new Eigen::Vector3f(0.0f, 0.0f, -5.0f));

  m_starField = new StarField();
  m_starField->init(m_cam->getPosition());

}

void
GameLoop::render()
{
  int width, height;
  glfwGetFramebufferSize(m_window, &width, &height);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_starField->draw(*m_cam);
}

void
GameLoop::update()
{
  inputHandler();
  m_starField->update(m_cam->getPosition());
}

void
GameLoop::inputHandler()
{
  float speed = 5.0f;
  float time = 4.0f;
  //float time = glfwGetTime();
  //glfwSetTime(time);

  /* Poll for and process events */
  glfwPollEvents();  
  
  if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(m_window, GL_TRUE);

  if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    m_cam->moveFoward(-speed * time);

  if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
    m_cam->moveFoward(speed * time);

  if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    m_cam->moveHorizontal(-speed * time);

  if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    m_cam->moveHorizontal(speed * time);

  double x, y;
  float rotSpeed = 0.0005f;
  glfwGetCursorPos(m_window, &x, &y);

  m_cam->yaw(rotSpeed * (320 - x) * time);
  m_cam->pitch(rotSpeed * (240 - y) * time);

  glfwSetCursorPos(m_window, 320, 240);
} 
