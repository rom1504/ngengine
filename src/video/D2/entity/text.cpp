#include <ngengine/video/D2/entity/text.h>
#include <string.h>

using namespace nge::video::D2::entity::text;

Text::Text()
{

}

Text::~Text()
{

}

void Text::drawAtPosition(Sint32 x, Sint32 y)
{
  TextCharacter *c;
  uint32_t nb, i;

  glPushMatrix();
  glTranslated((double) x, (double) y, 0.);

  glEnable(GL_TEXTURE_2D);

  nb = _chars.size();
  for(i = 0; i < nb; i++) {
    c = _chars[i];

    c->tex->bind();

    glBegin(GL_QUADS);
    
    glColor4ub(c->r, c->g, c->b, c->a);

    glTexCoord2f(c->texcoords[0], c->texcoords[1]);
    glVertex2f(c->vertices[0], c->vertices[1]);//glVertex2f(c->x, c->y);
    glTexCoord2f(c->texcoords[2], c->texcoords[3]);
    glVertex2f(c->vertices[2], c->vertices[3]);//glVertex2f(c->x + c->w, c->y);
    glTexCoord2f(c->texcoords[4], c->texcoords[5]);
    glVertex2f(c->vertices[4], c->vertices[5]);//glVertex2f(c->x + c->w, c->y + c->h);
    glTexCoord2f(c->texcoords[6], c->texcoords[7]);
    glVertex2f(c->vertices[6], c->vertices[7]);//glVertex2f(c->x, c->y + c->h);

    glEnd();
  }

  glPopMatrix();
}
#include <stdio.h>
Font::Font(const char *filename, size_t i)
{
  _atlas = texture_atlas_new(512, 512, 1);
  _font = texture_font_new_from_file(_atlas, i, filename);
  _atlas_tex = new nge::texture::Texture(_atlas->id);
  printf("atlas id: %d\n", _atlas->id);
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

      int x0  = (int)( _x + glyph->offset_x );
      int y0  = (int)( _y - glyph->offset_y );
      int x1  = (int)( x0 + glyph->width );
      int y1  = (int)( y0 + glyph->height );
      float s0 = glyph->s0;
      float t0 = glyph->t0;
      float s1 = glyph->s1;
      float t1 = glyph->t1;

      font->_atlas_tex->set_id(font->_atlas->id);
      //printf("atlas id: %d\n", font->_atlas->id);

      TextCharacter *tc = new TextCharacter;
      tc->tex = font->_atlas_tex;
      //tc->x = x0;
      //tc->y = y0 - ((float) glyph->height) + ((float)glyph->offset_y);
      //tc->y = 25 + y0 - ((float) glyph->height);
      //tc->w = glyph->width;
      //tc->h = glyph->height;
      tc->texcoords[0] = s0;
      tc->texcoords[1] = t0;
      tc->texcoords[2] = s1;
      tc->texcoords[3] = t0;
      tc->texcoords[4] = s1;
      tc->texcoords[5] = t1;
      tc->texcoords[6] = s0;
      tc->texcoords[7] = t1;
      tc->vertices[0] = x0;
      tc->vertices[1] = y0;
      tc->vertices[2] = x1;
      tc->vertices[3] = y0;
      tc->vertices[4] = x1;
      tc->vertices[5] = y1;
      tc->vertices[6] = x0;
      tc->vertices[7] = y1;
      tc->r = _r;
      tc->g = _g;
      tc->b = _b;
      tc->a = _a;

      _text->_chars.push_back(tc);

      _x += glyph->advance_x;
    }
    else;
  }
}

