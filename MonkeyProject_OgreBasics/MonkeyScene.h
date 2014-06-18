#pragma once

#include "InputSubscriber.h"

class Application;
class OgreFramework;

namespace OgreBites
  {
  class SdkCameraMan;
  }

namespace CEGUI
  {
  class Window;
  class EventArgs;
  }

class MonkeyScene : public InputSubscriber
  {
  private:
    OgreFramework&  m_ogre_framework;
    Application&    m_application;
    std::unique_ptr<OgreBites::SdkCameraMan> mp_camera_man; // basic camera controller

    CEGUI::Window* mp_root_ui_window;

  private:
    void _CreateScene();
    void _CreateColourCubeMesh();
    // normally this should be another class and another system that will
    // manage UI
    void _InitializeUI();

  public:
    MonkeyScene(OgreFramework& i_ogre_framework, Application& i_application);
    ~MonkeyScene();

    OgreBites::SdkCameraMan& CameraMan();

  // InputSubscriber
  public:
    virtual bool KeyPressed(const OIS::KeyEvent &keyEventRef) override;
    virtual bool KeyReleased(const OIS::KeyEvent &keyEventRef) override;

    virtual bool MouseMoved(const OIS::MouseEvent &evt) override;
    virtual bool MousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) override;
    virtual bool MouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) override;

    bool         ButtonHandler(const CEGUI::EventArgs &e);
  };

//////////////////////////////////////////////////////////////////////////

inline OgreBites::SdkCameraMan& MonkeyScene::CameraMan()
  {
  return *mp_camera_man;
  }