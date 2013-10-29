#include <06_CameraQuat/FreeFly.h>
#include <glm/gtx/quaternion.hpp>

FreeFly::FreeFly() : _targetRel(1., 0., 0)
{
  
}

FreeFly::~FreeFly()
{
  
}

void FreeFly::forward(double l)
{
  glm::vec3 t = _targetRel;
  t *= l;

  _position += t;
  glm::vec3 d(_targetRel[0], _targetRel[1], _targetRel[2]);
  _target = _position + d;
}

void FreeFly::left(double l)
{
  glm::vec3 left = glm::cross(_targetRel, _normal);

  //left = glm::normalize(left);

  left *= l;
  _position += left;
  _target = _position + _targetRel;
}

void FreeFly::normal(double l)
{
  glm::vec3 t(_normal);
  t *= l;

  _position += t;
  _target = _position + _targetRel;
}

void FreeFly::rotateForward(double angle)
{
  glm::quat q2 = glm::angleAxis((float) -angle, _targetRel);
  q2 = glm::normalize(q2);
  _quat = _quat * q2;
  
  this->updateVectRel();
}

void FreeFly::rotateLeft(double angle)
{
  glm::quat q2 = glm::angleAxis((float) -angle, _leftRel);
  q2 = glm::normalize(q2);
  _quat = _quat * q2;//glm::cross(_quat, q2);
  
  this->updateVectRel();
}

void FreeFly::rotateNormal(double angle)
{
  glm::quat q2 = glm::angleAxis((float) -angle, _normalRel);
  q2 = glm::normalize(q2);
  _quat = _quat * q2; //glm::cross(_quat, q2);
  
  this->updateVectRel();
}
#include <stdio.h>
void FreeFly::updateVectRel()
{
  // Récupération de l'angle de rotation
  
  _targetRel = glm::dvec3(1., 0., 0.);
  _leftRel = glm::dvec3(0., -1., 0.);
  _normalRel = glm::dvec3(0., 0., 1.);

  _quat = glm::normalize(_quat);

  _targetRel =  _targetRel * _quat;
  _leftRel = _leftRel * _quat;
  _normalRel = _normalRel * _quat;

  /*printf("%f %f %f\n", glm::dot(_targetRel, _leftRel),
                       glm::dot(_targetRel, _normalRel),
                       glm::dot(_leftRel, _normalRel));*/
  
  _target = _position + _targetRel;
  _normal = _normalRel;
}

