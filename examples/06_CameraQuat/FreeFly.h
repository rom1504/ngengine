#ifndef FREE_FLY_H
#define FREE_FLY_H

/*
  version avec quaternions, problème avec la normale.
*/

#include <ngengine/ngengine.h>
#include <glm/gtc/quaternion.hpp>

class FreeFly : public nge::video::D3::Camera {

  public:
  
    FreeFly();
    ~FreeFly();

    void forward(double l); // avance selon _target
    void left(double l); // avance selon le produit vectoriel de _target et _normal
    void normal(double l); // avance selon _normal

    void rotateForward(double angle);
    void rotateLeft(double angle);
    void rotateNormal(double angle);

  private:

    void updateVectRel();

    glm::quat _quat;

    glm::vec3 _targetRel;
    glm::vec3 _leftRel;
    glm::vec3 _normalRel;
};

#endif

