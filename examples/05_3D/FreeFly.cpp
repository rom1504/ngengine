#include <05_3D/FreeFly.h>
#include <glm/gtc/quaternion.hpp>
#include <math.h>

FreeFly::FreeFly() : _targetRel(1., 0., 0)
{
}

FreeFly::~FreeFly()
{
}

void FreeFly::forward(double l)
{
  glm::vec3 t = _targetRelCart;
  t *= l;

  _position += t;
  this->update();
}

void FreeFly::left(double l)
{
  glm::vec3 left = _leftCart;
  
  left *= l;
  _position += left;

  this->update();
}

void FreeFly::normal(double l)
{
  glm::vec3 t = _normal;
  t *= l;

  _position += t;
  this->update();
}

void FreeFly::rotateLeft(double angle)
{
  _targetRel[1] += angle;

  if(_targetRel[1] > M_PI / 2.) {
    _targetRel[1] = M_PI / 2. - 0.001;
  }

  if(_targetRel[1] < - M_PI / 2.) {
    _targetRel[1] = - M_PI / 2. + 0.001;
  }

  this->update();
}

void FreeFly::rotateNormal(double angle)
{
  _targetRel[2] += angle;

  this->update();
}

glm::vec3 FreeFly::getCartesianTargetRel()
{
  glm::vec3 targetRel(
    _targetRel[0] * cos(_targetRel[1]) * cos(_targetRel[2]),
    _targetRel[0] * cos(_targetRel[1]) * sin(_targetRel[2]),
    _targetRel[0] * sin(_targetRel[1])
  );

  return targetRel;
}

void FreeFly::update()
{
  _targetRelCart = this->getCartesianTargetRel();

  _leftCart = glm::cross(_targetRelCart, _normal);
  _leftCart = glm::normalize(_leftCart);

  _target = _position + _targetRelCart;
}

