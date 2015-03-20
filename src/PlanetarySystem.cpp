#include "PlanetarySystem.h"

#include "MeshLoader.h"
#include <cstdlib>
#include <Eigen/Geometry>

Mesh* PlanetarySystem::s_mesh = NULL;
Shader* PlanetarySystem::s_shader = NULL;
bool PlanetarySystem::s_assetsAreLoad = false;

PlanetarySystem::PlanetarySystem(const Eigen::Vector3i& index)
  : m_index(index)
  , m_star(NULL)
{
  if (!s_assetsAreLoad)
    loadAssets();

  Eigen::Vector3f randomVector(rand() % PLANETARY_SYSTEM_SIZE,
                               rand() % PLANETARY_SYSTEM_SIZE,
                               rand() % PLANETARY_SYSTEM_SIZE);
  Eigen::Vector3f starPosition = float(PLANETARY_SYSTEM_SIZE) * Eigen::Vector3f(index[0], index[1], index[2]) + randomVector;
  Eigen::Affine3f M = (Eigen::Affine3f) Eigen::Translation3f(starPosition);

  m_star = new Star(s_mesh, s_shader);
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
