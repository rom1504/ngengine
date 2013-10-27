#include <SDL/SDL.h>
#include <ngengine/ngengine.h>
#include "NGE_SDL.h"

int main(int argc, char **argv)
{
  nge::camera::Camera *cam;
  SDL_Init(SDL_INIT_VIDEO);
	SDL_SetVideoMode(800, 600, 32, SDL_OPENGL | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("NGEngine - 04Camera", NULL);

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

  cam = subscene->getCamera2D();

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

  bool t[6] = {0};

  while(!done) {

    if(SDL_PollEvent(&event)) {

      switch(event.type) {
        
        case SDL_QUIT:
          done = 1;
          break;

        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
              done = 1;
              break;
            case SDLK_LEFT:
              t[0] = 1;
              break;
            case SDLK_RIGHT:
              t[1] = 1;
              break;
            case SDLK_UP:
              t[2] = 1;
              break;
            case SDLK_DOWN:
              t[3] = 1;
              break;
            case SDLK_z:
              t[4] = 1;
              break;
            case SDLK_s:
              t[5] = 1;
              break;
            default:
              break;
          }
          break;
        case SDL_KEYUP:
          switch (event.key.keysym.sym) {
            case SDLK_LEFT:
              t[0] = 0;
              break;
            case SDLK_RIGHT:
              t[1] = 0;
              break;
            case SDLK_UP:
              t[2] = 0;
              break;
            case SDLK_DOWN:
              t[3] = 0;
              break;
            case SDLK_z:
              t[4] = 0;
              break;
            case SDLK_s:
              t[5] = 0;
              break;
            default:
              break;
          }
          break;
        default:
          break;
      }
    }

    if(t[0])
      cam->moveX(-1);
    else;

    if(t[1])
      cam->moveX(1);
    else;

    if(t[2])
      cam->moveY(-1);
    else;

    if(t[3])
      cam->moveY(1);
    else;

    if(t[4]) {
      cam->increaseWidth(- cam->getZoomXSpeed() * 2);
      cam->increaseHeight(- cam->getZoomYSpeed() * 2);
    }
    else;

    if(t[5]) {
      cam->increaseWidth(cam->getZoomXSpeed() * 2);
      cam->increaseHeight(cam->getZoomYSpeed() * 2);
    }
    else;

    //glClear(GL_COLOR_BUFFER_BIT);

    scene.draw();

    glFlush();
    SDL_GL_SwapBuffers();
  }

  delete tex1;
  delete tex2;

  SDL_Quit();

  return 0;
}

