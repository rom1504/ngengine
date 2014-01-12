#include <ngengine/video/D2/entity/text.h>
#include <string.h>
#include <stdlib.h>

using namespace nge::video::D2::entity::text;

TextCharacter::TextCharacter(nge::video::shader::Shader *shader) : nge::video::D2::entity::Basic(4, 1, GL_TRIANGLE_STRIP)
{
  Sint32 *vertices = (Sint32 *) malloc(sizeof(Sint32) * 8);
  Uint8 *colors = (Uint8 *) malloc(sizeof(Uint8) * 16);
  double *texcoords = (double *) malloc(sizeof(double) * 8);

  this->setVertexBuf(vertices, true);  // (x, y) couples
  this->setColorBuf(colors, true);
  this->setTexCoords(texcoords, true);

  this->_shader = shader;
}

TextCharacter::~TextCharacter()
{

}

Text::Text()
{

}

Text::~Text()
{

}

void Text::drawAtPosition(Sint32 x, Sint32 y)
{
  uint32_t nb, i;

  nb = _chars.size();
  for(i = 0; i < nb; i++) {
    _chars[i]->drawWithOffset(x, y);
  }
}

Font::Font(nge::video::shader::Shader *shader, const char *filename, size_t i)
{
  _atlas = texture_atlas_new(512, 512, 1);
  _font = texture_font_new_from_file(_atlas, i, filename);
  _atlas_tex = new nge::texture::Texture(_atlas->id);
  _shader = shader;
}

Font::~Font()
{
  texture_font_delete(_font);
  texture_atlas_delete(_atlas);
  _atlas_tex->set_id(0);
  delete _atlas_tex;
}

Pen::Pen(Text *txt)
{
  _text = txt;
  _x = 0;
  _y = 0;
  _r = 255;
  _g = 255;
  _b = 255;
  _a = 255;
}

Pen::~Pen()
{
  
}

void Pen::write(char *str, Font *font)
{
  uint32_t i, len = strlen(str);

  texture_font_load_glyphs(font->_font, (wchar_t *) str);

  for(i = 0; i < len; i++) {
    texture_glyph_t *glyph = texture_font_get_glyph(font->_font, str[i]);

    if(glyph) {      
      if(i > 0)
      {
        int kerning = 0;
        kerning = texture_glyph_get_kerning( glyph, str[i-1] );
        _x += kerning;
      }
      else;

      printf("caractère '%c': %f %f %f %f\n", str[i], (double) glyph->s0, (double) glyph->s1, (double) glyph->t0, (double) glyph->t1);

      // utiliser le buffer de glyph

      int x0  = (int)( ((int)_x) + ((int)glyph->offset_x));
      int y0  = (int)( ((int)_y) - ((int)glyph->offset_y));
      int x1  = (int)( ((int)x0) + ((int)glyph->width));
      int y1  = (int)( ((int)y0) + ((int)glyph->height));
      float s0 = glyph->s0;
      float t0 = glyph->t0;
      float s1 = glyph->s1;
      float t1 = glyph->t1;

      font->_atlas_tex->set_id(font->_atlas->id);

      TextCharacter *tc = new TextCharacter(font->_shader);
      tc->setTexture(font->_atlas_tex, false);
      double *texcoords = tc->getTexCoords();
      texcoords[0] = s0;
      texcoords[1] = t0;
      texcoords[2] = s1;
      texcoords[3] = t0;
      texcoords[4] = s0;
      texcoords[5] = t1;
      texcoords[6] = s1;
      texcoords[7] = t1;
      Sint32 *vertices = tc->getVerticesBuf();
      vertices[0] = x0;
      vertices[1] = y0;
      vertices[2] = x1;
      vertices[3] = y0;
      vertices[4] = x0;
      vertices[5] = y1;
      vertices[6] = x1;
      vertices[7] = y1;
      Uint8 *colors = tc->getColorsBuf();
      for(int l = 0; l < 4; l++) { 
        colors[4 * l] = _r;
        colors[4 * l + 1] = _g;
        colors[4 * l + 2] = _b;
        colors[4 * l + 3] = _a;
      }

      printf("%c:\ntexcoords: ", str[i]);
      for(int l = 0; l < 8; l++)
        printf("%f ", texcoords[l]);
      printf("\nvertices:");
      for(int l = 0; l < 8; l++)
        printf("%d ", vertices[l]);
      printf("\n");
      _text->_chars.push_back(tc);

      _x += glyph->advance_x;
    }
    else;
  }
}

