#ifndef LAMBDA_GALAXY_PLANETARYSYSTEM
#define LAMBDA_GALAXY_PLANETARYSYSTEM

#include "Object.h"
#include "Camera.h"
#include "Star.h"

#define PLANETARY_SYSTEM_SIZE 300

class PlanetarySystem
{
  public:
    PlanetarySystem(int i, int j, int k);
    void draw(Camera& cam);

  private:
    static void loadAssets();

    int m_x;
    int m_y;
    int m_z;
    Star* m_star;
    static Mesh* s_mesh;
    static Shader* s_shader;
    static bool s_assetsAreLoad;
};

#endif

