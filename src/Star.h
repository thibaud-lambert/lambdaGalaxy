#ifndef LAMBDA_GALAXY_STAR
#define LAMBDA_GALAXY_STAR

#include "Object.h"
#include <Eigen/Geometry>

class Star : public Object
{
  public:
    Star(Mesh * mesh, Shader * shader);
    ~Star();
    virtual void setTransformation(const Eigen::Affine3f& mat);

  private:
    virtual void sendUniform(Camera &cam);

    float scale;
    Eigen::Vector3f color;
};

#endif 

