/*
	Un fichier qui est l'unique lien entre la SDL et RPGEngine.
	Fonctions implémentées:
	-> Chargement d'une texture png, jpg etc... via SDL-image
	L'utilisation de SDL_image pourra être changée + tard, passer par libpng est + rapide pour les perfs.
	Je ne pense pas que nous ayons besoin d'un autre format que le png, il gère déjà la transparence et bon 
	taux de compression.
	-> Gestion des Events, en faisant 1 conversion des SDLEvent vers les NGE::Event::Event (traitement le + rapide possible).
	Cela permet d'avoir:
	1) RPGEngine indépendant de la SDL, i.e. on peut prendre la SFML ou même freeglut plus tard
	2) Un système de gestion des événements complet pour la GUI par exemple, au sein de RPGEngine.
*/

#include <ngengine/ngengine.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "NGE_SDL.h"
#include <iostream>

using namespace nge;
using namespace nge::texture;

Texture *NGE_SDL_Texture_Load(const char *path)
{
	PixelBuffer *buf;
	Texture *tex = NULL;
	SDL_Surface *surface;
	Sint32 i, j;
	Uint8 *p, *q;
	Uint8 r, g, b, a;
	
	if(path) {
		
		if((surface = IMG_Load(path))) {
			//SDL_LockSurface(surface); -> peut poser des pb
			buf = new PixelBuffer(surface->format->BytesPerPixel, surface->w, surface->h);
			p = (Uint8 *) surface->pixels;

			//for(i = 0; i < surface->h; i++) {
      for(i = surface->h - 1; i >= 0; i--) {
				q = buf->getPixelAddr(0, i + (buf->getRealHeight() - buf->getHeight()));
				
				for(j = 0; j < surface->w; j++) {
					r = p[j * surface->format->BytesPerPixel + 0];
					g = p[j * surface->format->BytesPerPixel + 1];
					b = p[j * surface->format->BytesPerPixel + 2];
					
					if(surface->format->BytesPerPixel == 4)
						a = p[j * surface->format->BytesPerPixel + 3];
					else;
					
					q[j * surface->format->BytesPerPixel + 0] = r;
					q[j * surface->format->BytesPerPixel + 1] = g;
					q[j * surface->format->BytesPerPixel + 2] = b;
					if(surface->format->BytesPerPixel == 4)
						q[j * surface->format->BytesPerPixel + 3] = a;
					else;
				}
				
				//p += surface->format->BytesPerPixel * surface->w;
        p += surface->format->BytesPerPixel * surface->w;
			}
			
			tex = new Texture();
			tex->setPixelBuffer(buf);
//			tex->updateInGC();
			//SDL_UnlockSurface(surface);
			SDL_FreeSurface(surface);
		}
		else
      printf("Texture \"%s\" not loaded: not found.\n", path);
	}
	else;
	
	return tex;
}
/*
static void NGE_SDL_Event_LoadStates(nge::event::Event *event)
{
	SDLMod mod;

	mod = SDL_GetModState();

	if(!mod)
		;
	else { 
		// On initialise l'état de: numlock, caps, insert avec les bonnes valeurs.
		if(mod & KMOD_NUM)
			event->map.keyboard.states[EC_EKM_Num] = 1;
		else;
		if(mod & KMOD_CAPS)
			event->map.keyboard.states[EC_EKM_Caps] = 1;
		else;
	}

	return;
}

void NGE_SDL_Event_Init(nge::event::Event *event)
{
	if(event) {
		memset(event, 0, sizeof(nge::event::Event));
		
		// Chargement de l'état (activée ou non) de inser/num lock/caps
		// Ne pas confondre avec : "la touche caps lock est pressée". 
		// Cela c'est le keymap[EC_EKM_NumLock] qui le détermine.
		NGE_SDL_Event_LoadStates(event);
		
		// Pour les touches qui sont appuyées avant que l'application ne soit lancé, on ne s'en occupe pas
		// il lui suffit de lacher la touche et de réappuyer.	
	}
	else;
}*/

