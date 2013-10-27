#ifndef NATIV_GAMES_ENGINE_VIDEO_D3_CAMERA_CAMERA_H
#define NATIV_GAMES_ENGINE_VIDEO_D3_CAMERA_CAMERA_H

#include <glm/glm.hpp>

namespace nge {
  namespace video {
    namespace D3 {

class Camera {
  public:
    Camera();
    ~Camera();

    glm::vec3 *getPosition();
    glm::vec3 *getTarget();
    glm::vec3 *getNormal();

    double getFovy();
    double getAspect();
    double getZNear();
    double getZFar();

    void setFovy(double d);
    void setAspect(double width, double height);
    void setAspect(double d);
    void setZNear(double z);
    void setZFar(double z);

  protected:
  
    glm::vec3 _position;
    glm::vec3 _target;
    glm::vec3 _normal;

    double _fovy;
    double _aspect;
    double _zNear;
    double _zFar;
};

    }
  }
}

#endif

