#include "Star.h"

#include <cstdlib>
#include <iostream>

Star::Star(Mesh* mesh, Shader* shader)
  : Object(mesh, shader)
{
  m_scale = 0.1f + ((rand() * 1.0f) /RAND_MAX) * 2.0f;
  m_color[0] = (rand() * 1.0f) / RAND_MAX;
  m_color[1] = (rand() * 1.0f) / RAND_MAX;
  m_color[2] = (rand() * 1.0f) / RAND_MAX;
}

Star::~Star()
{
}

void
Star::setTransformation(const Eigen::Affine3f& mat)
{
  Object::setTransformation(mat * Eigen::Scaling(m_scale));
}

void
Star::sendUniform(Camera& cam)
{
  Object::sendUniform(cam);

  glUniform3fv(glGetUniformLocation(m_shader->id(), "color"), 1, m_color.data());
}

