#ifndef NATIV_GAMES_ENGINE_COLLISION_D2_ABSTRACT_DESCRIPTOR_H
#define NATIV_GAMES_ENGINE_COLLISION_D2_ABSTRACT_DESCRIPTOR_H

#include <glm/glm.hpp>
#include <ngengine/utils/types.h>

namespace nge {
  namespace collision {
    namespace D2 {

  class AbstractDescriptor {
    public:

      enum {
        Collection = 0, // contains multiple AbstractDescriptor
        BoundingBox = 1
      };

      AbstractDescriptor(Uint32 type);
      virtual ~AbstractDescriptor();

      // Collision doit appeler collisionWithoutCallOtherCollision de l'autre figure 
      // dans le cas où la classe de l'instance ne sait pas gérer la collision.
      // Si l'autre ne sait pas gérer la collision alors lever une exception. 
      bool collision(AbstractDescriptor *ad);
      bool collisionWithoutCallOtherCollision(AbstractDescriptor *ad);

      // A implémenter 
      virtual bool collisionWithOffset(
        AbstractDescriptor *ad, 
        glm::vec2 offsetSelf, 
        glm::vec2 offsetAd
      ) = 0;

      virtual bool collisionWithoutCallOtherCollisionWithOffset(
        AbstractDescriptor *ad,
        glm::vec2 offsetSelf,
        glm::vec2 offsetAd
      ) = 0;

      Uint32 getType();

    protected:

      Uint32 _type;
  };

    }
  }
}

#endif
