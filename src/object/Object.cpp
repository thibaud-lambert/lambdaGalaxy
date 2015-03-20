#include <Object.h>

Object::Object(Mesh* m, Shader* s)
  : m_shader(s)
  , m_mesh(m)
  , m_transMatrix(Eigen::Matrix4f::Identity())
{}

Object::~Object()
{
}


void
Object::setTransformation(const Eigen::Affine3f& mat)
{
  m_transMatrix = mat;
}

void
Object::draw(Camera& cam)
{
  m_shader->activate();

  sendUniform(cam);

  m_mesh->drawGeometry(m_shader->id(), false);
}

void
Object::sendUniform(Camera& cam)
{
    glUniformMatrix4fv(glGetUniformLocation(m_shader->id(), "matView"), 1, GL_FALSE, cam.getView().data());
    
    glUniformMatrix4fv(glGetUniformLocation(m_shader->id(), "matProj"), 1, GL_FALSE, cam.getProjection().data());

    glUniformMatrix4fv(glGetUniformLocation(m_shader->id(), "matObj"), 1, GL_FALSE, m_transMatrix.data());
}

