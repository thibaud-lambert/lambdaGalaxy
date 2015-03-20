#ifndef LAMBDAGALAXY_OBJECT_H
#define LAMBDAGALAXY_OBJECT_H

#include <Mesh.h>
#include <Shader.h>
#include <Eigen/Geometry>
#include "Camera.h"

class Object
{
public:
    Object(Mesh* mesh, Shader* shader);
    virtual ~Object();
    virtual void setTransformation(const Eigen::Affine3f& mat);
    virtual void draw(Camera& cam);

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

protected:
    virtual void sendUniform(Camera& cam);

    Shader* shader;
    Mesh* mesh;
    Eigen::Affine3f transMatrix;
};

#endif
