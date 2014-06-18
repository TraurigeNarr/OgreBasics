#include "stdafx.h"

#include "Application.h"
#include "InputManager.h"
#include "InputSubscriber.h"
#include "OgreFramework.h"
#include "CEGUIFramework.h"

#include "MonkeyScene.h"

#include "SdkCameraMan.h"

namespace Utilities
  {
  CEGUI::MouseButton ConvertButton(OIS::MouseButtonID buttonID)
    {
    switch (buttonID)
      {
      case OIS::MB_Left:
        return CEGUI::LeftButton;
        break;

      case OIS::MB_Right:
        return CEGUI::RightButton;
        break;

      case OIS::MB_Middle:
        return CEGUI::MiddleButton;
        break;

      default:
        return CEGUI::LeftButton;
        break;
      }
    }
  }

namespace Test
  {
  class DefaultInputListener : public InputSubscriber
    {
    private:
      Application& m_application;
    public:
      DefaultInputListener(Application& i_application)
        : m_application(i_application)
        {        }

      virtual bool KeyReleased(const OIS::KeyEvent &keyEventRef) override
        {
        if (keyEventRef.key == OIS::KC_ESCAPE)
          {
          m_application.Shutdown();
          return true;
          }
        return false;
        }
    };

  class CeguiEventListener : public InputSubscriber
    {
    public:
      virtual bool KeyPressed(const OIS::KeyEvent &keyEventRef) override 
        { 
        CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
        context.injectKeyDown((CEGUI::Key::Scan)keyEventRef.key);
        context.injectChar((CEGUI::Key::Scan)keyEventRef.text);
        return true;
        }

      virtual bool KeyReleased(const OIS::KeyEvent &keyEventRef) override 
        { 
        CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)keyEventRef.key);
        CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(keyEventRef.text);
        return true; 
        }

      virtual bool MouseMoved(const OIS::MouseEvent &evt) override 
        { 
        CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
        context.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
        // Scroll wheel.
        if (evt.state.Z.rel)
          context.injectMouseWheelChange(evt.state.Z.rel / 120.0f);
        return false; 
        }
      virtual bool MousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) override 
        { 
        CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
        context.injectMouseButtonDown(Utilities::ConvertButton(id));
        return false; 
        }
      virtual bool MouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) override 
        {
        CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
        context.injectMouseButtonUp(Utilities::ConvertButton(id));
        return true;
        }
    };

  } // namespace

//////////////////////////////////////////////////////////////////////////

Application::Application()
  {

  }

Application::~Application()
  {
  if (mp_input_manager)
    {
    if (mp_monkey_scene)
      mp_input_manager->RemoveSubscriber(mp_monkey_scene);
    mp_input_manager.reset();
    }

  if (mp_ogre_framework)
    {
    mp_ogre_framework->Release();
    mp_ogre_framework.reset();
    }
  }

void Application::Start()
  {
  mp_ogre_framework.reset(new OgreFramework());
  mp_ogre_framework->Initialize();

  mp_cegui_framework.reset(new CEGUIFramework(*mp_ogre_framework));
  mp_cegui_framework->InitializeCEGUI();

  mp_input_manager.reset(new InputManager(*mp_ogre_framework));
  mp_ogre_framework->GetRoot()->addFrameListener(this);
  
  mp_input_manager->AddSubscriber(std::make_shared<Test::DefaultInputListener>(*this));
  mp_input_manager->AddSubscriber(std::make_shared<Test::CeguiEventListener>());

  m_shutdown = false;
  mp_monkey_scene = std::make_shared<MonkeyScene>(*mp_ogre_framework, *this);
  mp_input_manager->AddSubscriber(mp_monkey_scene);
  //start rendering
  mp_ogre_framework->GetRoot()->startRendering();
  }

void Application::Shutdown()
  {
  m_shutdown = true;
  }

bool Application::frameRenderingQueued(const Ogre::FrameEvent& evt)
  {
  if(m_shutdown)
    return false;
  float sleepTime = 0.018 - evt.timeSinceLastFrame;
  sleepTime *= 1000.0f;
  if(0 < sleepTime)
    Sleep(sleepTime);

  mp_monkey_scene->CameraMan().frameRenderingQueued(evt);

  mp_input_manager->Update(evt.timeSinceLastFrame);
  return true;
  }