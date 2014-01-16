#include <10_Breakout_like/entities/player.h>
#include <10_Breakout_like/shaders.h>

PlayerEntity::PlayerEntity()
{
  static nge::Sint32 vertices[] = {
    0, 0,
    200, 0,
    0, 20,
    200, 20
  };

  static nge::Uint8 colors[] = {
    255, 255, 255, 255,
    255, 255, 255, 255,
    255, 255, 255, 255,
    255, 255, 255, 255
  };

  _graphic_entity = new nge::video::D2::entity::Basic(4, 1, GL_TRIANGLE_STRIP);
  _graphic_entity->_shader = shader_color;
  _graphic_entity->setVertexBuf(vertices, false);  // (x, y) couples
  _graphic_entity->setColorBuf(colors, false);

  *(_graphic_entity->getPosition()) = glm::vec2(300, 560);

  _collision_entity = new nge::collision::D2::BoundingBox();

}

PlayerEntity::~PlayerEntity()
{
  delete _graphic_entity;
}

void PlayerEntity::move(nge::Sint32 dx)
{
  (*(_graphic_entity->getPosition()))[0] += dx;
}

nge::video::D2::entity::Basic *PlayerEntity::get_graphic_entity()
{
  return _graphic_entity;
}

nge::collision::D2::BoundingBox *PlayerEntity::get_collision_entity()
{
  return _collision_entity;
}

