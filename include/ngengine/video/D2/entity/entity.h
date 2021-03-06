#ifndef NATIV_GAMES_ENGINE_VIDEO_D2_ENTITY_ENTITY_H
#define NATIV_GAMES_ENGINE_VIDEO_D2_ENTITY_ENTITY_H

#include <ngengine/utils/types.h>
#include <ngengine/video/shader/shader.h>

namespace nge {
  namespace video {
    namespace D2 {

  class Entity {
    public:

      virtual ~Entity();

      virtual void drawAtPosition(Sint32 x, Sint32 y) = 0; // A coder

      void draw(); // A la pos courante
      void drawWithOffset(Sint32 x, Sint32 y);

      glm::vec2 *getPosition();
      double *getAngle();

      shader::Shader *_shader;

    protected:
      glm::vec2 _pos;
      double _angle;
  };

    }
  }
}

#endif
