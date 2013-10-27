#ifndef NATIV_GAMES_ENGINE_VIDEO_SCENE_SCENE_H
#define NATIV_GAMES_ENGINE_VIDEO_SCENE_SCENE_H

#include <ngengine/video/scene/subscene.h>
#include <vector>

namespace nge {
  namespace scene {

  class Scene {
    public:

      Scene();
      ~Scene();

      void add(SubScene *subscene);
      void draw();

      void updateScreenHeight(Uint32 screenHeight);

      std::vector<SubScene *> *getSubScenes();

    private:
  
      std::vector<SubScene *> _subscenes;
  };

  }
}

#endif
