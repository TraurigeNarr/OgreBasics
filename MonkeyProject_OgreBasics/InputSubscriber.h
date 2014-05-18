#pragma once

#include <OISKeyboard.h>
#include <OISMouse.h>

class InputSubscriber
{
public:
  virtual ~InputSubscriber(){}
	virtual bool KeyPressed(const OIS::KeyEvent &keyEventRef) { return false; }
	virtual bool KeyReleased(const OIS::KeyEvent &keyEventRef) { return false; }

	virtual bool MouseMoved(const OIS::MouseEvent &evt) { return false; }
	virtual bool MousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) { return false; }
	virtual bool MouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) { return false; }
};

typedef std::shared_ptr<InputSubscriber> InputSubscriberPtr;