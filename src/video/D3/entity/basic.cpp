#include <ngengine/video/D3/entity/basic.h>
#include <stdlib.h>

using namespace nge;
using namespace nge::video;
using namespace nge::video::D3;
using namespace nge::video::D3::entity;

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

void Basic::setVertexBuf(double *p, bool toFree)
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

void Basic::drawAtPosition(glm::vec3 pos)
{
  Uint32 i, j, k, l;
  Uint32 alpha;

  glPushMatrix();
  glTranslated(pos[0], pos[1], pos[2]);
  glRotated(_rotation[0], _rotation[1], _rotation[2], _rotation[3]);

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

  

#define setGLColor() alpha = _colorsBuf[l + 3]; \
                     alpha *= _alpha; \
                     alpha /= 255; \
                     glColor4ub(_colorsBuf[l], \
                                _colorsBuf[l + 1],\
                                _colorsBuf[l + 2], \
                                (Uint8) alpha);
  k = 0; // k va de 3 en 3
  l = 0; // l va de 4 en 4
  int z = 0; // z va de de 2 en 2

  for(i = 0; i < _nbForms; i++) {
    glBegin(_renderType);
    for(j = 0; j < _nbVertices; j++) {
      
      if(_texCoords && _tex) {
        glTexCoord2d(_texCoords[z], 
                     _texCoords[z + 1]);
      }

      setGLColor();

      glVertex3d(_verticesBuf[k], 
                 _verticesBuf[k + 1],
                 _verticesBuf[k + 2]);

      z += 2;
      k += 3;
      l += 4;
    }
    glEnd();
  }

  glPopMatrix();
}


double *Basic::getVertices()
{
  return _verticesBuf;
}

Uint8 *Basic::getColors()
{
  return _colorsBuf;
}

