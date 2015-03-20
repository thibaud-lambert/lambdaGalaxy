#include "PlanetarySystem.h"

#include "MeshLoader.h"
#include <cstdlib>
#include <Eigen/Geometry>

Mesh* PlanetarySystem::mesh = NULL;
Shader* PlanetarySystem::shader = NULL;
bool PlanetarySystem::assetsAreLoad = false;

PlanetarySystem::PlanetarySystem(int i, int j, int k)
  : x(i), y(j), z(k), star(NULL)
{
  if (!assetsAreLoad)
    loadAssets();

  float starx, stary, starz;
  starx = i * PLANETARY_SYSTEM_SIZE + rand() % PLANETARY_SYSTEM_SIZE;
  stary = j * PLANETARY_SYSTEM_SIZE + rand() % PLANETARY_SYSTEM_SIZE;
  starz = k * PLANETARY_SYSTEM_SIZE + rand() % PLANETARY_SYSTEM_SIZE;

  star = new Star(mesh, shader);
  Eigen::Affine3f M = (Eigen::Affine3f) Eigen::Translation3f(starx, stary, starz);
  star->setTransformation(M);
}

void
PlanetarySystem::draw(Camera& cam)
{
  star->draw(cam);
}

void
PlanetarySystem::loadAssets()
{
  if (!assetsAreLoad)
  {
    mesh = MeshLoader::loadMesh("../data/icoSphere.obj");

    shader = new Shader();
    shader->loadFromFiles("../shader/star/star.vert", "../shader/star/star.frag", "", "", "");

    assetsAreLoad = true;
  }
}
