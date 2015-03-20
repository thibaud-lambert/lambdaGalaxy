#include "Camera.h"

#include <Eigen/Core>
#include <iostream>

  Camera::Camera(float width, float height, float fovY)
:orientation( Eigen::Quaternionf::Identity()), 
  position(0,0,0),
  projectionIsUpdate(false),
  viewIsUpdate(false)
{
   this->fovY = fovY;
   this->width = width;
   this->height = height;
   zFar = 50000.f;
   zNear = 0.1f;
}

const Eigen::Vector3f&
Camera::getPosition() const
{
  return position;
}

const Eigen::Affine3f&
Camera::getView()
{
  updateViewMatrix();
  return view;
}

const Eigen::Matrix4f&
Camera::getProjection()
{
  updateProjectionMatrix();
  return projection;
}

void
Camera::setPosition(const Eigen::Vector3f& pos)
{
  viewIsUpdate = false;
  position = pos;
}

void
Camera::move(float distance, Eigen::Vector3f& axis)
{
  viewIsUpdate = false;
  axis.normalize();
  position += orientation.toRotationMatrix() * axis * distance;
}

void
Camera::moveFoward(float distance)
{
  Eigen::Vector3f vec = Eigen::Vector3f(0,0,1);
  move(distance, vec);
}

void
Camera::moveVertical(float distance)
{
  Eigen::Vector3f vec(0.0f, 1.0f, 0.0f);
  move(distance, vec);
}

void
Camera::moveHorizontal(float distance)
{
  Eigen::Vector3f vec(1.0f, 0.0f, 0.0f);
  move(distance, vec);
}

void
Camera::rotate(float theta, const Eigen::Vector3f& axis)
{
  viewIsUpdate = false;
  Eigen::AngleAxisf angleAxis(theta, axis);
  Eigen::Quaternionf rot(angleAxis);
  rot.normalize();
  orientation = orientation * rot;
  orientation.normalize();
}

void
Camera::roll(float theta)
{
  rotate(theta, Eigen::Vector3f(0.0f, 0.0f, 1.0f));
}

void
Camera::pitch(float theta)
{
  rotate(theta, Eigen::Vector3f(1.0f, 0.0f, 0.0f));
}

void
Camera::yaw(float theta)
{
  rotate(theta, Eigen::Vector3f(0.0f, 1.0f, 0.0f));
}

void
Camera::updateViewMatrix()
{
  if(!viewIsUpdate)
  {
    view.linear() = orientation.conjugate().toRotationMatrix();
    view.translation() = - (view.linear() * position);
    viewIsUpdate = true;
  }
}

void
Camera::updateProjectionMatrix()
{
  if(!projectionIsUpdate)
  {
    projection.setIdentity();

    float xScale = yScale * height / width;
    projection(0,0) = xScale;
    projection(1,1) = yScale;

    projectionIsUpdate = true;
    float yScale = 1.0f / tan(fovY * 0.5);
    projection(2, 2) = -(zFar + zNear) / (zFar - zNear);
    projection(3, 2) = -1.0f;
    projection(2, 3) = -2.0f * zNear * zFar / (zFar - zNear);
    projection(3, 3) = 0.0f;
  }
}

