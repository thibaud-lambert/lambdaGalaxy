#include "Vertex.h"

Vertex::Vertex()
    : position(Eigen::Vector3f::Zero()), normal(Eigen::Vector3f::Zero()), texcoord(Eigen::Vector2f::Zero())
{
}

Vertex::Vertex(const Eigen::Vector3f& pos)
  : position(pos), normal(Eigen::Vector3f::Zero()), texcoord(Eigen::Vector2f::Zero())
{
}


