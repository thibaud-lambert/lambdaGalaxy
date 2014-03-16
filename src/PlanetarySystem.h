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
    void draw(Camera &cam);

  private:
    int x;
    int y;
    int z;
    Star * star;

    static void loadAssets();
    static Mesh * mesh;
    static Shader * shader;
    static bool assetsAreLoad;
};

#endif

