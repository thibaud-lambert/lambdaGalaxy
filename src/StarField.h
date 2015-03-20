#ifndef LAMBDA_GALAXY_STARFIELD
#define LAMBDA_GALAXY_STARFIELD

#include "Camera.h"
#include "Chunk.h"

#include <Eigen/Geometry>

#define CHUNK_NUMBER 5

class StarField
{
  public:
    StarField();
    void init(const Eigen::Vector3f& pos);
    void update(const Eigen::Vector3f& pos);
    void draw(Camera& cam);
    float getDist(const Eigen::Vector3f& pos);

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  private:
    void updateDelete(const Eigen::Vector3i& pos);
    void updateMove(const Eigen::Vector3i& pos);
    void updateNew();

    Chunk**** m_chunkGrid;
    Eigen::Vector3i m_position;
};

#endif

