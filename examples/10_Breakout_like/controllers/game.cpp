#include <10_Breakout_like/controllers/game.h>
#include <10_Breakout_like/shaders.h>

GameController::GameController(SDL_Window *window)
{
  _window = window;
//  _scene = new nge::scene::Scene;
  _subscene = new nge::scene::SubScene(600, 800, 600, 0, 0);

  shader_color->set_matrix(&_subscene->_projection, &_subscene->_modelview);

  // creating the player
  _player = new PlayerEntity;
  _subscene->add(_player->get_graphic_entity());

  // creating the first ball
  _player_ball = new BallEntity(390, 540, 0, 0);
  _subscene->add(_player_ball->get_graphic_entity());

  // creating the blocks
  BlockEntity *block;

  int color = 0;
  nge::Uint8 r, g, b;

  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 11; j++) {
      
      switch(color) {
        case 0:
          r = 255; g = 0; b = 0;
          break;
        case 1:
          r = 0; g = 255; b = 0;
          break;
        case 2:
          r = 0; g = 0; b = 255;
          break;
        default:
          r = 255; g = 255; b = 255;
          break;
      };

      color ++;
      color = color % 3;

      block = new BlockEntity(80 + 80 * i, 20 + 30 * j, r, g, b, 255);

      _subscene->add(block->get_graphic_entity());
      _blocks.push_back(block);
      
    }
  }
}

GameController::~GameController()
{
  for(unsigned int i = 0; i < _blocks.size(); i++)
    delete _blocks[i];

  delete _player;
  delete _subscene;
  //delete _scene;
}

void GameController::start()
{
  bool done;

  do {
    done = this->event_loop();

    // deplacements/collisions
  
    for(unsigned int i = 0; i < _balls.size(); i++) {
      if( ((*(_balls[i]->get_graphic_entity()->getPosition()))[0] + _balls[i]->get_dx()) < 0)
        _balls[i]->invert_dx();

      if( ((*(_balls[i]->get_graphic_entity()->getPosition()))[0] + _balls[i]->get_dx() + 20) > 800)
        _balls[i]->invert_dx();


      if( ((*(_balls[i]->get_graphic_entity()->getPosition()))[1] + _balls[i]->get_dy()) < 0)
        _balls[i]->invert_dy();
    }

    // 1) test with blocks
    for(unsigned int i = 0; i < _balls.size(); i++) {
      for(unsigned int j = 0; j < _blocks.size(); j++) {
        if(_balls[i]->get_collision_entity()->collisionWithOffset(
             _blocks[j]->get_collision_entity(), 
             *(_balls[i]->get_graphic_entity()->getPosition()) + 
               glm::vec2(_balls[i]->get_dx(), _balls[i]->get_dy()),
             *(_blocks[j]->get_graphic_entity()->getPosition())
           )
        ) {

          if(_balls[i]->get_collision_entity()->collisionWithOffset(
               _blocks[j]->get_collision_entity(), 
               *(_balls[i]->get_graphic_entity()->getPosition()) + 
                 glm::vec2(_balls[i]->get_dx(), 0.f),
               *(_blocks[j]->get_graphic_entity()->getPosition())
             )
          ) {
            _balls[i]->invert_dx();
          }

          if(_balls[i]->get_collision_entity()->collisionWithOffset(
               _blocks[j]->get_collision_entity(), 
               *(_balls[i]->get_graphic_entity()->getPosition()) + 
                 glm::vec2(0.f, _balls[i]->get_dy()),
               *(_blocks[j]->get_graphic_entity()->getPosition())
             )
          ) {
            _balls[i]->invert_dy();
          }

          _subscene->remove(_blocks[j]->get_graphic_entity());
          delete _blocks[j];
          _blocks.erase(_blocks.begin() + j);
        }
      }
    }

    // test with player
    for(unsigned int i = 0; i < _balls.size(); i++) {
      if(_balls[i]->get_collision_entity()->collisionWithOffset(
           _player->get_collision_entity(), 
           *(_balls[i]->get_graphic_entity()->getPosition()) + 
             glm::vec2(_balls[i]->get_dx(), _balls[i]->get_dy()),
           *(_player->get_graphic_entity()->getPosition())
         )
      ) {
/*
        if(_balls[i]->get_collision_entity()->collisionWithOffset(
             _player->get_collision_entity(), 
             *(_balls[i]->get_graphic_entity()->getPosition()) + 
               glm::vec2(_balls[i]->get_dx(), 0.f),
             *(_player->get_graphic_entity()->getPosition())
           )
        ) {
          _balls[i]->invert_dx();
        }*/

        if(_balls[i]->get_collision_entity()->collisionWithOffset(
             _player->get_collision_entity(), 
             *(_balls[i]->get_graphic_entity()->getPosition()) + 
               glm::vec2(0.f, _balls[i]->get_dy()),
             *(_player->get_graphic_entity()->getPosition())
           )
        ) {
          double angle;

          angle = acos(
            ((*(_balls[i]->get_graphic_entity()->getPosition()))[0] - ((*(_player->get_graphic_entity()->getPosition()))[0] + 100.f))
             / 120.f
          );

          _balls[i]->set(
            8. * cos(angle), -8. * sin(angle)
          );
        }
      }
    }

    for(unsigned int i = 0; i < _balls.size(); i++)
      _balls[i]->move();

    // display
    this->display();

  } while(!done);

  return;
}


bool GameController::event_loop()
{
  bool done = false;
  SDL_Event event;
  
  static int left = 0;
  static int right = 0;
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
          case SDLK_LEFT:
            left = 1;
          break;
          case SDLK_RIGHT:
            right = 1;
          break;
          case SDLK_SPACE:
            if(_player_ball) {

              _player_ball->set(0, -4);
              _balls.push_back(_player_ball);
              _player_ball = nullptr;
            }
          break;
          default:
          break;
        }
        break;
      case SDL_KEYUP:
        switch (event.key.keysym.sym) {
          case SDLK_LEFT:
            left = 0;
          break;
          case SDLK_RIGHT:
            right = 0;
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

  if(left) {
    _player->move(-15);
    if(_player_ball) {
      _player_ball->move(-15, 0);
    }
  }
  if(right) {
    _player->move(15);
    if(_player_ball) {
      _player_ball->move(15, 0);
    }
  }

  return done;
}


void GameController::display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  _subscene->draw();
  
  SDL_GL_SwapWindow(_window);

  //SDL_Delay(30);
}

