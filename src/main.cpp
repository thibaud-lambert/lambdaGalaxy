#include <GLFW/glfw3.h>
#include "GameLoop.h"

int main(void)
{
  GameLoop::init();
  GameLoop::run();
  GameLoop::terminate();
  return 0;
}
