#ifndef LAMBDA_GALAXY_GAMELOOP
#define LAMBDA_GALAXY_GAMELOOP

#include <GLFW/glfw3.h>

class GameLoop
{
  private:
    static GLFWwindow * window;

    GameLoop();

  public:
    static void init();
    static void run();
    static void terminate();
};

#endif

