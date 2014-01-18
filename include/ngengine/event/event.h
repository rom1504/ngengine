#ifndef NATIV_GAMES_ENGINE_EVENTS_EVENTS_H
#define NATIV_GAMES_ENGINE_EVENTS_EVENTS_H

/*
	Event:
	Permet de définir une structure d'événements indépendante du système de fenêtrage.
	Elle va sans doute évoluer par la suite (gestion des keyCodes et tableau de booléens représentant les keyCodes actif/nonactifs etc..).
*/

#include <ngengine/utils/types.h>

namespace nge {

	/**
	 * \namespace NGE::Event
    *
    * Concerne la gestion des événements. \n
	 * Sur PC, il s'agit de la gestion de la souris et du clavier
    * Sur téléphone Android, il s'agit de la gestion de l'écran tactile
    *
	 */

	namespace event {

// -- La souris --
#define EC_EventMouse_ButtonLeft 0
#define EC_EventMouse_ButtonRight 1
#define EC_EventMouse_ButtonMiddle 2

		struct EventMouseMap { 
			Sint32 x, y; // la position de la souris dans la fenêtre, n'a de sens que si in = true
			// x = -1 et y = -1 si la souris est en dehors de la fenêtre
		
			bool button[3]; // = 1 si le bouton est appuyé
		};

// -- Le clavier --
// Définition des touches selon un clavier AZERTY
// le a d'un QWERTY correspondra à la touche q pour les macros EC_EKM_
// Pour savoir si a est utilisé sur un clavier AZERTY et QWERTY, il faut donc 
// faire une fonction isUnicodeActive(Event, Utf8Char); (faut-il encore que le caractère soit une des touches du clavier)
// Note: Il n'y en a pas besoin si l'on ne fait pas de saisie de texte (on en aura besoin pour les éditeurs :/ donc à voir + tard)
// int SDL_EnableUNICODE(int enable);

// SDLMod SDL_GetModState(void);
// State va de 0 à 2. keymap de 0 à ... à voir
// State est important car si il indique si num lock est actif ou non etc...
// On active appuie sur Num lock, mais comment savoir si l'on doit activer ou désactiver num lock ?

// EKM = EventKeyboardMap
// Les 2 premiers pour EventKeyboardMap.state et EventKeyboardMap.key
#define EC_EKM_Num    0 // OK
#define EC_EKM_Caps   1 // OK
// Le reste pour EventKeyboardMap.key
#define EC_EKM_Insert  2 // OK
#define EC_EKM_LShift 3 // OK
#define EC_EKM_RShift 4 // OK
#define EC_EKM_LCtrl  5 // OK
#define EC_EKM_RCtrl  6 // OK
#define EC_EKM_LAlt   7 // OK
#define EC_EKM_RAlt   8 // OK
#define EC_EKM_LMeta  9  // OK  // touche Windows Gauche - Meta Gauche
#define EC_EKM_RMeta  10  // OK  // touche Windows Droit - Meta droit
#define EC_EKM_ArrowUp 11 // OK
#define EC_EKM_ArrowDown 12 // OK
#define EC_EKM_ArrowLeft 13 // OK
#define EC_EKM_ArrowRight 14 // OK
#define EC_EKM_Escape 15 // OK
#define EC_EKM_Tab 16 // OK
#define EC_EKM_a 17 // OK
#define EC_EKM_b 18 // OK
#define EC_EKM_c 19 // OK
#define EC_EKM_d 20 // OK
#define EC_EKM_e 21 // OK
#define EC_EKM_f 22 // OK
#define EC_EKM_g 23 // OK
#define EC_EKM_h 24 // OK
#define EC_EKM_i 25 // OK
#define EC_EKM_j 26 // OK
#define EC_EKM_k 27 // OK
#define EC_EKM_l 28 // OK
#define EC_EKM_m 29 // OK
#define EC_EKM_n 30 // OK
#define EC_EKM_o 31 // OK
#define EC_EKM_p 32 // OK
#define EC_EKM_q 33 // OK
#define EC_EKM_r 34 // OK
#define EC_EKM_s 35 // OK
#define EC_EKM_t 36 // OK
#define EC_EKM_u 37 // OK
#define EC_EKM_v 38 // OK
#define EC_EKM_w 39 // OK
#define EC_EKM_x 40 // OK
#define EC_EKM_y 41 // OK
#define EC_EKM_z 42 // OK
#define EC_EKM_0 43 // OK
#define EC_EKM_1 44 // OK
#define EC_EKM_2 45 // OK
#define EC_EKM_3 46 // OK
#define EC_EKM_4 47 // OK
#define EC_EKM_5 48 // OK
#define EC_EKM_6 49 // OK
#define EC_EKM_7 50 // OK
#define EC_EKM_8 51 // OK
#define EC_EKM_9 52 // OK
#define EC_EKM_KP0 53 // OK // KP = KP
#define EC_EKM_KP1 54 // OK
#define EC_EKM_KP2 55 // OK
#define EC_EKM_KP3 56 // OK
#define EC_EKM_KP4 57 // OK
#define EC_EKM_KP5 58 // OK
#define EC_EKM_KP6 59 // OK
#define EC_EKM_KP7 60 // OK
#define EC_EKM_KP8 61 // OK
#define EC_EKM_KP9 62 // OK
#define EC_EKM_KPDiv 63
#define EC_EKM_KPMult 64
#define EC_EKM_KPMinus 65
#define EC_EKM_KPPlus 66
#define EC_EKM_KPReturn 67
#define EC_EKM_Return 68
#define EC_EKM_Backspace 69
#define EC_EKM_Space 70
#define EC_EKM_Undefined 71
/*#define EC_EKM_
#define EC_EKM_
#define EC_EKM_
#define EC_EKM_
d'autres à venir genre F1 F2 F3 mais ce ne sera pas utilisable sous Mac. (même si je l'ai planté, c'est pas 1 raison d'implémenter la lib sous Mac).
*/

