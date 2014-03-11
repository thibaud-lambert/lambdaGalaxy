#include <Object.h>

Object::Object(Mesh *m, Shader *s)
    :mesh(m), shader(s), transMatrix(Eigen::Matrix4f::Identity())
{}

void Object::setTransformation(const Eigen::Affine3f &mat)
{
    transMatrix = mat;
}

void Object::draw(Camera &cam)
{
    shader->activate();

    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"matView"), 1, GL_FALSE, cam.getView().data());
    
    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"matProj"), 1, GL_FALSE, cam.getProjection().data());

    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"matObj"),  1, GL_FALSE, transMatrix.data());

    mesh->drawGeometry(shader->id(),false);
}

