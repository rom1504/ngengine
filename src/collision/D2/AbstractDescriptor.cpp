#include <ngengine/collision/D2/AbstractDescriptor.h>

using namespace nge;
using namespace nge::collision;
using namespace nge::collision::D2;


AbstractDescriptor::AbstractDescriptor(Uint32 type)
{
  _type = type;
}

AbstractDescriptor::~AbstractDescriptor()
{

}

bool AbstractDescriptor::collision(AbstractDescriptor *ad)
{
  return this->collisionWithOffset(ad, glm::vec2(0.f, 0.f), glm::vec2(0.f, 0.f));
}

bool AbstractDescriptor::collisionWithoutCallOtherCollision(AbstractDescriptor *ad)
{
  return this->collisionWithoutCallOtherCollisionWithOffset(
    ad, 
    glm::vec2(0.f, 0.f), 
    glm::vec2(0.f, 0.f)
  );
}

Uint32 AbstractDescriptor::getType()
{
  return _type;
}

