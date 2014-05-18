#pragma once

#include "InputSubscriber.h"

class OgreFramework;

namespace OgreBites
  {
  class SdkCameraMan;
  }

class MonkeyScene : public InputSubscriber
  {
  private:
    OgreFramework&  m_ogre_framework;
    
    std::unique_ptr<OgreBites::SdkCameraMan> mp_camera_man; // basic camera controller

  private:
    void _CreateScene();
    void _CreateColourCubeMesh();

  public:
    MonkeyScene(OgreFramework& i_ogre_framework);
    ~MonkeyScene();

    OgreBites::SdkCameraMan& CameraMan();

  // InputSubscriber
  public:
    virtual bool KeyPressed(const OIS::KeyEvent &keyEventRef) override;
    virtual bool KeyReleased(const OIS::KeyEvent &keyEventRef) override;

    virtual bool MouseMoved(const OIS::MouseEvent &evt) override;
    virtual bool MousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) override;
    virtual bool MouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) override;
  };

//////////////////////////////////////////////////////////////////////////

inline OgreBites::SdkCameraMan& MonkeyScene::CameraMan()
  {
  return *mp_camera_man;
  }