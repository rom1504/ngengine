#include <ngengine/video/D2/entity/basic.h>
#include <stdlib.h>

using namespace nge;
using namespace nge::entity;

Basic::Basic(Uint32 nbVertices, Uint32 nbForms, GLenum renderType)
{
  _verticesBuf = nullptr;
  _colorsBuf = nullptr;
  _texCoords = nullptr;
  _tex = nullptr;

  _freeVertices = 0;
  _freeColors = 0;
  _freeTexCoords = 0;
  _freeTex = 0;

  _nbVertices = nbVertices;
  _nbForms = nbForms;
  _renderType = renderType;

  _alpha = 255;
}

Basic::~Basic()
{
  if(_freeVertices)
    free(_verticesBuf);
  else;

  if(_freeColors)
    free(_colorsBuf);
  else;

  if(_freeTexCoords)
    free(_texCoords);
  else;

  if(_freeTex)
    delete _tex;
  else;
}

void Basic::setVertexBuf(Sint32 *p, bool toFree)
{
  _verticesBuf = p;
  _freeVertices = toFree;
}

void Basic::setColorBuf(Uint8 *p, bool toFree)
{
  _colorsBuf = p;
  _freeColors = toFree;
}

void Basic::setTexCoords(double *p, bool toFree)
{
  _texCoords = p;
  _freeTexCoords = toFree;
}

void Basic::setTexture(texture::Texture *tex, bool toFree)
{
  _tex = tex;
  _freeTex = toFree;
}

void Basic::drawAtPosition(Sint32 x, Sint32 y)
{
  Uint32 i, j, k, l;
  Uint32 alpha;

  if(_tex && _texCoords) {

    if(!glIsEnabled(GL_TEXTURE_2D))
      glEnable(GL_TEXTURE_2D);
    else;

    _tex->bind();
  }
  else {
    if(glIsEnabled(GL_TEXTURE_2D))
      glDisable(GL_TEXTURE_2D);
    else;
  }

  glBegin(_renderType);

#define setGLColor() alpha = _colorsBuf[l + 3]; \
                     alpha *= _alpha; \
                     alpha /= 255; \
                     glColor4ub(_colorsBuf[l], \
                                _colorsBuf[l + 1],\
                                _colorsBuf[l + 2], \
                                (Uint8) alpha);
  k = 0; // k va de 2 en 2
  l = 0; // l va de 4 en 4

  for(i = 0; i < _nbForms; i++) {
    for(j = 0; j < _nbVertices; j++) {
      
      if(_texCoords && _tex) {
        glTexCoord2d(_texCoords[k], 
                     _texCoords[k + 1]);
      }

      setGLColor();

      glVertex2i(_verticesBuf[k] + x, 
                 _verticesBuf[k + 1] + y);

      k += 2;
      l += 4;
    }
  }

  glEnd();
}

