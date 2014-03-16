#include "Star.h"

#include <cstdlib>
#include <iostream>

Star::Star(Mesh * mesh, Shader * shader)
  :Object(mesh,shader)
{
  scale = 0.1 + ((rand() * 1.) /RAND_MAX) * 2;
  color[0] = (rand() * 1.) / RAND_MAX;
  color[1] = (rand() * 1.) / RAND_MAX;
  color[2] = (rand() * 1.) / RAND_MAX;
}

Star::~Star()
{
}

void Star::setTransformation(const Eigen::Affine3f& mat)
{
  Object::setTransformation(mat * Eigen::Scaling(scale));
}

void Star::sendUniform(Camera &cam)
{
  Object::sendUniform(cam);

  glUniform3fv(glGetUniformLocation(shader->id(),"color"),  1, color.data());
}

