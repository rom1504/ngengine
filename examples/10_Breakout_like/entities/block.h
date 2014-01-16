#ifndef NGENGINE_EXAMPLES_10_BREAKOUT_LIKE_ENTITIES_BLOCK_H
#define NGENGINE_EXAMPLES_10_BREAKOUT_LIKE_ENTITIES_BLOCK_H

#include <ngengine/ngengine.h>

class BlockEntity {
  public:

    BlockEntity(nge::Sint32 x, nge::Sint32 y, nge::Uint8 r, nge::Uint8 g, nge::Uint8 b, nge::Uint8 a);
    ~BlockEntity();

    nge::video::D2::entity::Basic *get_graphic_entity();
    nge::collision::D2::BoundingBox *get_collision_entity();

  private:

    nge::video::D2::entity::Basic *_graphic_entity; // a rectangle drawn by opengl
    nge::collision::D2::BoundingBox  *_collision_entity; // the description of our form
};

#endif

