#ifndef NATIVE_GAMES_ENGINE_BRIDGES_SDL2_SDL2_H
#define NATIVE_GAMES_ENGINE_BRIDGES_SDL2_SDL2_H

#include <ngengine/ngengine.h>

nge::texture::Texture *NGE_SDL_Texture_Load(const char *path); // dans sdl.cpp
void NGE_SDL_Event_Init(nge::event::Event *event);
bool NGE_SDL_Event_Get(nge::event::Event *event);

nge::Uint32 NGE_SDL_GetTime(); // getTicks
void NGE_SDL_Pause(nge::Uint32 ms);

#endif

