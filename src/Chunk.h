#ifndef LAMBDA_GALAXY_CHUNK
#define LAMBDA_GALAXY_CHUNK

#include "Camera.h"
#include "PlanetarySystem.h"

#define PLANETARY_SYSTEM_NUMBER_BY_CHUNK 4
#define CHUNK_SIZE (PLANETARY_SYSTEM_NUMBER_BY_CHUNK * PLANETARY_SYSTEM_SIZE)

class Chunk
{
  public:
    Chunk(int x, int y, int z);
    void draw(Camera& cam);
  private:
    int x, y, z;
    PlanetarySystem**** planetarySystemGrid;
};

#endif
