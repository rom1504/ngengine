#include <ngengine/collision/D3/AbstractDescriptor.h>

using namespace nge;
using namespace nge::collision;
using namespace nge::collision::D3;


AbstractDescriptor::AbstractDescriptor(Uint32 type)
{
  _type = type;
}

AbstractDescriptor::~AbstractDescriptor()
{

}

bool AbstractDescriptor::collision(AbstractDescriptor *ad)
{
  return this->collisionWithOffset(ad, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f));
}

bool AbstractDescriptor::collisionWithoutCallOtherCollision(AbstractDescriptor *ad)
{
  return this->collisionWithoutCallOtherCollisionWithOffset(
    ad, 
    glm::vec3(0.f, 0.f, 0.f), 
    glm::vec3(0.f, 0.f, 0.f)
  );
}

Uint32 AbstractDescriptor::getType()
{
  return _type;
}

