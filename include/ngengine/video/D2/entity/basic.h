#ifndef NATIV_GAMES_ENGINE_VIDEO_D2_ENTITY_BASIC_H
#define NATIV_GAMES_ENGINE_VIDEO_D2_ENTITY_BASIC_H

#include <ngengine/video/D2/entity/entity.h>
#include <ngengine/video/opengl/opengl.h>
#include <ngengine/video/texture/texture.h>

namespace nge {
  namespace video {
    namespace D2 {
      namespace entity {

  class Basic : public Entity {
    public:

      // nb Vertices per form
      Basic(Uint32 nbVertices, Uint32 nbForms, GLenum renderType);
      virtual ~Basic();

      void setVertexBuf(Sint32 *p, bool toFree);  // (x, y) couples
      void setColorBuf(Uint8 *p, bool toFree); // rgba colors
      void setTexCoords(double *p, bool toFree);    // (x, y) couples
      void setTexture(texture::Texture *tex, bool toFree);

      Sint32 *getVerticesBuf();
      Uint8  *getColorsBuf();
      double *getTexCoords();
      texture::Texture *getTexture();

      void drawAtPosition(Sint32 x, Sint32 y);

      Uint8 _alpha;

    private:

      Sint32 *_verticesBuf;
      Uint8  *_colorsBuf;
      double *_texCoords;
      texture::Texture *_tex;

      bool _freeVertices;
      bool _freeColors;
      bool _freeTexCoords;
      bool _freeTex;

      Uint32 _nbVertices; // nb Vertices per form
      Uint32 _nbForms;
      GLenum _renderType;
  };

      }
    }
  }
}

#endif
