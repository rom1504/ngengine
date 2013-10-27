#include <SDL/SDL.h>
#include <ngengine/ngengine.h>
#include "NGE_SDL.h"

int main(int argc, char **argv)
{
  SDL_Init(SDL_INIT_VIDEO);
	SDL_SetVideoMode(800, 600, 32, SDL_OPENGL | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("NGEngine - 03Texture", NULL);

  glewInit();

  glClearColor(0.3, 0.3, 0.5, 1.);

  // Création de la subscene

  Sint32 vertices[] = {
    0, 0,
    128, 0,
    128, 128,
    0, 128
  };

  Uint8 colors[] = {
    255, 255, 255, 255,
    255, 255, 255, 255,
    255, 255, 255, 255,
    255, 255, 255, 255
  };

  double texCoords[] {
    0., 1.,
    1., 1.,
    1., 0.,
    0., 0.
  };

  nge::scene::SubScene *subscene = new nge::scene::SubScene(600, 800, 600, 0, 0);

  nge::texture::Texture *tex1 = NGE_SDL_Texture_Load("nge.png");
  nge::texture::Texture *tex2 = NGE_SDL_Texture_Load("nge_transp.png");

  nge::entity::Basic e1(4, 1, GL_QUADS);

  e1.setVertexBuf(vertices, false);  // (x, y) couples
  e1.setColorBuf(colors, false);
  e1.setTexture(tex1, false);
  e1.setTexCoords(texCoords, false);

  subscene->add(&e1);

  nge::scene::Scene scene;

  // Each subscene will be deleted by the scene destructor,
  // so we have to use SubScene * and not SubScene
  scene.add(subscene);

  //

  SDL_Event event;
  int done = 0;

  while(!done) {

    if(SDL_PollEvent(&event)) {

      switch(event.type) {
        
        case SDL_QUIT:
          done = 1;
          break;

        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
            case SDLK_q:
              done = 1;
              break;
            default:
              break;
          }
          break;
        default:
          break;
      }
    }

    scene.draw();

    glFlush();
    SDL_GL_SwapBuffers();
  }

  delete tex1;
  delete tex2;

  SDL_Quit();

  return 0;
}

