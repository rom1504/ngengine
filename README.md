#NGEngine

[![Build Status](https://travis-ci.org/nativgames/ngengine.png?branch=master)](https://travis-ci.org/nativgames/ngengine)

NGEngine by Nativ' Games is a C++ 2D/3D Game Engine, with the minimum of dependencies:
- OpenGL 3.1: A low-level graphics library
- Glew
- Glm (mathematic library designed for OpenGL programs)

The examples use the following libraries:
- SDL 2.0: create the window in which the OpenGL context is displayed
- SDL_image_2.0: support for png/jpeg images

#Folder Structure

- /include: contains the .h files of ngengine
- /src: contains the sources of ngengine (cpp)
- /externals: contains the external libraries: glm
- /build: contains compilation files (linux makefile)
- /bin: contains the ngengine library and the examples executables
- /examples: contains the sources of the examples
- /resources: contains the resources for the examples
- /tests: contains the unit tests
- /.travis.yml: configuration of the compilation to provide continous-integration (cloning this project on a VM, installing the dependencies, compiling the project, compiling the tests, launching the tests.

#Library Structure

- Collision: the collision shapes (3D BoundingBox for instant, in the future 2D/3D AABB, 2D (/3D ?) OBB etc...).
- Event
- Utils
- Video
- Network: contains classes to create TCP/IP clients and servers (Linux for instant).

#Compilation

##Linux

###With Apt-Get

- sudo apt-get install glew-utils libsdl2-dev libsdl2-image-dev libfreetype*
- cd ngengine && git submodule init && git submodule update
- cd build/linux && make

`make clean` and `make mrproper` are available in the build/linux makefile.

If you don't succeed to compile, read .travis.yml it details how to install the dependencies.

#Conventions

- Each namespace is in lower case letters.
- 2D and 3D folders are respectively written D2 and D3 because 2D and 3D can't refer to namespaces (namespaces must begin with a letter). 
- Each Class or Struct or Enum begins with an upper case letter.

#Warnings

- Lots of comments are in French, others are in English: I'm rewriting them in English.
- The 06_CameraQuat presents a bug: the rotation should be around the left\_axis and the normal\_axis, and when you do rounds with the camera, it turns over the target\_axis too... TO FIX

#Licence

MIT License: see License.md

