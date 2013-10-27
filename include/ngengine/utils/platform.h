#ifndef NATIV_GAMES_ENGINE_UTILS_PLATFORM_H
#define NATIV_GAMES_ENGINE_UTILS_PLATFORM_H

/*
	Definition of supported OS
*/
#ifdef linux 
#define NGE_PLATFORM_LINUX

#elif defined (__APPLE__)
#define NGE_PLATFORM_MAC

#elif defined(WIN32) || defined(_WIN32)
#define NGE_PLATFORM_WINDOWS

#else
#error Unsupported Operating Sytem
#endif

#endif

