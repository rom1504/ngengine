#ifndef NATIV_GAMES_ENGINE_VIDEO_D3_ENTITY_ENTITY_H
#define NATIV_GAMES_ENGINE_VIDEO_D3_ENTITY_ENTITY_H

#include <ngengine/utils/types.h>
#include <glm/glm.hpp>

namespace nge {
  namespace video {
    namespace D3 {

  class Entity {
    public:

      Entity();
      virtual ~Entity();

      virtual void drawAtPosition(glm::vec3 pos) = 0; // A coder

      void draw(); // A la pos courante
      void drawWithOffset(glm::vec3 offset);

      glm::vec3 *getPosition();
      glm::vec4 *getRotation(); // angle x y z

    protected:
      glm::vec3 _pos;
      glm::vec4 _rotation; // angle et vecteur de rotation
  };
   
    }
  }
}

#endif
