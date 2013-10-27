#ifndef NATIV_GAMES_ENGINE_VIDEO_SCENE_SUBSCENE_H
#define NATIV_GAMES_ENGINE_VIDEO_SCENE_SUBSCENE_H

#include <ngengine/video/D2/entity/entity.h>
#include <ngengine/video/D2/camera/camera.h>
#include <ngengine/video/D3/entity/entity.h>
#include <ngengine/video/D3/camera/camera.h>
#include <vector>

namespace nge {
  namespace scene {

  class SubScene {
    public:

      SubScene(Uint32 screenHeight, Uint32 width, Uint32 height, Uint32 x, Uint32 y);
      ~SubScene();

      void add(entity::Entity *entity);
      void add(video::D3::entity::Entity *entity);
      void draw();

      void setScreenHeight(Uint32 screenHeight);
      void setWidth(Uint32 width);
      void setHeight(Uint32 height);
      void setX(Uint32 x);
      void setY(Uint32 y);

      Uint32 getScreenHeight() const;
      Uint32 getWidth() const;
      Uint32 getHeight() const;
      Uint32 getX() const;
      Uint32 getY() const;
      
      std::vector<entity::Entity *> *getEntities();

      void setCamera3D(nge::video::D3::Camera *cam);

      camera::Camera *getCamera2D();
      nge::video::D3::Camera *getCamera3D();

    private:
  
      Uint32 _screenHeight;
      Uint32 _width;
      Uint32 _height;
      Uint32 _x;
      Uint32 _y;
      std::vector<entity::Entity *> _entities2D;
      std::vector<video::D3::entity::Entity *> _entities3D;

      camera::Camera _cam2D;
      nge::video::D3::Camera *_cam3D;
  };

  }
}

#endif
