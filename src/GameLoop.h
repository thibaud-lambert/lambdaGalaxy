#ifndef LAMBDA_GALAXY_GAMELOOP
#define LAMBDA_GALAXY_GAMELOOP

#include <GLFW/glfw3.h>

class GameLoop
{
  private:
    GLFWwindow * window;

  protected:
    void render();
    void update();

  public:
    GameLoop();

    void init();
    void run();
    void terminate();
};

#endif

