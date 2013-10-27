#include <SDL/SDL.h>
#include <ngengine/ngengine.h>
#include "NGE_SDL.h"
#include <05_3D/FreeFly.h>

nge::video::D3::entity::Basic *create3DEntity()
{
  nge::video::D3::entity::Basic *entity;
  static double vertices[] = {
     1,  1,  1,
     1,  1, -1,
    -1,  1, -1,
    -1,  1,  1,

    1, -1, 1,
    1,-1,-1,
    1,1,-1,
    1,1,1,
    
    -10., -10, -1., 
    -10., 10., -1.,
    10., 10., -1.,
    10., -10., -1. 
  };

  static Uint8 colors[] = {
    255, 0, 0, 255,
    255, 0, 0, 255,
    255, 0, 0, 255,
    255, 0, 0, 255,

    0, 255, 0, 255,
    0, 255, 0, 255,
    0, 255, 0, 255,
    0, 255, 0, 255,

    0, 0, 255, 255,
    0, 0, 255, 255,
    0, 0, 255, 255,
    0, 0, 255, 255
    
  };
  
  entity = new nge::video::D3::entity::Basic(4, 3, GL_QUADS);

  entity->setVertexBuf(vertices, false);  // (x, y) couples
  entity->setColorBuf(colors, false);

  return entity;
}

int main(int argc, char **argv)
{
  nge::video::D3::entity::Basic *entity;
  FreeFly *cam;
  nge::event::Event event;
  SDL_Init(SDL_INIT_VIDEO);

	SDL_SetVideoMode(800, 600, 32, SDL_OPENGL | SDL_DOUBLEBUF);

	SDL_WM_SetCaption("NGEngine - 05_3D", NULL);
  
  NGE_SDL_Event_Init(&event);

  glewInit();

  glClearColor(0.3, 0.3, 0.5, 1.);

  // Création de la subscene

  /*Sint32 vertices[] = {
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
  };*/

  SDL_ShowCursor(0);
  SDL_WM_GrabInput(SDL_GRAB_ON);

  nge::scene::SubScene *subscene = new nge::scene::SubScene(600, 800, 600, 0, 0);
  
  cam = new FreeFly(); 
  subscene->setCamera3D(cam);
  cam->setAspect(800., 600.);

  nge::texture::Texture *tex1 = NGE_SDL_Texture_Load("nge.png");
  nge::texture::Texture *tex2 = NGE_SDL_Texture_Load("nge_transp.png");
  
  nge::entity::Basic e1(4, 1, GL_QUADS);

  /*e1.setVertexBuf(vertices, false);  // (x, y) couples
  e1.setColorBuf(colors, false);
  e1.setTexture(tex1, false);
  e1.setTexCoords(texCoords, false);*/
 
  entity = create3DEntity();

  /*subscene->add(&e1);*/
  subscene->add(entity);

  nge::scene::Scene scene;

  // Each subscene will be deleted by the scene destructor,
  // so we have to use SubScene * and not SubScene
  scene.add(subscene);

  int done = 0;

  while(!done) {

    while(NGE_SDL_Event_Get(&event)) {
      switch(event.type) {
        case EC_Event_Window:
          if(event.change.keyboard.id == EC_EW_Close)
            done = 1;
          break;
        case EC_Event_Mouse:
          if(event.change.mouse.id == EC_EventMouse_Move) {
            cam->rotateNormal(-0.005 * event.change.mouse.dx);
            cam->rotateLeft(-0.005 * event.change.mouse.dy);
          }
          break;
        default:
          break;
      }
    }

    if(event.map.keyboard.key[EC_EKM_Escape])
      done = 1;
    
    if(event.map.keyboard.key[EC_EKM_ArrowLeft])
      cam->left(-0.1);
    if(event.map.keyboard.key[EC_EKM_ArrowRight])
      cam->left(0.1);
    if(event.map.keyboard.key[EC_EKM_ArrowUp])
      cam->forward(0.1);
    if(event.map.keyboard.key[EC_EKM_ArrowDown])
      cam->forward(-0.1);
    if(event.map.keyboard.key[EC_EKM_q])
      cam->rotateNormal(0.05);
    if(event.map.keyboard.key[EC_EKM_d])
      cam->rotateNormal(-0.05);
    if(event.map.keyboard.key[EC_EKM_z])
      cam->rotateLeft(0.05);
    if(event.map.keyboard.key[EC_EKM_s])
      cam->rotateLeft(-0.05);

    scene.draw();

    glFlush();
    SDL_GL_SwapBuffers();
  }

  delete tex1;
  delete tex2;

  SDL_WM_GrabInput( SDL_GRAB_OFF );

  SDL_Quit();

  return 0;
}

