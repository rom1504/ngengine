#ifndef NGENGINE_EXAMPLES_10_BREAKOUT_LIKE_ENTITIES_BALL_H
#define NGENGINE_EXAMPLES_10_BREAKOUT_LIKE_ENTITIES_BALL_H

#include <ngengine/ngengine.h>

class BallEntity {
  public:

    BallEntity(nge::Sint32 x, nge::Sint32 y, nge::Sint32 dx, nge::Sint32 dy);
    ~BallEntity();

    void move(nge::Sint32 dx, nge::Sint32 dy);

    void set(nge::Sint32 dx, nge::Sint32 dy);
    void move();

    void invert_dx();
    void invert_dy();

    nge::Sint32 get_dx();
    nge::Sint32 get_dy();

    nge::video::D2::entity::Basic *get_graphic_entity();
    nge::collision::D2::BoundingBox *get_collision_entity();

  private:

    nge::Sint32 _dx, _dy;

    nge::video::D2::entity::Basic *_graphic_entity; // a rectangle drawn by opengl
    nge::collision::D2::BoundingBox  *_collision_entity; // the description of our form
};

#endif

