#include <ngengine/video/scene/subscene.h>
#include <ngengine/video/opengl/opengl.h>

using namespace nge;
using namespace nge::scene;

SubScene::SubScene(Uint32 screenHeight, Uint32 width, Uint32 height, Uint32 x = 0, Uint32 y = 0)
{
  _screenHeight = screenHeight;
  _width = width;
  _height = height;
  _x = x;
  _y = y;

  _cam2D.setX(0);
	_cam2D.setY(0);
	_cam2D.setWidth(width);
	_cam2D.setHeight(height);
  _cam2D.setFrameSize(width, height);

  _cam3D = nullptr;
}

SubScene::~SubScene()
{
  
}

void SubScene::add(nge::video::D2::Entity *entity)
{
  _entities2D.push_back(entity);
}

void SubScene::add(nge::video::D3::Entity *entity)
{
  _entities3D.push_back(entity);
}

void SubScene::remove(nge::video::D2::Entity *entity)
{
  for(std::vector<nge::video::D2::Entity *>::iterator it = _entities2D.begin(); it < _entities2D.end(); it++) {
    if(*it == entity) {
      _entities2D.erase(it);
      it --;
    }
    else;
  }
}

void SubScene::remove(nge::video::D3::Entity *entity)
{
  for(std::vector<nge::video::D3::Entity *>::iterator it = _entities3D.begin(); it < _entities3D.end(); it++) {
    if(*it == entity) {
      _entities3D.erase(it);
      it --;
    }
    else;
  }
}

void SubScene::draw()
{
  int i, n;

  glViewport(
    (GLint) _x, 
    _screenHeight - ((GLint) _y) - _height, 
    (GLsizei) _width, 
    (GLsizei) _height
  );
  glDisable(GL_TEXTURE_2D);

  if(_entities3D.size() > 0) {

    if(_cam3D) {

      _projection = glm::perspective(
        _cam3D->getFovy(),
        _cam3D->getAspect(), 
        _cam3D->getZNear(),
        _cam3D->getZFar()
      );
 
      glm::vec3 *pos, *target, *normal;

      pos = _cam3D->getPosition();
      target = _cam3D->getTarget();
      normal = _cam3D->getNormal();

      _modelview = glm::mat4(1.0);
      _modelview = glm::lookAt(
        *pos,
        *target,
        *normal
      );
    }
    else
      printf("No 3D camera in the subscene...\n");

    n = _entities3D.size();

    for(i = 0; i < n; i++) {
      _entities3D[i]->draw();
    }
  }

  _projection = glm::mat4();

  glClear(GL_DEPTH_BUFFER_BIT);

  glDisable(GL_DEPTH_TEST);

  _projection = glm::ortho((GLdouble) _cam2D.getX() - 1, 
		  	     (GLdouble)(_cam2D.getWidth() + _cam2D.getX() - 1), 
		  		   (GLdouble)(_cam2D.getHeight() + _cam2D.getY() - 1), 
		  		   (GLdouble) _cam2D.getY() - 1);
  _modelview = glm::mat4(1.0);

  n = _entities2D.size();

  for(i = 0; i < n; i++) {
    _entities2D[i]->draw();
  }

  glEnable(GL_DEPTH_TEST);
}

void SubScene::setScreenHeight(Uint32 screenHeight)
{
  _screenHeight = screenHeight;
}

void SubScene::setWidth(Uint32 width)
{
  _width = width;
}

void SubScene::setHeight(Uint32 height)
{
  _height = height;
}

void SubScene::setX(Uint32 x)
{
  _x = x;
}

void SubScene::setY(Uint32 y)
{
  _y = y;
}

Uint32 SubScene::getScreenHeight() const
{
  return _screenHeight;
}

Uint32 SubScene::getWidth() const
{
  return _width;
}

Uint32 SubScene::getHeight() const
{
  return _height;
}

Uint32 SubScene::getX() const
{
  return _x;
}

Uint32 SubScene::getY() const
{
  return _y;
}

std::vector<nge::video::D2::Entity *> *SubScene::getEntities2D()
{
  return &_entities2D;
}

std::vector<nge::video::D3::Entity *> *SubScene::getEntities3D()
{
  return &_entities3D;
}

void SubScene::setCamera3D(nge::video::D3::Camera *cam)
{
  _cam3D = cam;
}

nge::video::D2::Camera *SubScene::getCamera2D()
{
  return &_cam2D;
}

nge::video::D3::Camera *SubScene::getCamera3D()
{
  return _cam3D;
}