		struct EventKeyboardMap {
			
			bool states[2]; // Num lock ? Majuscules ? etc...
			bool key[72]; // L'état des touches a b c d e f Maj ArrayUp etc..
			//EC::Char keyUnicode[42]; // la correspondance unicode des touches pour les lettres et les numéros
			//A mettre + tard pour gérer le japonais par exemple, ou même un clavier qwerty
	
			// 10, 42: valeurs au pif tant que les macros ne sont pas définies
		};

/*
	Pour l'instant, on ne gère 2 cas:
	- Soit la fenêtre est active, cad la souris dedans, et la fenêtre en 1er plan.
	- Soit la fenêtre n'est pas active
	Pour notre utilisation, cela est suffisant.
*/

		struct EventWindow {
			bool active;
			//bool mouseIn;
		};
// ----

		struct EventMap { // contient l'état du claviers et de la souris. 
		
			EventMouseMap mouse;
			EventKeyboardMap keyboard;
			EventWindow window;
		};

// ---- Les structures pour définir les modifications

// Définition des valeurs de EventMouse.id
#define EC_EventMouse_ButtonLeftDown 0
#define EC_EventMouse_ButtonLeftUp 1
#define EC_EventMouse_ButtonRightDown 2
#define EC_EventMouse_ButtonRightUp 3
#define EC_EventMouse_ButtonMiddleDown 4
#define EC_EventMouse_ButtonMiddleUp 5
#define EC_EventMouse_Move 6

		struct EventMouseChange {
			Uint8 type; // champ non utilisé, il est dans EventChange.
			Uint8 id; //
			Sint32 dx, dy; // Si c'est Move
		};

// Définition des valeurs de EventKeyboard.id
// EKC = EventKeyboardChange
#define EC_EKC_KeyDown 0
#define EC_EKC_KeyUp 1

		struct EventKeyboardChange {
			Uint8 type;
			Uint8 id; // Down / up
			Uint8 keyId;// EC_EKM_*keyId* -> la touche concernée
		};

// EW: EventWindow
#define EC_EW_Close 0
#define EC_EW_Activate 1
#define EC_EW_Unactivate 2
//#define EC_EW_MouseOut 3
//#define EC_EW_MouseIn 4

		struct EventWindowChange {
			Uint8 type;
			Uint8 id;
		};

// -- Les événements --

#define EC_Event_None 0
#define EC_Event_Mouse 1
#define EC_Event_Keyboard 2
#define EC_Event_Window 3 // active ou non - fermeture - redimensionnement (on ne le traitera pas pour le moment)

		union EventChange { // Utilisation des unions utiles ici ! 
			Uint8 type;
			EventMouseChange mouse;
			EventKeyboardChange keyboard;
			EventWindowChange window;
		};

		struct Event {
			EventMap map; // Définit l'état du clavier et de la souris
			
			// Maintenant définition de l'événement provoqué
			Uint8 type; // Mouse - Keyboard - other
			EventChange change;
		};
	}
}

#endif
