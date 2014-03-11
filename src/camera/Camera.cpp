#include "Camera.h"

#include <Eigen/Core>
#include <iostream>

  Camera::Camera(float width, float height, float fovY)
:orientation(Eigen::AngleAxisf(0,Eigen::Vector3f(1,1,1))), 
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
  position += axis * distance;
}

void Camera::moveFoward(float distance)
{
  move(distance,getFront());
}

void Camera::moveVertical(float distance)
{

  move(distance,getVertical());
}

void Camera::moveHorizontal(float distance)
{
  move(distance,getHorizontal());
}

void Camera::rotate(float theta, Eigen::Vector3f axis)
{
  viewIsUpdate = false;
  Eigen::AngleAxisf angleAxis(theta, axis);
  Eigen::Quaternionf rot(angleAxis);
  rot.norm();
  rot = orientation * rot;
  rot.norm();
  orientation = rot;
}

void Camera::roll(float theta)
{
  rotate(theta,getFront());
}

void Camera::pitch(float theta)
{
  rotate(theta,getHorizontal());
}

void Camera::yaw(float theta)
{
  rotate(theta,getVertical());
}

Eigen::Vector3f Camera::getFront()
{
  Eigen::Matrix3f orientMat = orientation.matrix();
  Eigen::Vector3f axis(orientMat(2,0), orientMat(2,1), orientMat(2,2));
  axis.normalize();
  return axis;
}

Eigen::Vector3f Camera::getVertical()
{
  Eigen::Matrix3f orientMat = orientation.matrix();
  Eigen::Vector3f axis(orientMat(1,0), orientMat(1,1), orientMat(1,2));
  axis.normalize();
  return axis;
}

Eigen::Vector3f Camera::getHorizontal()
{
  Eigen::Matrix3f orientMat = orientation.matrix();
  Eigen::Vector3f axis(orientMat(0,0), orientMat(0,1), orientMat(0,2));
  axis.normalize();
  return axis;
}

void Camera::updateViewMatrix()
{
  if(!viewIsUpdate)
  {
    view = orientation * Eigen::Translation3f(position);
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

