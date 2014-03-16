#include "Chunk.h"

Chunk::Chunk(int x, int y, int z)
  :x(x), y(y), z(z)
{
  int i,j,k;
  planetarySystemGrid = new PlanetarySystem***[PLANETARY_SYSTEM_NUMBER_BY_CHUNK];
  for(i=0; i<PLANETARY_SYSTEM_NUMBER_BY_CHUNK; i++)
  {
    planetarySystemGrid[i] = new PlanetarySystem**[PLANETARY_SYSTEM_NUMBER_BY_CHUNK];
    for(j=0; j<PLANETARY_SYSTEM_NUMBER_BY_CHUNK; j++)
    {
      planetarySystemGrid[i][j] = new PlanetarySystem*[PLANETARY_SYSTEM_NUMBER_BY_CHUNK];
      for(k=0; k<PLANETARY_SYSTEM_NUMBER_BY_CHUNK; k++)
      {
        planetarySystemGrid[i][j][k] = new PlanetarySystem(x*PLANETARY_SYSTEM_NUMBER_BY_CHUNK+i, y*PLANETARY_SYSTEM_NUMBER_BY_CHUNK+j, z*PLANETARY_SYSTEM_NUMBER_BY_CHUNK+k);
      }
    }
  }
}

void Chunk::draw(Camera &cam)
{
  int i,j,k;
  for(i=0; i<PLANETARY_SYSTEM_NUMBER_BY_CHUNK; i++)
  {
    for(j=0; j<PLANETARY_SYSTEM_NUMBER_BY_CHUNK; j++)
    {
      for(k=0; k<PLANETARY_SYSTEM_NUMBER_BY_CHUNK; k++)
      {
        planetarySystemGrid[i][j][k]->draw(cam);
      }
    }
  }
}

