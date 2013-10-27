#include <ngengine/video/texture/pixelbuffer.h>
#include <stdlib.h>

using namespace nge;
using namespace nge::texture;

PixelBuffer::PixelBuffer(Uint8 nbpp, Uint32 width, Uint32 height)
{
  _nbpp = nbpp;
  _width = width;
  _height = height;

  _rw = 2;

  while(_rw < _width)
    _rw *= 2;

  _rh = 2;

  while(_rh < _height)
    _rh *= 2;

  _content = (Uint8 *) malloc(nbpp * _rw * _rh);
}

PixelBuffer::~PixelBuffer()
{
  free(_content);
}

//void setPixel
//void fill
//void blit
Uint8 *PixelBuffer::getPixelAddr(Uint32 x, Uint32 y)
{
  bool ok = 0;
	Uint32 nb = 0;

  if((x >= _width) || (y >= _height))
    return nullptr;
  else;

	nb = (_rw * _rh);
	nb -= ((y + 1) * _rw);
	nb += x;
	nb *= _nbpp;

	return &_content[nb];
}

Uint8 *PixelBuffer::getContent() const
{
  return _content;
}


Uint8 PixelBuffer::getNbBytesPerPixel() const
{
  return _nbpp;
}

Uint32 PixelBuffer::getWidth()
{
  return _width;
}

Uint32 PixelBuffer::getHeight()
{
  return _height;
}

Uint32 PixelBuffer::getRealWidth()
{
  return _rw;
}

Uint32 PixelBuffer::getRealHeight()
{
  return _rh;
}

