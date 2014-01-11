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

  // push modelview
  glm::mat4 modelview = *(_shader->_modelview);

  // translation
  *(_shader->_modelview) = glm::translate(*(_shader->_modelview), pos);
  // rotation
  *(_shader->_modelview) = glm::rotate(*(_shader->_modelview), _rotation[3], 
    glm::vec3(_rotation[0], _rotation[1], _rotation[2])
  );

  uint32_t i;

  for(i = 0; i < _nbForms; i++) {

    glVertexAttribPointer(0, 2, GL_INT, GL_FALSE, 0, _verticesBuf + 3 * i);
    glEnableVertexAttribArray(0);

    if(_colorsBuf) {
      glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, _colorsBuf + 4 * i);
      glEnableVertexAttribArray(1);
    }
  
    if(_tex) {
      glVertexAttribPointer(2, 2, GL_DOUBLE, GL_FALSE, 0, _texCoords + 2 * i);
      glEnableVertexAttribArray(2);
    }

    if(_shader) {
      _shader->update_matrix();
    }
    else;

    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    glDrawArrays(_renderType, 0, _nbVertices);
    glDisableVertexAttribArray(0);

    if(_colorsBuf) {
      glDisableVertexAttribArray(1);
    }

    if(_tex) {
      glBindTexture(GL_TEXTURE_2D, 0);
      glDisableVertexAttribArray(2);
    }
  }

  if(_shader) {
    glUseProgram(0);
  }
  else;

  if(_tex)
    glBindTexture(GL_TEXTURE_2D, 0);
  else;

  // pop modelview
  *(_shader->_modelview) = modelview;
}


double *Basic::getVertices()
{
  return _verticesBuf;
}

Uint8 *Basic::getColors()
{
  return _colorsBuf;
}

