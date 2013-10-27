#include <SDL/SDL.h>
#include <ngengine/ngengine.h>

void create_window();
void init_subscene(nge::scene::SubScene &subscene);
void mainloop(nge::scene::SubScene *subscene);

int main(int argc, char **argv)
{
  // initialization of the application
  create_window();

  // set window refresh color
  glClearColor(0.3, 0.3, 0.5, 1.);

  // create subscene
  nge::scene::SubScene subscene(600, 800, 600, 0, 0);

  init_subscene(&subscene);

  mainloop();

  SDL_Quit();

  return 0;
}

void create_window()
{
  // initialize the window with an OpenGL context
  SDL_Init(SDL_INIT_VIDEO);
	SDL_SetVideoMode(800, 600, 32, SDL_OPENGL | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("NGEngine - 02Scene", NULL);

  // initialize OpenGL extensions
  glewInit();
}

void init_subscene(nge::scene::SubScene &subscene)
{
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
  
  nge::entity::Basic e1(3, 1, GL_TRIANGLES);

  e1.setVertexBuf(vertices, false);  // (x, y) couples
  e1.setColorBuf(colors, false); 

  subscene.add(&e1);
}

void mainloop(nge::scene::SubScene *subscene)
{
  SDL_Event event;
  int done = 0;

  while(!done) {

    // Events treatment
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

    // Display the subscene

    subscene.draw();

    glFlush();
    SDL_GL_SwapBuffers();
  }
}

