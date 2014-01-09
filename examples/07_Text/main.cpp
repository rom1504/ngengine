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

  nge::scene::SubScene *subscene = new nge::scene::SubScene(600, 800, 600, 0, 0);
  nge::video::D2::entity::text::Text *e1 = new nge::video::D2::entity::text::Text;

  nge::video::D2::entity::text::Font font("fonts/Vera.ttf", 25);
  nge::video::D2::entity::text::Pen *pen = new nge::video::D2::entity::text::Pen(e1);

  pen->_y = 30;
  pen->write("A Quick Brown Fox Jumps Over The Lazy Dog 0123456789", &font);

  delete pen;

  subscene->add(e1);

  Sint32 verticeBuf[8] {
    0, 0,
    500, 0,
    500, 500,
    0, 500
  };

  Uint8 colors[] = {
    255, 255, 255, 255,
    255, 255, 255, 255,
    255, 255, 255, 255,
    255, 255, 255, 255
  };

  double texCoords[8] {
    0., 0.,
    1., 0.,
    1., 1.,
    0., 1.
  };

  nge::video::D2::entity::Basic *basic = new nge::video::D2::entity::Basic(4, 1, GL_QUADS);
  basic->setVertexBuf(verticeBuf, false);
  basic->setColorBuf(colors, false);
  basic->setTexCoords(texCoords, false);
  basic->setTexture(font._atlas_tex, false);

  subscene->add(basic);

  *(basic->getPosition()) = glm::vec2(0.f, 50.f);

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

