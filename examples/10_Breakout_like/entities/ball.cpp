#include <10_Breakout_like/entities/ball.h>
#include <10_Breakout_like/shaders.h>
#include <stdlib.h>
#include <string.h>

BallEntity::BallEntity(nge::Sint32 x, nge::Sint32 y, nge::Sint32 dx, nge::Sint32 dy)
{
  _dx = dx;
  _dy = dy;

  nge::Sint32 vertices_tmp[] = {
    0, 0,
    20, 0,
    0, 20,
    20, 20
  };

  nge::Uint8 colors_tmp[] = {
    255, 255, 0, 255,
    255, 255, 0, 255,
    255, 255, 0, 255,
    255, 255, 0, 255
  };

  nge::Sint32 *vertices = (nge::Sint32 *) malloc(sizeof(nge::Sint32) * 8);
  nge::Uint8 *colors = (nge::Uint8 *) malloc(sizeof(nge::Uint8) * 16);

  memcpy(vertices, vertices_tmp, sizeof(nge::Sint32) * 8);
  memcpy(colors, colors_tmp, sizeof(nge::Uint8) * 16);

  _graphic_entity = new nge::video::D2::entity::Basic(4, 1, GL_TRIANGLE_STRIP);
  _graphic_entity->_shader = shader_color;
  _graphic_entity->setVertexBuf(vertices, true);  // (x, y) couples
  _graphic_entity->setColorBuf(colors, true);

  *(_graphic_entity->getPosition()) = glm::vec2(x, y);

  _collision_entity = new nge::collision::D2::BoundingBox();
  
}

BallEntity::~BallEntity()
{
  delete _graphic_entity;
}

void BallEntity::move(nge::Sint32 dx, nge::Sint32 dy)
{
  (*(_graphic_entity->getPosition())) += glm::vec2(dx, dy);
}

nge::video::D2::entity::Basic *BallEntity::get_graphic_entity()
{
  return _graphic_entity;
}

nge::collision::D2::BoundingBox *BallEntity::get_collision_entity()
{
  return _collision_entity;
}

