#include "Star.h"

#include <cstdlib>
#include <iostream>

Star::Star(Mesh* mesh, Shader* shader)
  : Object(mesh, shader)
{
  scale = 0.1f + ((rand() * 1.0f) /RAND_MAX) * 2.0f;
  color[0] = (rand() * 1.0f) / RAND_MAX;
  color[1] = (rand() * 1.0f) / RAND_MAX;
  color[2] = (rand() * 1.0f) / RAND_MAX;
}

Star::~Star()
{
}

void
Star::setTransformation(const Eigen::Affine3f& mat)
{
  Object::setTransformation(mat * Eigen::Scaling(scale));
}

void
Star::sendUniform(Camera& cam)
{
  Object::sendUniform(cam);

  glUniform3fv(glGetUniformLocation(shader->id(), "color"), 1, color.data());
}

