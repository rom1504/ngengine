#ifndef NGENGINE_EXAMPLES_10_BREAKOUT_LIKE_CONTROLLERS_GAME_H
#define NGENGINE_EXAMPLES_10_BREAKOUT_LIKE_CONTROLLERS_GAME_H

#include <ngengine/ngengine.h>
#include <SDL2/SDL.h>
#include <vector>

#include <10_Breakout_like/entities/entities.h>

class GameController {
  public:

    GameController(SDL_Window *window);
    ~GameController();

    void start();

  private:

    bool event_loop();
    void display();

    SDL_Window *_window;

    //nge::scene::Scene *_scene; // 1 scene containing 1 subscene ... no use for instant
    nge::scene::SubScene *_subscene; // 1 subscene only

    // entities

    std::vector<BlockEntity *> _blocks;
    std::vector<BallEntity *> _balls;
    PlayerEntity *_player;
    BallEntity *_player_ball;
};

#endif

