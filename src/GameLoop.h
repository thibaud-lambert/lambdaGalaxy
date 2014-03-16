#ifndef LAMBDA_GALAXY_GAMELOOP
#define LAMBDA_GALAXY_GAMELOOP


#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "StarField.h"

class GameLoop
{
  public:
    GameLoop();

    void init();
    void run();
    void terminate();

  protected:
    void render();
    void update();
    void initScene();
    void inputHandler();

  private:

      GLFWwindow * window;

     Camera * cam;

      StarField * starField;
};

#endif

