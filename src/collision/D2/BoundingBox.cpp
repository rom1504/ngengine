#include <ngengine/collision/D2/BoundingBox.h>
#include <string.h>

using namespace nge;
using namespace nge::collision;
using namespace nge::collision::D2;

BoundingBox::BoundingBox() : AbstractDescriptor(AbstractDescriptor::BoundingBox)
{
  
}

BoundingBox::~BoundingBox()
{

}

bool BoundingBox::collisionWithOffset(
  AbstractDescriptor *ad, 
  glm::vec2 offsetSelf, 
  glm::vec2 offsetAd
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
  glm::vec2 offsetSelf,
  glm::vec2 offsetAd
)
{
  bool ret = 1;

  // si c'est une bounding box
  BoundingBox *adb = (BoundingBox *) ad; 
  Sint32 *map = adb->getMap();

  if(((_map[0] + offsetSelf[0]) > (map[1]  + offsetAd[0])) || 
     ((_map[1] + offsetSelf[0]) < (map[0]  + offsetAd[0])) ||
     ((_map[2] + offsetSelf[1]) > (map[3]  + offsetAd[1])) || 
     ((_map[3] + offsetSelf[1]) < (map[2]  + offsetAd[1]))
    )
    ret = 0;

  return ret;
}

void BoundingBox::set(Sint32 xmin, Sint32 xmax, Sint32 ymin, Sint32 ymax)
{
  _map[0] = xmin;
  _map[1] = xmax;
  _map[2] = ymin;
  _map[3] = ymax;

  _points[0] = xmin; 
  _points[1] = ymin;
  _points[2] = xmax;
  _points[3] = ymin;
  _points[4] = xmax;
  _points[5] = ymax;
  _points[6] = xmin;
  _points[7] = ymax;
}

Sint32 *BoundingBox::getPoints()
{
  return _points;
}

Sint32 *BoundingBox::getMap()
{
  return _map;
}

// ENTITY

BoundingBoxEntity::BoundingBoxEntity(BoundingBox *bb) : 
  nge::video::D2::entity::Basic(4, 1, GL_LINE_LOOP)
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
  Sint32 *points = _bb->getPoints();
  int i = 0, j, k;

  // Première face: p1 p2 p3 p4

  memcpy(_vertices, points, 4 * 2 * sizeof(Sint32));
}

