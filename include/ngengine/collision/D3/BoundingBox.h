#ifndef NATIV_GAMES_ENGINE_COLLISION_D3_BOUNDINGBOX_H
#define NATIV_GAMES_ENGINE_COLLISION_D3_BOUNDINGBOX_H

#include <ngengine/collision/D3/AbstractDescriptor.h>
#include <ngengine/video/video.h>
#include <ngengine/utils/types.h>

namespace nge {
  namespace collision {
    namespace D3 {

  class BoundingBox : public AbstractDescriptor {
    public:

      BoundingBox();
      virtual ~BoundingBox();

      bool collisionWithOffset(
        AbstractDescriptor *ad, 
        glm::vec3 offsetSelf, 
        glm::vec3 offsetAd
      );

      bool collisionWithoutCallOtherCollisionWithOffset(
        AbstractDescriptor *ad,
        glm::vec3 offsetSelf,
        glm::vec3 offsetAd
      );

      void set(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
      glm::vec3 *getPoints();
      glm::vec2 *getMap();

    protected:

      glm::vec3 _points[8];
      glm::vec2 _map[3]; // xmin xmax ymin ymax zmin zmax
      /*
        _points[0] = xmin ymin zmin
        _points[1] = xmax ymin zmin
        _points[2] = xmin xmin zmin
        _points[3] = xmax xmax zmin
        _points[4] = xmin ymin zmax
        _points[5] = xmax ymin zmax
        _points[6] = xmin xmin zmax
        _points[7] = xmax xmax zmax
        
      */
  };

  class BoundingBoxEntity : public nge::video::D3::entity::Basic {
    public:
      BoundingBoxEntity(BoundingBox *bb);
      ~BoundingBoxEntity();

      void update();

    private:

      BoundingBox *_bb;
      double _vertices[72];
      nge::Uint8 _colors[96];
  };

    }
  }
}

#endif
