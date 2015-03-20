#include "Chunk.h"

Chunk::Chunk(int x, int y, int z)
  :m_x(x), m_y(y), m_z(z)
{
  int i, j, k;
  m_planetarySystemGrid = new PlanetarySystem***[PLANETARY_SYSTEM_NUMBER_BY_CHUNK];
  for (i = 0; i < PLANETARY_SYSTEM_NUMBER_BY_CHUNK; i++)
  {
    m_planetarySystemGrid[i] = new PlanetarySystem**[PLANETARY_SYSTEM_NUMBER_BY_CHUNK];
    for (j = 0; j < PLANETARY_SYSTEM_NUMBER_BY_CHUNK; j++)
    {
      m_planetarySystemGrid[i][j] = new PlanetarySystem*[PLANETARY_SYSTEM_NUMBER_BY_CHUNK];
      for (k = 0; k < PLANETARY_SYSTEM_NUMBER_BY_CHUNK; k++)
      {
        m_planetarySystemGrid[i][j][k] = new PlanetarySystem(m_x * PLANETARY_SYSTEM_NUMBER_BY_CHUNK + i,
                                                             m_y * PLANETARY_SYSTEM_NUMBER_BY_CHUNK + j,
                                                             m_z * PLANETARY_SYSTEM_NUMBER_BY_CHUNK + k);
      }
    }
  }
}

void
Chunk::draw(Camera& cam)
{
  int i, j, k;
  for (i = 0; i < PLANETARY_SYSTEM_NUMBER_BY_CHUNK; i++)
  {
    for (j = 0; j < PLANETARY_SYSTEM_NUMBER_BY_CHUNK; j++)
    {
      for (k = 0; k < PLANETARY_SYSTEM_NUMBER_BY_CHUNK; k++)
      {
        m_planetarySystemGrid[i][j][k]->draw(cam);
      }
    }
  }
}

