#pragma once

#include <CEGUI\CEGUI.h>
#include <CEGUI\RendererModules/Ogre/Renderer.h>
#include <CEGUI\ResourceProvider.h>

class OgreFramework;

class CEGUIFramework
  {
  private:
    CEGUI::OgreRenderer*  mp_renderer;
    OgreFramework&        m_ogre_framework;
  public:
	  CEGUIFramework(OgreFramework& i_ogre_framework);
	  ~CEGUIFramework(void);

	  bool InitializeCEGUI();
	
  private:
	  bool initialiseResourceGroupDirectories();
	  void initialiseDefaultResourceGroups();
	  void destroy();
  };