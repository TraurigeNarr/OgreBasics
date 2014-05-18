#include "stdafx.h"

#include "MonkeyScene.h"
#include "OgreFramework.h"

#include <SdkCameraMan.h>

MonkeyScene::MonkeyScene(OgreFramework& i_ogre_framework)
  : m_ogre_framework(i_ogre_framework)
  , mp_camera_man(nullptr)
  {
  _CreateScene();
  }

MonkeyScene::~MonkeyScene()
  {

  }

void MonkeyScene::_CreateScene()
  {
  Ogre::SceneManager* p_scene_manager = m_ogre_framework.CreateSceneManager(Ogre::ST_GENERIC, "MonkeySceneManager");
  p_scene_manager->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

  Ogre::Camera* p_camera = m_ogre_framework.CreateCamera("MonkeyCamera");
  p_camera->setPosition(Ogre::Vector3(0, 0, 80));
  p_camera->lookAt(Ogre::Vector3(0, 0, -300));
  p_camera->setNearClipDistance(5);

  mp_camera_man.reset(new OgreBites::SdkCameraMan(p_camera));
  mp_camera_man->setStyle(OgreBites::CS_FREELOOK);
  mp_camera_man->setTopSpeed(100);

  m_ogre_framework.GetViewport()->setCamera(p_camera);

  // Create a Light and set its position
  Ogre::Light* p_light = p_scene_manager->createLight("MainLight");
  p_light->setPosition(20.0f, 80.0f, 50.0f);

  // Create an Entity
  Ogre::Entity* p_ogre_head = p_scene_manager->createEntity("Head", "ogrehead.mesh");

  // Create a SceneNode and attach the Entity to it
  Ogre::SceneNode* p_head_node = p_scene_manager->getRootSceneNode()->createChildSceneNode("HeadNode");
  p_head_node->attachObject(p_ogre_head);
  }

bool MonkeyScene::KeyPressed(const OIS::KeyEvent &keyEventRef)
  {
  mp_camera_man->injectKeyDown(keyEventRef);
  return true;
  }

bool MonkeyScene::KeyReleased(const OIS::KeyEvent &keyEventRef) 
  {
  mp_camera_man->injectKeyUp(keyEventRef);
  return true;
  }

bool MonkeyScene::MouseMoved(const OIS::MouseEvent &evt) 
  {
  mp_camera_man->injectMouseMove(evt);
  return true;
  }

bool MonkeyScene::MousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) 
  {
  mp_camera_man->injectMouseDown(evt, id);
  return true;
  }

bool MonkeyScene::MouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) 
  {
  mp_camera_man->injectMouseUp(evt, id);
  return true;
  }