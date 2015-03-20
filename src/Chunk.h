#ifndef LAMBDA_GALAXY_CHUNK
#define LAMBDA_GALAXY_CHUNK

#include "Camera.h"
#include "PlanetarySystem.h"

#define PLANETARY_SYSTEM_NUMBER_BY_CHUNK 4
#define CHUNK_SIZE (PLANETARY_SYSTEM_NUMBER_BY_CHUNK * PLANETARY_SYSTEM_SIZE)

class Chunk
{
  public:
    Chunk(const Eigen::Vector3i& index);
    void draw(Camera& cam);

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  private:
    Eigen::Vector3i m_index;
    PlanetarySystem**** m_planetarySystemGrid;
};

#endif
