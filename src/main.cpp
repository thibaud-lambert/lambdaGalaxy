#include "GameLoop.h"

int main(void)
{
  GameLoop * gameloop = new GameLoop();
  gameloop->init();
  gameloop->run();
  gameloop->terminate();
  return 0;
}
