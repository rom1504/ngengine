#include <ngengine/video/D3/camera/camera.h>

using namespace nge;
using namespace nge::video;
using namespace D3;

Camera::Camera() : _position(0., 0., 0.), _target(1., 0., 0.), _normal(0., 0., 1.)
{
  _fovy = 70;
  _aspect = 640./480.;
  _zNear = 1.;
  _zFar = 1000.;
}

Camera::~Camera()
{

}

glm::vec3 *Camera::getPosition()
{
  return &_position;
}

glm::vec3 *Camera::getTarget()
{
  return &_target;
}

glm::vec3 *Camera::getNormal()
{
  return &_normal;
}

double Camera::getFovy()
{
  return _fovy;
}

double Camera::getAspect()
{
  return _aspect;
}

double Camera::getZNear()
{
  return _zNear;
}

double Camera::getZFar()
{
  return _zFar;
}

void Camera::setFovy(double d)
{
  _fovy = d;
}

void Camera::setAspect(double width, double height)
{
  _aspect = width / height;
}

void Camera::setAspect(double d)
{
  _aspect = d;
}

void Camera::setZNear(double z)
{
  _zNear = z;
}

void Camera::setZFar(double z)
{
  _zFar = z;
}

