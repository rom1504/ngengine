#include <ngengine/video/D2/entity/basic.h>
#include <stdlib.h>

using namespace nge;
using namespace nge::video;
using namespace nge::video::D2;
using namespace nge::video::D2::entity;

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

Sint32 *Basic::getVerticesBuf()
{
  return _verticesBuf;
}

Uint8 *Basic::getColorsBuf()
{
  return _colorsBuf;
}
    
double *Basic::getTexCoords()
{
  return _texCoords;
}

texture::Texture *Basic::getTexture()
{
  return _tex;
}

void Basic::drawAtPosition(Sint32 x, Sint32 y)
{
  Uint32 i, j, k, l;
  Uint32 alpha;

  if(_shader) {
    glUseProgram(_shader->get_id());
  }
  else;

  if(_tex) {

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

  //glPushMatrix();

  //glTranslated((double) x, (double) y, 0.);
  //glRotated(_angle, 0., 0., 1.);

  // push modelview
  glm::mat4 modelview = *(_shader->_modelview);

  // translation
  *(_shader->_modelview) = glm::translate(*(_shader->_modelview), glm::vec3((float) x, (float) y, 0.f));
  // rotation
  *(_shader->_modelview) = glm::rotate(*(_shader->_modelview), (float) _angle, glm::vec3(0.f, 0.f, 1.f));

  glVertexAttribPointer(0, 2, GL_INT, GL_FALSE, 0, _verticesBuf);
  glEnableVertexAttribArray(0);

  if(_colorsBuf) {
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, _colorsBuf);
    glEnableVertexAttribArray(1);
  }

  if(_tex) {
    glVertexAttribPointer(2, 2, GL_DOUBLE, GL_FALSE, 0, _texCoords);
    glEnableVertexAttribArray(2);
  }

  if(_shader) {
    _shader->update_matrix();
  }
  else;

  glEnable(GL_BLEND);
  glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
  glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

  glDrawArrays(_renderType, 0, _nbVertices * _nbForms);
  glDisableVertexAttribArray(0);

  if(_colorsBuf) {
    glDisableVertexAttribArray(1);
  }

  if(_tex) {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableVertexAttribArray(2);
  }

  if(_shader) {
    glUseProgram(0);
  }
  else;

  // pop modelview
  *(_shader->_modelview) = modelview;
}

