#ifndef LAMBDAGALAXY_CAMERA_H
#define LAMBDAGALAXY_CAMERA_H

#include <Eigen/Geometry>

class Camera
{
  public:
    Camera(float width, float height, float fovY = M_PI / 3);

    /* Getter */
    const Eigen::Vector3f& getPosition() const;
    const Eigen::Affine3f& getView();
    const Eigen::Matrix4f& getProjection();

    /* Setter */
    void setPosition(const Eigen::Vector3f& pos);

    /* Move camera */
    void move(float distance, Eigen::Vector3f& axis);
    void moveFoward(float distance);
    void moveVertical(float distance);
    void moveHorizontal(float distance);

    /* Rotate camera */
    void rotate(float theta, const Eigen::Vector3f& axis);
    void roll(float theta);
    void pitch(float theta);
    void yaw(float theta);

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  private:
    void updateViewMatrix();
    void updateProjectionMatrix();

    Eigen::Quaternionf m_orientation;
    Eigen::Vector3f m_position;
    Eigen::Affine3f m_view;
    Eigen::Matrix4f m_projection;

    float m_fovY;
    float m_zFar;
    float m_zNear;
    float m_width;
    float m_height;

    bool m_projectionIsUpdate;
    bool m_viewIsUpdate;

};

#endif
