#ifndef LAMBDA_GALAXY_GAMELOOP
#define LAMBDA_GALAXY_GAMELOOP


#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "MeshLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Object.h"
#include "Camera.h"

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

      Mesh * mesh;
      Shader * shader;
      Object * object;
      Camera * cam;
};

#endif

