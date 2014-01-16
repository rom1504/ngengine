#include <10_Breakout_like/entities/block.h>
#include <10_Breakout_like/shaders.h>
#include <stdlib.h>
#include <string.h>

BlockEntity::BlockEntity(nge::Sint32 x, nge::Sint32 y, nge::Uint8 r, nge::Uint8 g, nge::Uint8 b, nge::Uint8 a)
{
  nge::Sint32 vertices_tmp[] = {
    0, 0,
    80, 0,
    0, 30,
    80, 30
  };

  nge::Uint8 colors_tmp[] = {
    r, g, b, a,
    r, g, b, a,
    r, g, b, a,
    r, g, b, a
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

BlockEntity::~BlockEntity()
{
  delete _graphic_entity;
}

nge::video::D2::entity::Basic *BlockEntity::get_graphic_entity()
{
  return _graphic_entity;
}

nge::collision::D2::BoundingBox *BlockEntity::get_collision_entity()
{
  return _collision_entity;
}

