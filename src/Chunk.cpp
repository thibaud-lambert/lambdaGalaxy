#include "Chunk.h"

Chunk::Chunk(const Eigen::Vector3i& index)
  : m_index(index)
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
        m_planetarySystemGrid[i][j][k] = new PlanetarySystem(PLANETARY_SYSTEM_NUMBER_BY_CHUNK * index + Eigen::Vector3i(i, j, k));
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

