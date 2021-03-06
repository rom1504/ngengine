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
    "NGEngine - 04 TileConverter", 
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

  double vertices[] = {
    1.0, 1.0, -0.5,
    1.0, -1.0, -0.5,
    -1.0, 1.0, -0.5,
    -1.0, -1.0, -0.5,
  };

  Uint8 colors[] = {
    255, 255, 255, 255,
    255, 255, 255, 255,
    255, 255, 255, 255,
    255, 255, 255, 255
  };

  double texcoords[] {
    0., 0.,
    1., 0.,
    0., 1.,
    1., 1.
  };

  nge::video::D3::Camera cam;
  cam.setFovy(70.);
  cam.setAspect(800., 600.);
  cam.setZNear(0.1);
  cam.setZFar(100.);
  *(cam.getPosition()) = glm::vec3(-3.f, 3.f, 3.f);
  *(cam.getTarget()) = glm::vec3(0.f, 0.f, 0.f);
  *(cam.getNormal()) = glm::vec3(0.f, 0.f, 1.f);

  nge::texture::Texture *tex = NGE_SDL_Texture_Load("tile.png");
  nge::video::D3::entity::Basic 
    e1(4, 1, GL_TRIANGLE_STRIP);

  nge::video::shader::Shader *shader;

  shader = new nge::video::shader::Shader();
  if(!shader->load_files("Shaders/vertex3color4tex2.vert", "Shaders/vertex3color4tex2.frag"))
    printf("fichiers des shaders non trouvés.\n");

  if(!shader->compile())
    printf("shaders not compiled\n");
  else 
    printf("shaders compiled\n");

  shader->set_matrix(&subscene->_projection, &subscene->_modelview);

  e1.setVertexBuf(vertices, false);  // (x, y) couples
  e1.setColorBuf(colors, false);
  e1.setTexCoords(texcoords, false);
  e1.setTexture(tex, true); // free the texture
  e1._shader = shader;

  subscene->setCamera3D(&cam);
  subscene->add(&e1);

  // Boucle principale
  while(!done)
  {
    // Gestion des évènements
    while(SDL_PollEvent(&event)) {

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

    if(event.window.event == SDL_WINDOWEVENT_CLOSE)
      done = true;

    
    // Nettoyage de l'écran
    glClear(GL_COLOR_BUFFER_BIT);
    subscene->draw();

    // Actualisation de la fenêtre
    SDL_GL_SwapWindow(fenetre);

    SDL_Delay(30);
  }


  // On quitte la SDL

  delete shader;

  SDL_GL_DeleteContext(contexteOpenGL);
  SDL_DestroyWindow(fenetre);
  SDL_Quit();

  return 0;
}

