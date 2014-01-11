#include <ngengine/video/scene/scene.h>

using namespace nge;
using namespace nge::scene;

Scene::Scene()
{
  
}
#include <stdio.h>
Scene::~Scene()
{
  Uint32 i, n;

  n = _subscenes.size();

  for(i = 0; i < n; i++) {
    delete _subscenes[i];
  }
}

void Scene::add(SubScene *subscene)
{
  _subscenes.push_back(subscene);
}

void Scene::draw()
{
  Uint32 i, n;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(!glIsEnabled(GL_DEPTH_TEST))
    glEnable(GL_DEPTH_TEST);

  /*glEnable(GL_BLEND);
  glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
  glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);*/
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//  glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

  n = _subscenes.size();

  for(i = 0; i < n; i++) {
    _subscenes[i]->draw();
  }
//  glDisable(GL_BLEND);
}

void Scene::updateScreenHeight(Uint32 screenHeight)
{
  Uint32 i, n;

  n = _subscenes.size();

  for(i = 0; i < n; i++) {
    _subscenes[i]->setScreenHeight(screenHeight);
  }
}

std::vector<SubScene *> *Scene::getSubScenes()
{
  return &_subscenes;
}

