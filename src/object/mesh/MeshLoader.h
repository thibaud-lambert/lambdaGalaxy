#ifndef LAMBDAGALAXY_MESHLOADER
#define LAMBDAGALAXY_MESHLOADER

#include "Mesh.h"

#include <Eigen/Geometry>

class MeshLoader
{
  public:
    static Mesh* loadMesh(const std::string& filename);

  private:
    static Mesh* loadObj(const std::string& filename);
};

#endif

