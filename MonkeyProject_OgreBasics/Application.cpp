#include "stdafx.h"

#include "Application.h"
#include "OgreFramework.h"
#include "InputManager.h"
#include "InputSubscriber.h"

#include "MonkeyScene.h"

#include "SdkCameraMan.h"

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

  mp_input_manager.reset(new InputManager(*mp_ogre_framework));
  mp_ogre_framework->GetRoot()->addFrameListener(this);
  
  mp_input_manager->AddSubscriber(std::make_shared<Test::DefaultInputListener>(*this));

  m_shutdown = false;
  mp_monkey_scene = std::make_shared<MonkeyScene>(*mp_ogre_framework);
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