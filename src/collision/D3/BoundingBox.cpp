#include <ngengine/collision/D3/BoundingBox.h>
#include <string.h>
/*
using namespace nge;
using namespace nge::collision;
using namespace nge::collision::D3;

BoundingBox::BoundingBox() : AbstractDescriptor(AbstractDescriptor::BoundingBox)
{
  
}

BoundingBox::~BoundingBox()
{

}

bool BoundingBox::collisionWithOffset(
  AbstractDescriptor *ad, 
  glm::vec3 offsetSelf, 
  glm::vec3 offsetAd
)
{
  bool ret = 0;

  if(ad->getType() == AbstractDescriptor::BoundingBox) {
    ret = this->collisionWithoutCallOtherCollisionWithOffset(ad, offsetSelf, offsetAd);
  }
  else
    ret = ad->collisionWithoutCallOtherCollisionWithOffset(this, offsetAd, offsetSelf);

  return ret;
}

bool BoundingBox::collisionWithoutCallOtherCollisionWithOffset(
  AbstractDescriptor *ad,
  glm::vec3 offsetSelf,
  glm::vec3 offsetAd
)
{
  bool ret = 1;

  // si c'est une bounding box
  BoundingBox *adb = (BoundingBox *) ad; 
  glm::vec2 *map = adb->getMap();

  if(((_map[0][0] > map[0][1]) && (_map[0][1] < map[0][0])) ||
     ((_map[1][0] > map[1][1]) && (_map[1][1] < map[1][0])) ||
     ((_map[1][0] > map[1][1]) && (_map[1][1] < map[1][0])))
    ret = 0;

  return ret;
}

void BoundingBox::set(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
{
  _map[0] = glm::vec2(xmin, xmax);
  _map[1] = glm::vec2(ymin, ymax);
  _map[2] = glm::vec2(zmin, zmax);

  _points[0] = glm::vec3(xmin, ymin, zmin);
  _points[1] = glm::vec3(xmax, ymin, zmin);
  _points[2] = glm::vec3(xmin, ymax, zmin);
  _points[3] = glm::vec3(xmax, ymax, zmin);
  _points[4] = glm::vec3(xmin, ymin, zmax);
  _points[5] = glm::vec3(xmax, ymin, zmax);
  _points[6] = glm::vec3(xmin, ymax, zmax);
  _points[7] = glm::vec3(xmax, ymax, zmax);
}

glm::vec3 *BoundingBox::getPoints()
{
  return _points;
}

glm::vec2 *BoundingBox::getMap()
{
  return _map;
}

// ENTITY

BoundingBoxEntity::BoundingBoxEntity(BoundingBox *bb) : 
  nge::video::D3::entity::Basic(4, 4, GL_LINE_LOOP)
{
  _bb = bb;

  this->setVertexBuf(_vertices, false);  // (x, y) couples
  this->setColorBuf(_colors, false);

  memset(_colors, 255, 96);
}

BoundingBoxEntity::~BoundingBoxEntity()
{
  
}

void BoundingBoxEntity::update()
{
  glm::vec3 *points = _bb->getPoints();
  int i = 0, j, k;

  // Première face: p1 p2 p3 p4

#define copie_point(n) for(k = 0; k < 3; k++) {\
      _vertices[i + k] = points[n][k];\
    }\
    i+= 3;

  copie_point(0)
  copie_point(1)
  copie_point(3)
  copie_point(2)
  // Seconde face: p3 p4 p5 p6

  copie_point(2)
  copie_point(3)
  copie_point(7)
  copie_point(6)

  copie_point(0)
  copie_point(1)
  copie_point(5)
  copie_point(4)

  copie_point(4)
  copie_point(5)
  copie_point(7)
  copie_point(6)

}
*/
