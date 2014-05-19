#pragma once

#pragma warning( disable : 4251 )
#pragma warning( disable : 4193 )
#pragma warning( disable : 4275 )

#include <OgreConfigFile.h>
#include <OgreLogManager.h>
#include <Overlay\OgreOverlay.h>
#include <Overlay\OgreOverlayElement.h>
#include <Overlay\OgreOverlayManager.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreViewport.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <SdkTrays.h>

typedef Ogre::NameValuePairList Options;

class OgreFramework : public Ogre::WindowEventListener
  {
  private:
    std::unique_ptr<Ogre::Root> mp_root;
    Ogre::RenderWindow*			    mp_render_window;
    Ogre::Viewport*				      mp_viewport;
    Ogre::Log*					        mp_log;

    OIS::InputManager*			    mp_input_manager;
    OIS::Keyboard*				      mp_keyboard;
    OIS::Mouse*					        mp_mouse;

    Ogre::SceneManager*			    mp_scene_manager;
    Ogre::Camera*               mp_camera;
    bool                        m_show_fps;

  private:
    void    _InitializeLogFile();
    void    _InitializeReources();
    void    _InitializeRenderSystem();
    void    _InitializeRenderWindow();
    void    _InitializeViewport();
    void    _InitializeInput();
    Options _DefaultOptions();
    void    _ClearCurrentScene();

  public:
    OgreFramework();
    ~OgreFramework();

    void Initialize();
    void Release();

    Ogre::SceneManager* CreateSceneManager(Ogre::SceneTypeMask i_mask, const std::string& i_name /* = "" */);
    Ogre::Camera*       CreateCamera(const std::string& i_name = "");

    Ogre::Root*     GetRoot();
    OIS::Keyboard*  GetKeyboard();
    OIS::Mouse*     GetMouse();
    Ogre::Viewport* GetViewport();

  // Ogre::WindowEventListener
  public:
    virtual void windowResized(Ogre::RenderWindow* rw) override;
    virtual bool windowClosing(Ogre::RenderWindow* rw) override;
  };

//////////////////////////////////////////////////////////////////////////

inline Ogre::Root* OgreFramework::GetRoot()
  {
  return mp_root.get();
  }

inline OIS::Keyboard* OgreFramework::GetKeyboard()
  {
  return mp_keyboard;
  }

inline OIS::Mouse* OgreFramework::GetMouse()
  {
  return mp_mouse;
  }

inline Ogre::Viewport* OgreFramework::GetViewport()
  {
  return mp_viewport;
  }