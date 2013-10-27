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

  _cam2D.setX(-100);
	_cam2D.setY(-100);
	_cam2D.setWidth(width);
	_cam2D.setHeight(height);
  _cam2D.setFrameSize(width, height);

  _cam3D = nullptr;
}

SubScene::~SubScene()
{
  
}

void SubScene::add(entity::Entity *entity)
{
  _entities2D.push_back(entity);
}

void SubScene::add(video::D3::entity::Entity *entity)
{
  _entities3D.push_back(entity);
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(_cam3D->getFovy(),
                   _cam3D->getAspect(), 
                   _cam3D->getZNear(), 
                   _cam3D->getZFar());
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(_cam3D) {
 
      glm::vec3 *pos, *target, *normal;

      pos = _cam3D->getPosition();
      target = _cam3D->getTarget();
      normal = _cam3D->getNormal();

      gluLookAt((*pos)[0], 
                (*pos)[1],
                (*pos)[2],
                (*target)[0], 
                (*target)[1],
                (*target)[2],
                (*normal)[0], 
                (*normal)[1],
                (*normal)[2]);
    }
    else
      gluLookAt(3,4,2,0,0,0,0,0,1);

  /*  glBegin(GL_QUADS);
 
    glColor3ub(255,0,0); //face rouge
    glVertex3d(1,1,1);
    glVertex3d(1,1,-1);
    glVertex3d(-1,1,-1);
    glVertex3d(-1,1,1);
 
    glColor3ub(0,255,0); //face verte
    glVertex3d(1,-1,1);
    glVertex3d(1,-1,-1);
    glVertex3d(1,1,-1);
    glVertex3d(1,1,1);
 
    glColor3ub(0,0,255); //face bleue
    glVertex3d(-1,-1,1);
    glVertex3d(-1,-1,-1);
    glVertex3d(1,-1,-1);
    glVertex3d(1,-1,1);
 
    glEnd();
*/
    n = _entities3D.size();

    for(i = 0; i < n; i++) {
      _entities3D[i]->draw();
    }
  }

  glEnable(GL_TEXTURE_2D);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glClear(GL_DEPTH_BUFFER_BIT);

  gluOrtho2D((GLdouble) _cam2D.getX() - 1, 
		  	     (GLdouble)(_cam2D.getWidth() + _cam2D.getX() - 1), 
		  		   (GLdouble)(_cam2D.getHeight() + _cam2D.getY() - 1), 
		  		   (GLdouble) _cam2D.getY() - 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  n = _entities2D.size();

  for(i = 0; i < n; i++) {
    _entities2D[i]->draw();
  }
}

/*void SubScene::draw()
{
  int i, n;

  glViewport(
    (GLint) _x, 
    _screenHeight - ((GLint) _y) - _height, 
    (GLsizei) _width, 
    (GLsizei) _height
  );

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D((GLdouble) _cam2D.getX() - 1, 
		  	     (GLdouble)(_cam2D.getWidth() + _cam2D.getX() - 1), 
		  		   (GLdouble)(_cam2D.getHeight() + _cam2D.getY() - 1), 
		  		   (GLdouble) _cam2D.getY() - 1);

  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  n = _entities2D.size();

  for(i = 0; i < n; i++) {
    _entities2D[i]->draw();
  }
}*/

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

std::vector<entity::Entity *> *SubScene::getEntities()
{
  return &_entities2D;
}

void SubScene::setCamera3D(nge::video::D3::Camera *cam)
{
  _cam3D = cam;
}

camera::Camera *SubScene::getCamera2D()
{
  return &_cam2D;
}

nge::video::D3::Camera *SubScene::getCamera3D()
{
  return _cam3D;
}

