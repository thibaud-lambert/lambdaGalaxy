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
    void updateDelete(int x, int y, int z);
    void updateMove(int x, int y, int z);
    void updateNew();
    Chunk**** chunkGrid;
    int range;
    Eigen::Vector3i position;
};

#endif

