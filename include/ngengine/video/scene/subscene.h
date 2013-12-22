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

      void add(nge::video::D2::Entity *entity);
      void add(nge::video::D3::Entity *entity);
      void remove(nge::video::D2::Entity *entity);
      void remove(nge::video::D3::Entity *entity);
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
      
      std::vector<nge::video::D2::Entity *> *getEntities2D();
      std::vector<nge::video::D3::Entity *> *getEntities3D();

      void setCamera3D(nge::video::D3::Camera *cam);

      nge::video::D2::Camera *getCamera2D();
      nge::video::D3::Camera *getCamera3D();

    private:
  
      Uint32 _screenHeight;
      Uint32 _width;
      Uint32 _height;
      Uint32 _x;
      Uint32 _y;
      std::vector<nge::video::D2::Entity *> _entities2D;
      std::vector<nge::video::D3::Entity *> _entities3D;

      nge::video::D2::Camera _cam2D;
      nge::video::D3::Camera *_cam3D;
  };

  }
}

#endif