/*
	La fonction marrante: un switch immonde.
	Une bonne partie écrite à la main, sauf pour SDLK_a -> SDLK_z et SDLK_0 -> SDLK_9 où j'ai fait 1 script php avec 1 boucle et c'était plié (commande : "php script.php > truc.c" exécute le script php et met le résultat dans truc.c)
	C'est une nouvelle bidouille pour BIDOUILLE :P
*/
/*
static nge::Uint8 Event_ConvertKey(SDLKey key)
{
	nge::Uint8 r = EC_EKM_Undefined;
	
	switch(key) {
		case SDLK_ESCAPE:
				r = EC_EKM_Escape;
			break;
		case SDLK_TAB:
				r = EC_EKM_Tab;
			break;
		case SDLK_UP:
				r = EC_EKM_ArrowUp;
			break;
		case SDLK_DOWN:
				r = EC_EKM_ArrowDown;
				
			break;
		case SDLK_LEFT:
				r = EC_EKM_ArrowLeft;
			break;
		case SDLK_RIGHT:
				r = EC_EKM_ArrowRight;
			break;
		case SDLK_NUMLOCK:
				r = EC_EKM_Num;
			break;
		case SDLK_CAPSLOCK:
				r = EC_EKM_Caps;
			break;
		case SDLK_INSERT:
				r = EC_EKM_Insert;
			break;
		case SDLK_LSHIFT:
				r = EC_EKM_LShift;
			break;
		case SDLK_RSHIFT:
				r = EC_EKM_RShift;
			break;
		case SDLK_LCTRL:
				r = EC_EKM_LCtrl;
			break;
		case SDLK_RCTRL:
				r = EC_EKM_RCtrl;
			break;
		case SDLK_LALT:
				r = EC_EKM_LAlt;
			break;
		case SDLK_RALT:
				r = EC_EKM_RAlt;
			break;
		case SDLK_LMETA:
				r = EC_EKM_LMeta;
			break;
		case SDLK_RMETA:
				r = EC_EKM_RMeta;
			break;
		case SDLK_0:
				r = EC_EKM_0;
			break;
		case SDLK_1:
				r = EC_EKM_1;
			break;
		case SDLK_2:
				r = EC_EKM_2;
			break;
		case SDLK_3:
				r = EC_EKM_3;
			break;
		case SDLK_4:
				r = EC_EKM_4;
			break;
		case SDLK_5:
				r = EC_EKM_5;
			break;
		case SDLK_6:
				r = EC_EKM_6;
			break;
		case SDLK_7:
				r = EC_EKM_7;
			break;
		case SDLK_8:
				r = EC_EKM_8;
			break;
		case SDLK_9:
				r = EC_EKM_9;
			break;
		case SDLK_a:
				r = EC_EKM_a;
			break;
		case SDLK_b:
				r = EC_EKM_b;
			break;
		case SDLK_c:
				r = EC_EKM_c;
			break;
		case SDLK_d:
				r = EC_EKM_d;
			break;
		case SDLK_e:
				r = EC_EKM_e;
			break;
		case SDLK_f:
				r = EC_EKM_f;
			break;
		case SDLK_g:
				r = EC_EKM_g;
			break;
		case SDLK_h:
				r = EC_EKM_h;
			break;
		case SDLK_i:
				r = EC_EKM_i;
			break;
		case SDLK_j:
				r = EC_EKM_j;
			break;
		case SDLK_k:
				r = EC_EKM_k;
			break;
		case SDLK_l:
				r = EC_EKM_l;
			break;
		case SDLK_m:
				r = EC_EKM_m;
			break;
		case SDLK_n:
				r = EC_EKM_n;
			break;
		case SDLK_o:
				r = EC_EKM_o;
			break;
		case SDLK_p:
				r = EC_EKM_p;
			break;
		case SDLK_q:
				r = EC_EKM_q;
			break;
		case SDLK_r:
				r = EC_EKM_r;
			break;
		case SDLK_s:
				r = EC_EKM_s;
			break;
		case SDLK_t:
				r = EC_EKM_t;
			break;
		case SDLK_u:
				r = EC_EKM_u;
			break;
		case SDLK_v:
				r = EC_EKM_v;
			break;
		case SDLK_w:
				r = EC_EKM_w;
			break;
		case SDLK_x:
				r = EC_EKM_x;
			break;
		case SDLK_y:
				r = EC_EKM_y;
			break;
		case SDLK_z:
				r = EC_EKM_z;
			break;
		case SDLK_KP0:
				r = EC_EKM_KP0;
			break;
		case SDLK_KP1:
				r = EC_EKM_KP1;
			break;
		case SDLK_KP2:
				r = EC_EKM_KP2;
			break;
		case SDLK_KP3:
				r = EC_EKM_KP3;
			break;
		case SDLK_KP4:
				r = EC_EKM_KP4;
			break;
		case SDLK_KP5:
				r = EC_EKM_KP5;
			break;
		case SDLK_KP6:
				r = EC_EKM_KP6;
			break;
		case SDLK_KP7:
				r = EC_EKM_KP7;
			break;
		case SDLK_KP8:
				r = EC_EKM_KP8;
			break;
		case SDLK_KP9:
				r = EC_EKM_KP9;
			break;
		case SDLK_KP_DIVIDE:
				r = EC_EKM_KPDiv;
			break;
		case SDLK_KP_MULTIPLY:
				r = EC_EKM_KPMult;
			break;
		case SDLK_KP_MINUS:
				r = EC_EKM_KPMinus;
			break;
		case SDLK_KP_PLUS:
				r = EC_EKM_KPPlus;
			break;
		case SDLK_KP_ENTER:
				r = EC_EKM_KPReturn;
			break;
		case SDLK_RETURN:
				r = EC_EKM_Return;
			break;
		case SDLK_BACKSPACE:
				r = EC_EKM_Backspace;
			break;
		default:
			break;
	}
	
	return r;
}

bool NGE_SDL_Event_Get(nge::event::Event *event)
{
	bool ret = false;
	SDL_Event sdlevent;
	Uint8 state;
	
	if(event) {
		if(SDL_PollEvent(&sdlevent)) {
			ret = true;
	
			switch(sdlevent.type) {
				case SDL_QUIT:
						event->type = EC_Event_Window;
						event->change.window.id = EC_EW_Close;
					break;
				case SDL_ACTIVEEVENT:
						event->type = EC_Event_Window;
						state = SDL_GetAppState();
						
						if((state & SDL_APPACTIVE) && (state & SDL_APPMOUSEFOCUS) && (state & SDL_APPINPUTFOCUS))
						{
							if(!event->map.window.active) {
								event->map.window.active = 1;
								event->change.window.id = EC_EW_Activate;
								NGE_SDL_Event_LoadStates(event); // on recharge l'état de num lock etc...
								// pour peu que l'utilisateur ait changé ces états
							}
							else
								ret = false;
						}

						else {
							if(event->map.window.active) {
								event->change.window.id = EC_EW_Unactivate;
								event->map.window.active = 0;
							}
							else
								ret = false;
						}
						
					break;
				case SDL_MOUSEBUTTONDOWN:

					event->type = EC_Event_Mouse;
					event->map.mouse.x = sdlevent.button.x;
					event->map.mouse.y = sdlevent.button.y;

					switch(sdlevent.button.button) {
							
						case SDL_BUTTON_LEFT:
							event->change.mouse.id = EC_EventMouse_ButtonLeftDown;
							event->map.mouse.button[EC_EventMouse_ButtonLeft] = 1;
							break;
						case SDL_BUTTON_RIGHT:
							event->change.mouse.id = EC_EventMouse_ButtonRightDown;
							event->map.mouse.button[EC_EventMouse_ButtonRight] = 1;
							break;
						case SDL_BUTTON_MIDDLE:
							event->change.mouse.id = EC_EventMouse_ButtonMiddleDown;
							event->map.mouse.button[EC_EventMouse_ButtonMiddle] = 1;
							break;
						default:
							break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					event->type = EC_Event_Mouse;
					event->map.mouse.x = sdlevent.button.x;
					event->map.mouse.y = sdlevent.button.y;

					switch(sdlevent.button.button) {
							
						case SDL_BUTTON_LEFT:
							event->change.mouse.id = EC_EventMouse_ButtonLeftUp;
							event->map.mouse.button[EC_EventMouse_ButtonLeft] = 0;
							break;
						case SDL_BUTTON_RIGHT:
							event->change.mouse.id = EC_EventMouse_ButtonRightUp;
							event->map.mouse.button[EC_EventMouse_ButtonRight] = 0;
							break;
						case SDL_BUTTON_MIDDLE:
							event->change.mouse.id = EC_EventMouse_ButtonMiddleUp;
							event->map.mouse.button[EC_EventMouse_ButtonMiddle] = 0;
							break;
						default:
							break;
					}
					break;
				case SDL_MOUSEMOTION:
						event->type = EC_Event_Mouse;
						event->change.mouse.id = EC_EventMouse_Move;
						event->change.mouse.dx = sdlevent.motion.xrel;
						event->change.mouse.dy = sdlevent.motion.yrel;
						event->map.mouse.x = sdlevent.motion.x;
						event->map.mouse.y = sdlevent.motion.y;
					break;
				case SDL_KEYDOWN:
						event->type = EC_Event_Keyboard;
						event->change.keyboard.id = EC_EKC_KeyDown;
						event->change.keyboard.keyId = Event_ConvertKey(sdlevent.key.keysym.sym);
						event->map.keyboard.key[event->change.keyboard.keyId] = 1;
					break;
				case SDL_KEYUP:
						event->type = EC_Event_Keyboard;
						event->change.keyboard.id = EC_EKC_KeyUp;
						event->change.keyboard.keyId = Event_ConvertKey(sdlevent.key.keysym.sym);
						event->map.keyboard.key[event->change.keyboard.keyId] = 0;
					break;
				default:
						event->type = EC_Event_None;
						ret = false;
					break;
				
			}
		}
		
		else;
	}
	else;
	
	return ret;
}*/

nge::Uint32 NGE_SDL_GetTime()
{
	return SDL_GetTicks();
}

void NGE_SDL_Pause(nge::Uint32 ms)
{
	SDL_Delay(ms);
}

