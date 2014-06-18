#include "stdafx.h"
#include "CEGUIFramework.h"

#include "OgreFramework.h"

#include <OgreRenderTarget.h>

const int PATH_MAX = 255;

namespace
  {
  const std::string LogPath        = ".\\CeguiLog.log";
  }

CEGUIFramework::CEGUIFramework(OgreFramework& i_ogre_framework)
  : m_ogre_framework(i_ogre_framework)
  , mp_renderer(nullptr)
{
}


CEGUIFramework::~CEGUIFramework(void)
  {
  // if uncomment this -> crash on exit
  // it is a memory leak and if you resolve this give me a note ;)
	/*if(mp_renderer)
		CEGUI::OgreRenderer::destroySystem();*/
  }

bool CEGUIFramework::InitializeCEGUI()
{
	try
	  {
    new CEGUI::DefaultLogger();
    
		Ogre::RenderTarget *rendTarget = m_ogre_framework.GetRenderTarget();
		mp_renderer = &CEGUI::OgreRenderer::bootstrapSystem(*rendTarget);
    CEGUI::Logger::getSingletonPtr()->setLogFilename(LogPath);
    initialiseDefaultResourceGroups();
	  }
	catch (std::exception& e)
	  {
    mp_renderer = nullptr;
		MessageBoxA(NULL, e.what(), "Raw initialization!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	  }

	try
	{
    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
		
		//initialize tooltips
    CEGUI::GUIContext& default_context = CEGUI::System::getSingleton().getDefaultGUIContext();
    default_context.setDefaultTooltipType("TaharezLook/Tooltip"); // Set the name of the default tooltip
		CEGUI::Tooltip* tooltip = default_context.getDefaultTooltipObject();
		if(0 != tooltip)
		{
			tooltip->setHoverTime(0.02f); // Display the tooltip after the mouse has been hovering over the widget
			tooltip->setDisplayTime(15.0f); // Display for 15 seconds then disappear
		}
	}
	catch (CEGUI::Exception& e)
	{
		MessageBoxA(NULL, e.what(), "An exception has occurred while initializing CEGUI!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		// something went wrong - probably did not load the imageset first!
		//TODO: Handle error,
	}
	return true;
}

bool CEGUIFramework::initialiseResourceGroupDirectories()
{
	CEGUI::DefaultResourceProvider* rp =
		static_cast<CEGUI::DefaultResourceProvider*>
		(CEGUI::System::getSingleton().getResourceProvider());

	/*const char* dataPathPrefix = FileUtilities::GetApplicationDirectory().c_str();

	try
	{
    std::string path = FileUtilities::JoinPath(FileUtilities::GetApplicationDirectory(), "Client\\Media\\CEGUI\\layouts");
		rp->setResourceGroupDirectory("Layouts", path.c_str());
	}
	catch (...)
	{
		return false;
	}*/
	return true;
}


void CEGUIFramework::initialiseDefaultResourceGroups()
{
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
}