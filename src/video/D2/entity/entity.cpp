#include <ngengine/video/D2/entity/entity.h>

using namespace nge;
using namespace nge::video;
using namespace nge::video::D2;

Entity::~Entity()
{
  _angle = 0.;
  _shader = nullptr;
}

void Entity::draw()
{
  this->drawAtPosition(_pos[0], _pos[1]);
}

void Entity::drawWithOffset(Sint32 x, Sint32 y)
{
  this->drawAtPosition(_pos[0] + x, _pos[1] + y);
}

glm::vec2 *Entity::getPosition()
{
  return &_pos;
}

double *Entity::getAngle()
{
  return &_angle;
}

