#include "Chunk.h"

Chunk::Chunk(int x, int y, int z)
  :m_x(x), m_y(y), m_z(z)
{
  m_planetarySystemGrid = new PlanetarySystem***[PLANETARY_SYSTEM_NUMBER_BY_CHUNK];
  for (int i = 0; i < PLANETARY_SYSTEM_NUMBER_BY_CHUNK; i++)
  {
    m_planetarySystemGrid[i] = new PlanetarySystem**[PLANETARY_SYSTEM_NUMBER_BY_CHUNK];
    for (int j = 0; j < PLANETARY_SYSTEM_NUMBER_BY_CHUNK; j++)
    {
      m_planetarySystemGrid[i][j] = new PlanetarySystem*[PLANETARY_SYSTEM_NUMBER_BY_CHUNK];
      for (int k = 0; k < PLANETARY_SYSTEM_NUMBER_BY_CHUNK; k++)
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
  for (int i = 0; i < PLANETARY_SYSTEM_NUMBER_BY_CHUNK; i++)
  {
    for (int j = 0; j < PLANETARY_SYSTEM_NUMBER_BY_CHUNK; j++)
    {
      for (int k = 0; k < PLANETARY_SYSTEM_NUMBER_BY_CHUNK; k++)
      {
        m_planetarySystemGrid[i][j][k]->draw(cam);
      }
    }
  }
}

