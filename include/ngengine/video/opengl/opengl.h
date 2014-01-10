#ifndef NATIV_GAMES_ENGINE_VIDEO_OPENGL_OPENGL_H
#define NATIV_GAMES_ENGINE_VIDEO_OPENGL_OPENGL_H

#include <ngengine/utils/platform.h>

#ifdef NGE_PLATFORM_LINUX
#include <GL/glew.h>

#else
#error System not supported yet
#endif

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#endif

