#include <SDL/SDL.h>
#include <ngengine/ngengine.h>

int main(int argc, char **argv)
{
  SDL_Init(SDL_INIT_VIDEO);
	SDL_SetVideoMode(800, 600, 32, SDL_OPENGL | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("NGEngine - 02Scene", NULL);

  glewInit();

  glClearColor(0.3, 0.3, 0.5, 1.);

  // Création de la subscene

  Sint32 vertices[] = {
    0, 0,
    150, 150,
    150, 0
  };

  Uint8 colors[] = {
    255, 255, 255, 255,
    0, 0, 255, 255,
    255, 255, 255, 255
  };

  nge::scene::SubScene *subscene = new nge::scene::SubScene(600, 800, 600, 0, 0);
  nge::video::D2::entity::Basic e1(3, 1, GL_TRIANGLES);

  e1.setVertexBuf(vertices, false);  // (x, y) couples
  e1.setColorBuf(colors, false); 

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


  SDL_Quit();

  return 0;
}

