#ifndef FREE_FLY_H
#define FREE_FLY_H

/*
  Version FreeFly sans rotation autour du vecteur 'targetRel'.
*/

#include <ngengine/ngengine.h>

class FreeFly : public nge::video::D3::Camera {

  public:
  
    FreeFly();
    ~FreeFly();

    void forward(double l); // avance selon _target
    void left(double l); // avance selon le produit vectoriel de _target et _normal
    void normal(double l); // avance selon _normal

    void rotateLeft(double angle);
    void rotateNormal(double angle);

  private:

    glm::vec3 getCartesianTargetRel();
    void update();

    glm::vec3 _targetRel; // in spheric coordinates
    glm::vec3 _targetRelCart; // in cartesian
    glm::vec3 _leftCart;
};

#endif

