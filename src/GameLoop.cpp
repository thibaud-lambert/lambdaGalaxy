#include "GameLoop.h"

#include <cstdlib>
#include <iostream>

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGH 800

GameLoop::GameLoop()
:window(NULL),cam(NULL),starField(NULL),lastTime(0)
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
  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGH, "lambdaGalaxy", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    exit(1);
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  /* Glew */
  glewExperimental=true;
  GLenum err=glewInit();
  if(err!=GLEW_OK)
  {
    std::cout<<"glewInit failed, aborting."<<std::endl;
    glfwTerminate();
    exit(1);
  }

  glEnable(GL_DEPTH_TEST);
  initScene();
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

void GameLoop::initScene()
{
  cam = new Camera(WINDOW_WIDTH, WINDOW_HEIGH);
  cam->setPosition(*new Eigen::Vector3f(0,0,-5));

  starField = new StarField();
  starField->init(cam->getPosition());
  lastTime = glfwGetTime();

}

void GameLoop::render()
{
  float ratio;
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  ratio = width / (float) height;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  starField->draw(*cam);
}

void GameLoop::update()
{
  inputHandler();
  starField->update(cam->getPosition());
}

void GameLoop::inputHandler()
{
  float dist = starField->getDist(cam->getPosition());
  float speed = 1000.0f;
  float time = glfwGetTime();
  float elapsed_time = time - lastTime;
  lastTime = time;

  /* Poll for and process events */
  glfwPollEvents();

  if(glfwGetKey(window, GLFW_KEY_ESCAPE)  == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  if(glfwGetKey(window, GLFW_KEY_W)  == GLFW_PRESS)
    cam->moveFoward(-speed * elapsed_time);

  if(glfwGetKey(window, GLFW_KEY_S)  == GLFW_PRESS)
    cam->moveFoward(speed * elapsed_time);

  if(glfwGetKey(window, GLFW_KEY_A)  == GLFW_PRESS)
    cam->moveHorizontal(-speed * elapsed_time);

  if(glfwGetKey(window, GLFW_KEY_D)  == GLFW_PRESS)
    cam->moveHorizontal(speed * elapsed_time);

  double x,y;
  float rotSpeed = 0.05f;
  glfwGetCursorPos(window, &x, &y);

  cam->yaw(rotSpeed * (WINDOW_WIDTH/2. - x) * elapsed_time);
  cam->pitch(rotSpeed * (WINDOW_HEIGH/2. - y) * elapsed_time);

  glfwSetCursorPos(window, WINDOW_WIDTH/2., WINDOW_HEIGH/2.);
}
