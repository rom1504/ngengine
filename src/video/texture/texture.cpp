#include <ngengine/video/texture/texture.h>
#include <stdlib.h>

using namespace nge;
using namespace nge::texture;

Texture::Texture()
{
  _pxBuf = nullptr;
	glGenTextures(1, &_texid);
}

Texture::Texture(GLuint texid)
{
  _pxBuf = nullptr;
  _texid = texid;
}

Texture::~Texture()
{
  if(_texid > 0)
    glDeleteTextures(1, &_texid);
  else;
}

void Texture::setPixelBuffer(PixelBuffer *pxBuf)
{
  _pxBuf = pxBuf;
	this->updateInGC();
}

void Texture::updateInGC()
{
  if(_pxBuf) {
		_nbpp = _pxBuf->getNbBytesPerPixel();
		_width = _pxBuf->getWidth();
		_height = _pxBuf->getHeight();

		this->bind();

		glTexImage2D(GL_TEXTURE_2D,
						 0,   // mipmap
						 _nbpp,   // nb couleurs
						 _width,   // width
						 _height,   // height
						 0,   // largeur du bord
						 ((_nbpp == 3) ? GL_RGB : GL_RGBA),
						 GL_UNSIGNED_BYTE,
						 _pxBuf->getContent());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}
	else
		; // Si pxBuf == NULL, alors le buffer a été libéré pour faire de la place
		  // Mais on ne supprime pas pour autant la texture.

	return;
}

void Texture::bind()
{
  glBindTexture(GL_TEXTURE_2D, _texid);
}

PixelBuffer *Texture::getPxBuf() const
{
  return _pxBuf;
}


void Texture::set_id(GLuint texid)
{
  _texid = texid;
}

