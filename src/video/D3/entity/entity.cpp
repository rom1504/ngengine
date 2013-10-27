#include <ngengine/video/D3/entity/entity.h>

using namespace nge;
using namespace nge::video;
using namespace nge::video::D3;
using namespace nge::video::D3::entity;

Entity::Entity() : _rotation(0., 0., 0., 1.)
{

}

Entity::~Entity() 
{
}

void Entity::draw()
{
  this->drawAtPosition(_pos);
}

void Entity::drawWithOffset(glm::vec3 offset)
{
  this->drawAtPosition(_pos + offset);
}

glm::vec3 *Entity::getPosition()
{
  return &_pos;
}

glm::vec4 *Entity::getRotation()
{
  return &_rotation;
}

