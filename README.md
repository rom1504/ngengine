#NGEngine

[![Build Status](https://travis-ci.org/nativgames/ngengine.png?branch=master)](https://travis-ci.org/nativgames/ngengine)

NGEngine by Nativ' Games is a C++ 2D/3D Game Engine, with the minimum of dependencies:
- OpenGL: A low-level graphics library
- GLU
- Glew
- Glm (mathematic library designed for OpenGL programs)

The examples use the following libraries:
- SDL 1.2: create the window in which the OpenGL Context is displayed
- SDL_image_1.2: support for png/jpeg images

Currently, OpenGL 2.1 is used, without shader support.

An update to SDL 2.0 should be done in the future (and to OpenGL 3.1 or 3.2).

#Library Structure

- Collision: the collision shapes (3D BoundingBox for instant, in the future 2D/3D AABB, 2D (/3D ?) OBB etc...).
- Event
- Utils
- Video

#Folder Structure

- /include: contains the .h files of ngengine
- /src: contains the sources of ngengine (cpp)
- /externals: contains the external libraries: glm
- /build: contains compilation files (linux makefile)
- /bin: contains the ngengine library and the examples executables
- /examples: contains the sources of the examples
- /resources: contains the resources for the examples

#Compilation

##Linux

###With Apt-Get

- sudo apt-get install glew-utils libsdl2-dev libsdl2-image-dev libfreetype*
- cd ngengine && git submodule init && git submodule update
- cd build/linux && make

`make clean` and `make mrproper` are available in the build/linux makefile.

#Conventions

- Each namespace is in lower case letters.
- 2D and 3D folders are respectively written D2 and D3 because 2D and 3D can't refer to namespaces (namespaces must begin with a letter). 
- Each Class or Struct or Enum begins with an upper case letter.

#Warnings

- Lots of comments are in French, others are in English. They will definitly be re-written in English soon.
- The 06_CameraQuat presents a bug: the rotation should be around the left\_axis and the normal\_axis, and when you do rounds with the camera, it turns over the target\_axis too... TO FIX
- Moving to OpenGL 3.X

#Licence

MIT License: see License.md
