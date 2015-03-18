#ifndef LAMBDAGALAXY_MESH
#define LAMBDAGALAXY_MESH

#include "Vertex.h"

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <Eigen/Geometry>

class Mesh
{
  public:
  Mesh();
  void drawGeometry(int prg_id, bool usePatch);

  void addVertex(const Eigen::Vector3f &v);
  void addFaces(const Eigen::Vector3i &f);

  void displayInfo();

  private:
  std::vector<Vertex> vertices;
  std::vector<Eigen::Vector3i> faces;

  unsigned int vertexBufferId;
  unsigned int indexBufferId;
  unsigned int vertexArrayId;

  bool isInit;
};

#endif
