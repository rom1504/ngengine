#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/NGE_SDL.h>
#include <iostream>
#include <ngengine/ngengine.h>

int main(int argc, char **argv)
{	
  // Notre fenêtre
	
  SDL_Window* fenetre(0);
  SDL_GLContext contexteOpenGL(0);
	
  SDL_Event event;
  bool done(false);
	
	
  // Initialisation de la SDL
	
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_HAPTIC) < 0)
  {
    std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
    SDL_Quit();
		
    return -1;
  }

  IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	
	
  // Version d'OpenGL
	
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	
	
  // Double Buffer
	
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	
  // Création de la fenêtre

  fenetre = SDL_CreateWindow(
    "NGEngine - 01Basic", 
    SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED, 
    800, 600, 
    SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
  );

  if(fenetre == 0) {
    std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
    SDL_Quit();

    return -1;
  }


  // Création du contexte OpenGL

  contexteOpenGL = SDL_GL_CreateContext(fenetre);

  if(contexteOpenGL == 0)
  {
    std::cout << SDL_GetError() << std::endl;
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return -1;
  }

  // On initialise GLEW
  GLenum initialisationGLEW( glewInit() );

  // Si l'initialisation a échouée :
  if(initialisationGLEW != GLEW_OK)
  {
    // On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)

    std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;


    // On quitte la SDL

    SDL_GL_DeleteContext(contexteOpenGL);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return -1;
  }

  glClearColor(0.3, 0.3, 0.5, 1.);

  // Vertices et coordonnées

//  float vertices[] = {-0.5, -0.5,   0.0, 0.5,   0.5, -0.5};

  // Création de la subscene

  nge::scene::Scene scene;
  nge::scene::SubScene *subscene = new nge::scene::SubScene(600, 800, 600, 0, 0);

  scene.add(subscene);

  Sint32 vertices[] = {
    0, 0,
    160, 0,
    0, 160,
    160, 160,
  };

  Uint8 colors[] = {
    255, 0, 0, 255, 
    0, 255, 255, 255,
    0, 255, 0, 255,
    0, 0, 255, 255
  };

  double texcoords[] {
    0., 0.,
    1., 0.,
    0., 1.,
    1., 1.
  };

  nge::texture::Texture *tex = NGE_SDL_Texture_Load("nge.png");
  nge::video::D2::entity::Basic 
    e1(4, 1, GL_TRIANGLE_STRIP), 
    e2(4, 1, GL_TRIANGLE_STRIP), 
    e3(4, 1, GL_TRIANGLE_STRIP), 
    e4(4, 1, GL_TRIANGLE_STRIP);

  nge::video::shader::Shader *shaders[3];

  shaders[0] = new nge::video::shader::Shader();
  if(!shaders[0]->load_files("Shaders/vertex2.vert", "Shaders/vertex2.frag"))
    printf("fichiers des shaders non trouvés.\n");

  shaders[1] = new nge::video::shader::Shader();
  if(!shaders[1]->load_files("Shaders/vertex2color4.vert", "Shaders/vertex2color4.frag"))
    printf("fichiers des shaders non trouvés.\n");

  shaders[2] = new nge::video::shader::Shader();
  if(!shaders[2]->load_files("Shaders/vertex2color4tex2.vert", "Shaders/vertex2color4tex2.frag"))
    printf("fichiers des shaders non trouvés.\n");

  if(!shaders[0]->compile())
    printf("shaders not compiled\n");
  else 
    printf("shaders compiled\n");

  if(!shaders[1]->compile())
    printf("shaders not compiled\n");
  else 
    printf("shaders compiled\n");

  if(!shaders[2]->compile())
    printf("shaders not compiled\n");
  else 
    printf("shaders compiled\n");

  shaders[0]->set_matrix(&subscene->_projection, &subscene->_modelview);
  shaders[1]->set_matrix(&subscene->_projection, &subscene->_modelview);
  shaders[2]->set_matrix(&subscene->_projection, &subscene->_modelview);

  e1.setVertexBuf(vertices, false);  // (x, y) couples
  e1._shader = shaders[0];

  e2.setVertexBuf(vertices, false);  // (x, y) couples
  e2.setColorBuf(colors, false);
  e2._shader = shaders[1];
  *(e2.getPosition()) = glm::vec2(165, 0);

  e3.setVertexBuf(vertices, false);  // (x, y) couples
  e3.setColorBuf(colors, false);
  e3.setTexCoords(texcoords, false);
  e3.setTexture(tex, true); // free the texture
  e3._shader = shaders[2];
  *(e3.getPosition()) = glm::vec2(330, 0);

  e4.setVertexBuf(vertices, false);  // (x, y) couples
  e4.setColorBuf(colors, false);
  e4.setTexCoords(texcoords, false);
  e4.setTexture(tex, false); // don't free the texture
  e4._shader = shaders[2];
  *(e4.getPosition()) = glm::vec2(0, 170);

  subscene->add(&e1);
  subscene->add(&e2);
  subscene->add(&e3);
  subscene->add(&e4);

  char down;
  
  nge::video::D2::Camera *cam;
  cam = subscene->getCamera2D();

  bool t[6] = {0};

  // Boucle principale
  while(!done)
  {
    while(SDL_PollEvent(&event)) {

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

#define NB 5

    if(t[0])
      cam->moveX(-NB);
    else;

    if(t[1])
      cam->moveX(NB);
    else;

    if(t[2])
      cam->moveY(-NB);
    else;

    if(t[3])
      cam->moveY(NB);
    else;

#undef NB

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

    // on met à jour
    if(e4._alpha == 255)
      down = -5;
    else if(e4._alpha == 0)
      down = 5;
    
    e4._alpha += down;
    // Nettoyage de l'écran

    glClear(GL_COLOR_BUFFER_BIT);
    subscene->draw();

    // Actualisation de la fenêtre

    SDL_GL_SwapWindow(fenetre);

    SDL_Delay(10);
  }


  // On quitte la SDL

  delete shaders[0];
  delete shaders[1];
  delete shaders[2];

  SDL_GL_DeleteContext(contexteOpenGL);
  SDL_DestroyWindow(fenetre);
  SDL_Quit();

  return 0;
}


