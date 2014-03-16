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

Eigen::Vector3f Camera::getPosition()
{
  return position;
}

Eigen::Affine3f Camera::getView()
{
  updateViewMatrix();
  return view;
}

Eigen::Matrix4f Camera::getProjection()
{
  updateProjectionMatrix();
  return projection;
}

void Camera::setPosition(Eigen::Vector3f pos)
{
  viewIsUpdate = false;
  position = pos;
}

void Camera::move(float distance, Eigen::Vector3f axis)
{
  viewIsUpdate = false;
  axis.normalize();
  position += orientation.toRotationMatrix() * axis * distance;
}

void Camera::moveFoward(float distance)
{
  move(distance,Eigen::Vector3f(0,0,1));
}

void Camera::moveVertical(float distance)
{

  move(distance,Eigen::Vector3f(0,1,0));
}

void Camera::moveHorizontal(float distance)
{
  move(distance,Eigen::Vector3f(1,0,0));
}

void Camera::rotate(float theta, Eigen::Vector3f axis)
{
  viewIsUpdate = false;
  Eigen::AngleAxisf angleAxis(theta, axis);
  Eigen::Quaternionf rot(angleAxis);
  rot.normalize();
  orientation = orientation * rot;
  orientation.normalize();
}

void Camera::roll(float theta)
{
  rotate(theta,Eigen::Vector3f(0,0,1));
}

void Camera::pitch(float theta)
{
  rotate(theta,Eigen::Vector3f(1,0,0));
}

void Camera::yaw(float theta)
{
  rotate(theta,Eigen::Vector3f(0,1,0));
}

void Camera::updateViewMatrix()
{
  if(!viewIsUpdate)
  {
    view.linear() = orientation.conjugate().toRotationMatrix();
    view.translation() = - (view.linear() * position);
    viewIsUpdate = true;
  }
}

void Camera::updateProjectionMatrix()
{
  if(!projectionIsUpdate)
  {
    projection.setIdentity();

    float yScale = 1./tan(fovY*0.5);
    float xScale = yScale * height / width;
    projection(0,0) = xScale;
    projection(1,1) = yScale;
    projection(2,2) = -(zFar+zNear)/(zFar-zNear);
    projection(3,2) = -1;
    projection(2,3) = -2*zNear*zFar/(zFar-zNear);
    projection(3,3) = 0;

    projectionIsUpdate = true;
  }
}

