#ifndef NATIV_GAMES_ENGINE_VIDEO_TEXTURE_PIXELBUFFER_H
#define NATIV_GAMES_ENGINE_VIDEO_TEXTURE_PIXELBUFFER_H

#include <ngengine/utils/types.h>
#include <vector>

namespace nge {
  namespace texture {

  class PixelBuffer {
    public:

      PixelBuffer(Uint8 nbpp, Uint32 width, Uint32 height);
      ~PixelBuffer();
      
      //void setPixel
      //void fill
      //void blit
      Uint8 *getPixelAddr(Uint32 x, Uint32 y);
        
      Uint8 *getContent() const;
      Uint8 getNbBytesPerPixel() const;

      Uint32 getWidth();
      Uint32 getHeight();
      Uint32 getRealWidth();
      Uint32 getRealHeight();

    private:
  
      Uint8 *_content;
      Uint32 _width, _height;
      Uint32 _rw, _rh; // real width and real height
      Uint8 _nbpp; // nb bytes per pixel: 3 (RGB) or 4 (RGBA)
  };

  }
}

#endif
