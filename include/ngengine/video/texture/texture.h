#ifndef NATIV_GAMES_ENGINE_VIDEO_TEXTURE_TEXTURE_H
#define NATIV_GAMES_ENGINE_VIDEO_TEXTURE_TEXTURE_H

#include <ngengine/video/texture/pixelbuffer.h>
#include <ngengine/video/opengl/opengl.h>
#include <vector>

namespace nge {
  namespace texture {

  class Texture {
    public:

      Texture();
      ~Texture();

      void setPixelBuffer(PixelBuffer *pxBuf); // appelle updateInGC
      void updateInGC();

      void bind(); // bindTexture for OpenGL

      PixelBuffer *getPxBuf() const;

    private:

      GLuint _texid;

      PixelBuffer *_pxBuf;
  
      Uint32 _width, _height;
      Uint32 _rw, _rh; // real width and real height
      Uint8 _nbpp; // nb bytes per pixel: 3 (RGB) or 4 (RGBA)
  };

  }
}

#endif
