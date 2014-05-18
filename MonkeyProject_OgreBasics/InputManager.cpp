#include "stdafx.h"
#include "InputManager.h"
#include "InputSubscriber.h"

#include "OgreFramework.h"

#include <algorithm>

//////////////////////////////////////////////////////////////////////////

InputManager::InputManager(OgreFramework& i_ogre_framework)
  : m_ogre_framework(i_ogre_framework)
  {
  m_ogre_framework.GetKeyboard()->setEventCallback(this);
  m_ogre_framework.GetMouse()->setEventCallback(this);
  }

InputManager::~InputManager()
  {
  }

void InputManager::Update(float ElapsedTime)
  {
	m_ogre_framework.GetKeyboard()->capture();
	m_ogre_framework.GetMouse()->capture();
  }

/************************************************************************/
/*                      Event handlers                                  */
/************************************************************************/
bool InputManager::keyPressed(const OIS::KeyEvent &keyEventRef)
  {
	std::for_each(m_subscribers.begin(), m_subscribers.end(), [&keyEventRef](InputSubscriberPtr subsriber)
		{
			subsriber->KeyPressed(keyEventRef);
	});
	return true;
  }

bool InputManager::keyReleased(const OIS::KeyEvent &keyEventRef)
  {
	std::for_each(m_subscribers.begin(), m_subscribers.end(), [&keyEventRef](InputSubscriberPtr subsriber)
	{
		subsriber->KeyReleased(keyEventRef);
	});
	return true;
  }

bool InputManager::mouseMoved(const OIS::MouseEvent &evt)
  {
	std::for_each(m_subscribers.begin(), m_subscribers.end(), [&evt](InputSubscriberPtr subsriber)
	{
		subsriber->MouseMoved(evt);
	});
	return true;
  }

bool InputManager::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
  {
	std::for_each(m_subscribers.begin(), m_subscribers.end(), [&evt, id](InputSubscriberPtr subsriber)
	{
		subsriber->MousePressed(evt, id);
	});
	return true;
  }

bool InputManager::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
  {
	std::for_each(m_subscribers.begin(), m_subscribers.end(), [&evt, id](InputSubscriberPtr subsriber)
	  {
		subsriber->MouseReleased(evt, id);
	  });
	return true;
  }

void InputManager::AddSubscriber(InputSubscriberPtr subscriber)
  {
	if(m_subscribers.end() == std::find(m_subscribers.begin(), m_subscribers.end(), subscriber))
		m_subscribers.push_back(subscriber);
  }

void InputManager::RemoveSubscriber(InputSubscriberPtr subscriber)
  {
	std::vector<InputSubscriberPtr>::iterator iterFind = std::find(m_subscribers.begin(), m_subscribers.end(), subscriber);
	if(m_subscribers.end() != iterFind)
		m_subscribers.erase(iterFind);
  }