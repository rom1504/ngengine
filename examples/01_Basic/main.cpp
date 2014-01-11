#include <SDL2/SDL.h>
#include <iostream>
#include <ngengine/ngengine.h>

int main(int argc, char **argv)
{	
  // Notre fenêtre
	
  SDL_Window* fenetre(0);
  SDL_GLContext contexteOpenGL(0);
	
  SDL_Event evenements;
  bool terminer(false);
	
	
  // Initialisation de la SDL
	
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
  std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
  SDL_Quit();
		
  return -1;
  }
	
	
  // Version d'OpenGL
	
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	
	
  // Double Buffer
	
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	
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

  nge::scene::SubScene subscene(600, 800, 600, 0, 0);

  Sint32 vertices[] = {
    0, 0,
    160, 160,
    160, 0
  };

  Uint8 colors[] = {
    255, 0, 0, 255, 
    0, 255, 0, 255,
    0, 0, 255, 255
  };

  nge::video::D2::entity::Basic e1(3, 1, GL_TRIANGLES), e2(3, 1, GL_TRIANGLES);

  nge::video::shader::Shader *shaders[3];

  shaders[0] = new nge::video::shader::Shader();
  if(!shaders[0]->load_files("Shaders/vertex2.vert", "Shaders/vertex2.frag"))
    printf("fichiers des shaders non trouvés.\n");

  shaders[1] = new nge::video::shader::Shader();
  if(!shaders[1]->load_files("Shaders/vertex2color4.vert", "Shaders/vertex2color4.frag"))
    printf("fichiers des shaders non trouvés.\n");

/*  shaders[2] = new nge::video::shader::Shader();
  shader->load_files("Shaders/vertex2.vert", "Shaders/vertex2.frag");*/

  if(!shaders[0]->compile())
    printf("shaders not compiled\n");
  else 
    printf("shaders compiled\n");

  if(!shaders[1]->compile())
    printf("shaders not compiled\n");
  else 
    printf("shaders compiled\n");

  shaders[0]->set_matrix(&subscene._projection, &subscene._modelview);
  shaders[1]->set_matrix(&subscene._projection, &subscene._modelview);
//shaders[2]->set_matrix(&subscene._projection, &subscene._modelview);

  e1.setVertexBuf(vertices, false);  // (x, y) couples
  e1._shader = shaders[0];

  e2.setVertexBuf(vertices, false);  // (x, y) couples
  e2.setColorBuf(colors, false);
  e2._shader = shaders[1];
  *(e2.getPosition()) = glm::vec2(165, 1);

  subscene.add(&e1);
  subscene.add(&e2);

  // Boucle principale

  while(!terminer)
  {
    // Gestion des évènements

    SDL_WaitEvent(&evenements);

    if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
      terminer = true;


    // Nettoyage de l'écran

    glClear(GL_COLOR_BUFFER_BIT);
    subscene.draw();

    // Actualisation de la fenêtre

    SDL_GL_SwapWindow(fenetre);
  }


  // On quitte la SDL

  delete shaders[0];
  delete shaders[1];

  SDL_GL_DeleteContext(contexteOpenGL);
  SDL_DestroyWindow(fenetre);
  SDL_Quit();

  return 0;
}
/*
int main(int argc, char **argv)
{
  SDL_Init(SDL_INIT_VIDEO);
	SDL_SetVideoMode(800, 600, 32, SDL_OPENGL | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("NGEngine - 01Basic", NULL);

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

  nge::scene::SubScene subscene(600, 800, 600, 0, 0);
  nge::video::D2::entity::Basic e1(3, 1, GL_TRIANGLES);

  e1.setVertexBuf(vertices, false);  // (x, y) couples
  e1.setColorBuf(colors, false); 

  subscene.add(&e1);

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

  glClear(GL_COLOR_BUFFER_BIT);

  subscene.draw();

  glFlush();
  SDL_GL_SwapBuffers();
  }


  SDL_Quit();

  return 0;
}*/

