#ifndef NATIV_GAMES_ENGINE_VIDEO_D2_ENTITY_TEXT_H
#define NATIV_GAMES_ENGINE_VIDEO_D2_ENTITY_TEXT_H

#include <ngengine/video/D2/entity/entity.h>
#include <ngengine/video/opengl/opengl.h>
#include <ngengine/video/texture/texture.h>
#include <vector>

#include "freetype-gl.h"

namespace nge {
namespace video {
namespace D2 {
namespace entity {
namespace text {
 
  struct TextCharacter {
    nge::texture::Texture *tex;
    float texcoords[8]; // 4 * 2
    float vertices[8];
    uint8_t r, g, b, a;
  };

  class Text : public Entity {
    public:

      Text();
      ~Text();

      void drawAtPosition(Sint32 x, Sint32 y);

      std::vector<TextCharacter *> _chars;

    private:
  };

  class Font {
    public:

      Font(const char *filename, size_t i);
      ~Font();

    //private:

      texture_atlas_t *_atlas;
      nge::texture::Texture *_atlas_tex;
      texture_font_t *_font;
  };

  class Pen {
    public: 

      Pen(Text *txt);
      ~Pen();

      void write(char *str, Font *font);

//    private:
      Text *_text;
      uint32_t _x, _y;
      uint8_t _r, _g, _b, _a;
  };

}
}   
}
}
}

#endif
