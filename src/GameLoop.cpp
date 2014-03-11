#include "GameLoop.h"

#include <cstdlib>
#include <iostream>

GameLoop::GameLoop()
:window(NULL),mesh(NULL),shader(NULL),object(NULL),cam(NULL)
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
  mesh = MeshLoader::loadMesh("../data/cube.obj");

  mesh->displayInfo();

  shader = new Shader();
  shader->loadFromFiles("../shader/basic.vert","../shader/basic.frag","","","../shader/basic.geo");

  object = new Object(mesh,shader);

  cam = new Camera(640, 480);
  cam->setPosition(*new Eigen::Vector3f(0,0,-5));
}

void GameLoop::render()
{
  float ratio;
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  ratio = width / (float) height;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  object->draw(*cam);
}

void GameLoop::update()
{
  inputHandler();
}

void GameLoop::inputHandler()
{
  float speed = 0.001f;
  float time = glfwGetTime();

  /* Poll for and process events */
  glfwPollEvents();  
  
  if(glfwGetKey(window, GLFW_KEY_ESCAPE)  == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  if(glfwGetKey(window, GLFW_KEY_W)  == GLFW_PRESS)
    cam->moveFoward(speed * time);

  if(glfwGetKey(window, GLFW_KEY_S)  == GLFW_PRESS)
    cam->moveFoward(-speed * time);

  if(glfwGetKey(window, GLFW_KEY_A)  == GLFW_PRESS)
    cam->moveHorizontal(speed * time);

  if(glfwGetKey(window, GLFW_KEY_D)  == GLFW_PRESS)
    cam->moveHorizontal(-speed * time);

  double x,y;
  float rotSpeed = 0.0001f;
  glfwGetCursorPos(window, &x, &y);     

  cam->yaw(-rotSpeed * (320 - x) * time);
  cam->pitch(-rotSpeed * (240 - y) * time);

  glfwSetCursorPos(window, 320, 240);
}
