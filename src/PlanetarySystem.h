#ifndef LAMBDA_GALAXY_PLANETARYSYSTEM
#define LAMBDA_GALAXY_PLANETARYSYSTEM

#include "Object.h"
#include "Camera.h"
#include "Star.h"

#define PLANETARY_SYSTEM_SIZE 300

class PlanetarySystem
{
  public:
    PlanetarySystem(const Eigen::Vector3i& index);
    void draw(Camera& cam);

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  private:
    static void loadAssets();

    Eigen::Vector3i m_index;
    Star* m_star;
    static Mesh* s_mesh;
    static Shader* s_shader;
    static bool s_assetsAreLoad;
};

#endif

