#include "PlanetarySystem.h"

#include "MeshLoader.h"
#include <cstdlib>
#include <Eigen/Geometry>

Mesh* PlanetarySystem::s_mesh = NULL;
Shader* PlanetarySystem::s_shader = NULL;
bool PlanetarySystem::s_assetsAreLoad = false;

PlanetarySystem::PlanetarySystem(int i, int j, int k)
  : m_x(i), m_y(j), m_z(k), m_star(NULL)
{
  if (!s_assetsAreLoad)
    loadAssets();

  float starx, stary, starz;
  starx = i * PLANETARY_SYSTEM_SIZE + rand() % PLANETARY_SYSTEM_SIZE;
  stary = j * PLANETARY_SYSTEM_SIZE + rand() % PLANETARY_SYSTEM_SIZE;
  starz = k * PLANETARY_SYSTEM_SIZE + rand() % PLANETARY_SYSTEM_SIZE;

  m_star = new Star(s_mesh, s_shader);
  Eigen::Affine3f M = (Eigen::Affine3f) Eigen::Translation3f(starx, stary, starz);
  m_star->setTransformation(M);
}

void
PlanetarySystem::draw(Camera& cam)
{
  m_star->draw(cam);
}

void
PlanetarySystem::loadAssets()
{
  if (!s_assetsAreLoad)
  {
    s_mesh = MeshLoader::loadMesh("../data/icoSphere.obj");

    s_shader = new Shader();
    s_shader->loadFromFiles("../shader/star/star.vert", "../shader/star/star.frag", "", "", "");

    s_assetsAreLoad = true;
  }
}
