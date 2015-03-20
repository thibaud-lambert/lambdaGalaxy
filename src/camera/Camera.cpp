#include "Camera.h"

#include <Eigen/Core>
#include <iostream>

Camera::Camera(float width, float height, float fovY)
  : m_orientation(Eigen::Quaternionf::Identity())
  , m_position(0, 0, 0)
  , m_fovY(fovY)
  , m_zFar(50000.0f)
  , m_zNear(0.1f)
  , m_width(width)
  , m_height(height)
  , m_projectionIsUpdate(false)
  , m_viewIsUpdate(false)
{
}

const Eigen::Vector3f&
Camera::getPosition() const
{
  return m_position;
}

const Eigen::Affine3f&
Camera::getView()
{
  updateViewMatrix();
  return m_view;
}

const Eigen::Matrix4f&
Camera::getProjection()
{
  updateProjectionMatrix();
  return m_projection;
}

void
Camera::setPosition(const Eigen::Vector3f& pos)
{
  m_viewIsUpdate = false;
  m_position = pos;
}

void
Camera::move(float distance, Eigen::Vector3f& axis)
{
  m_viewIsUpdate = false;
  axis.normalize();
  m_position += m_orientation.toRotationMatrix() * axis * distance;
}

void
Camera::moveFoward(float distance)
{
  Eigen::Vector3f vec(0.0f, 0.0f, 1.0f);
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
  m_viewIsUpdate = false;
  Eigen::AngleAxisf angleAxis(theta, axis);
  Eigen::Quaternionf rot(angleAxis);
  rot.normalize();
  m_orientation *= rot;
  m_orientation.normalize();
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
  if(!m_viewIsUpdate)
  {
    m_view.linear() = m_orientation.conjugate().toRotationMatrix();
    m_view.translation() = -(m_view.linear() * m_position);
    m_viewIsUpdate = true;
  }
}

void
Camera::updateProjectionMatrix()
{
  if (!m_projectionIsUpdate)
  {
    m_projection.setIdentity();

    float yScale = 1.0f / tan(m_fovY * 0.5);
    float xScale = yScale * m_height / m_width;
    m_projection(0, 0) = xScale;
    m_projection(1, 1) = yScale;
    m_projection(2, 2) = -(m_zFar + m_zNear) / (m_zFar - m_zNear);
    m_projection(3, 2) = -1.0f;
    m_projection(2, 3) = -2.0f * m_zNear * m_zFar / (m_zFar - m_zNear);
    m_projection(3, 3) = 0.0f;

    m_projectionIsUpdate = true;
  }
}

