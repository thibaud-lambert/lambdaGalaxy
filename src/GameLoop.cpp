#include "GameLoop.h"

#include <cstdlib>
#include <iostream>

GameLoop::GameLoop()
:window(NULL),cam(NULL),starField(NULL)
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
  cam = new Camera(640, 480);
  cam->setPosition(*new Eigen::Vector3f(0,0,-5));

  starField = new StarField();
  starField->init(cam->getPosition());

}

void GameLoop::render()
{
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

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
  float speed = 5.0f;
  float time = 4.0f;
  //float time = glfwGetTime();
  //glfwSetTime(time);

  /* Poll for and process events */
  glfwPollEvents();  
  
  if(glfwGetKey(window, GLFW_KEY_ESCAPE)  == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  if(glfwGetKey(window, GLFW_KEY_W)  == GLFW_PRESS)
    cam->moveFoward(-speed * time);

  if(glfwGetKey(window, GLFW_KEY_S)  == GLFW_PRESS)
    cam->moveFoward(speed * time);

  if(glfwGetKey(window, GLFW_KEY_A)  == GLFW_PRESS)
    cam->moveHorizontal(-speed * time);

  if(glfwGetKey(window, GLFW_KEY_D)  == GLFW_PRESS)
    cam->moveHorizontal(speed * time);

  double x,y;
  float rotSpeed = 0.0005f;
  glfwGetCursorPos(window, &x, &y);     

  cam->yaw(rotSpeed * (320 - x) * time);
  cam->pitch(rotSpeed * (240 - y) * time);

  glfwSetCursorPos(window, 320, 240);
} 
