#ifndef NGENGINE_EXAMPLES_10_BREAKOUT_LIKE_ENTITIES_PLAYER_H
#define NGENGINE_EXAMPLES_10_BREAKOUT_LIKE_ENTITIES_PLAYER_H

#include <ngengine/ngengine.h>

class PlayerEntity {
  public:

    PlayerEntity();
    ~PlayerEntity();

    void move(nge::Sint32 dx);

    nge::video::D2::entity::Basic *get_graphic_entity();
    nge::collision::D2::BoundingBox *get_collision_entity();

  private:

    nge::video::D2::entity::Basic *_graphic_entity; // a rectangle drawn by opengl
    nge::collision::D2::BoundingBox  *_collision_entity; // the description of our form
};

#endif

