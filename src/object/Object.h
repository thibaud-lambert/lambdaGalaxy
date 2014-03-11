#ifndef LAMBDAGALAXY_OBJECT_H
#define LAMBDAGALAXY_OBJECT_H

#include <Mesh.h>
#include <Shader.h>
#include <Eigen/Geometry>
#include "Camera.h"

class Object
{
public:
    Object(Mesh *mesh, Shader* shader);
    void setTransformation(const Eigen::Affine3f& mat);
    void draw(Camera &cam);

protected:
    Shader* shader;
    Mesh* mesh;
    Eigen::Affine3f transMatrix;
};

#endif
