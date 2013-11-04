#ifndef NATIV_GAMES_ENGINE_COLLISION_D2_BOUNDINGBOX_H
#define NATIV_GAMES_ENGINE_COLLISION_D2_BOUNDINGBOX_H

#include <ngengine/collision/D2/AbstractDescriptor.h>
#include <ngengine/video/video.h>
#include <ngengine/utils/types.h>

namespace nge {
  namespace collision {
    namespace D2 {

  class BoundingBox : public AbstractDescriptor {
    public:

      BoundingBox();
      virtual ~BoundingBox();

      bool collisionWithOffset(
        AbstractDescriptor *ad, 
        glm::vec2 offsetSelf, 
        glm::vec2 offsetAd
      );

      bool collisionWithoutCallOtherCollisionWithOffset(
        AbstractDescriptor *ad,
        glm::vec2 offsetSelf,
        glm::vec2 offsetAd
      );

      void set(Sint32 xmin, Sint32 xmax, Sint32 ymin, Sint32 ymax);
      Sint32 *getPoints();
      Sint32 *getMap();

    protected:

      Sint32 _points[8]; // x y x y x y x y
      Sint32 _map[4]; // xmin xmax ymin ymax
      /*
        _points[0] = xmin ymin
        _points[1] = xmax ymin
        _points[2] = xmax ymax
        _points[3] = xmin ymax
        
      */
  };

  class BoundingBoxEntity : public nge::video::D2::entity::Basic {
    public:
      BoundingBoxEntity(BoundingBox *bb);
      ~BoundingBoxEntity();

      void update();

    private:

      BoundingBox *_bb;
      Sint32 _vertices[8]; // 4 * 2
      nge::Uint8 _colors[16]; // 4 * 4
  };

    }
  }
}

#endif
