#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/NGE_SDL.h>
#include <iostream>
#include <ngengine/ngengine.h>
#include <10_Breakout_like/controllers/game.h>

nge::video::shader::Shader *shader_color;
nge::video::shader::Shader *shader_tex;

int main(int argc, char **argv)
{	
  // The window
	
  SDL_Window* fenetre(0);
  SDL_GLContext contexteOpenGL(0);
		
  // SDL Initialisation
	
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_HAPTIC) < 0)
  {
    std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
    SDL_Quit();
		
    return -1;
  }

  IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	
  // Setting OpenGL Version for the context
	
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	
	
  // Double Buffer
	
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	//SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	
  // Création de la fenêtre

  fenetre = SDL_CreateWindow(
    "NGEngine - 10 - Breakout-like", 
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

  shader_color = new nge::video::shader::Shader();
  shader_tex = new nge::video::shader::Shader();

  if(!shader_color->load_files("Shaders/vertex2color4.vert", "Shaders/vertex2color4.frag"))
    printf("Shader vertex2color4 not found\n");
  if(!shader_tex->load_files("Shaders/vertex2color4tex2.vert", "Shaders/vertex2color4tex2.frag"))
    printf("Shader vertex2color4tex2 not found\n");
  shader_color->compile();
  shader_tex->compile();

  glClearColor(0., 0., 0., 1.);

  GameController *game = new GameController(fenetre);
  
  game->start();

  delete game;
  delete shader_tex;
  delete shader_color;

  SDL_GL_DeleteContext(contexteOpenGL);
  SDL_DestroyWindow(fenetre);
  SDL_Quit();

  return 0;
}

