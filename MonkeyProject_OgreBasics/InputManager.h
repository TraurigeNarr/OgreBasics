#pragma once

#include <OIS.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

class OgreFramework;
class InputSubscriber;

class InputManager 
            : public OIS::MouseListener
            , public OIS::KeyListener 
  {
  private:
    std::vector<std::shared_ptr<InputSubscriber>> m_subscribers;
    OgreFramework&                                m_ogre_framework;

  public:
	  InputManager(OgreFramework& i_ogre_framework);
	  ~InputManager();

	  void Update(float ElapsedTime);

	  bool keyPressed(const OIS::KeyEvent &keyEventRef);
	  bool keyReleased(const OIS::KeyEvent &keyEventRef);

	  bool mouseMoved(const OIS::MouseEvent &evt);
	  bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	  bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	  void AddSubscriber(std::shared_ptr<InputSubscriber> subscriber);
	  void RemoveSubscriber(std::shared_ptr<InputSubscriber> subscriber);
	  const std::vector<std::shared_ptr<InputSubscriber>>& GetSubscribers() const { return m_subscribers; }
  };