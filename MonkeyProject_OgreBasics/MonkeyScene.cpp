#include "stdafx.h"

#include "MonkeyScene.h"
#include "Application.h"
#include "OgreFramework.h"
#include "CEGUIFramework.h"

#include <SdkCameraMan.h>

//////////////////////////////////////////////////////////////////////////

enum class UICommand : unsigned int
  {
  UC_EXIT
  };

//////////////////////////////////////////////////////////////////////////

MonkeyScene::MonkeyScene(OgreFramework& i_ogre_framework, Application& i_application)
  : m_ogre_framework(i_ogre_framework)
  , m_application(i_application)
  , mp_camera_man(nullptr)
  {
  _CreateColourCubeMesh();
  _CreateScene();
  }

MonkeyScene::~MonkeyScene()
  {
  // destroy CEGUI windows no exit from scene
  CEGUI::WindowManager::getSingletonPtr()->destroyWindow(mp_root_ui_window);
  CEGUI::WindowManager::getSingletonPtr()->destroyAllWindows();
  }

/*
void _CreateTriangleMesh()
  {
  static bool initialized = false;
  if (initialized)
    return;
  initialized = true;

  /// Create the mesh via the MeshManager
  MeshPtr msh = MeshManager::getSingleton().createManual("ColourCube", "General");

  /// Create one submesh
  SubMesh* sub = msh->createSubMesh();
  
  const float sqrt13 = 0.577350269f; / * sqrt(1/3) * /
  /// Define the vertices (8 vertices, each consisting of 2 groups of 3 floats
  const size_t nVertices = 3;
  const size_t vbufCount = 3*2*nVertices;
  float vertices[vbufCount] = {
    -100.0,100.0,-100.0,        //0 position
    -sqrt13,sqrt13,-sqrt13,     //0 normal
    100.0,100.0,-100.0,         //1 position
    sqrt13,sqrt13,-sqrt13,      //1 normal
    100.0,-100.0,-100.0,        //2 position
    sqrt13,-sqrt13,-sqrt13,     //2 normal
    -100.0,-100.0,-100.0,       //3 position
    -sqrt13,-sqrt13,-sqrt13,    //3 normal
    -100.0,100.0,100.0,         //4 position
    -sqrt13,sqrt13,sqrt13,      //4 normal
    100.0,100.0,100.0,          //5 position
    sqrt13,sqrt13,sqrt13,       //5 normal
    100.0,-100.0,100.0,         //6 position
    sqrt13,-sqrt13,sqrt13,      //6 normal
    -100.0,-100.0,100.0,        //7 position
    -sqrt13,-sqrt13,sqrt13,     //7 normal
    };

  RenderSystem* rs = Root::getSingleton().getRenderSystem();
  RGBA colours[nVertices];
  RGBA *pColour = colours;
  // Use render system to convert colour value since colour packing varies
  rs->convertColourValue(ColourValue(1.0,0.0,0.0), pColour++); //0 colour
  rs->convertColourValue(ColourValue(1.0,1.0,0.0), pColour++); //1 colour
  rs->convertColourValue(ColourValue(0.0,1.0,0.0), pColour++); //2 colour

  /// Define 12 triangles (two triangles per cube face)
  /// The values in this table refer to vertices in the above table
  const size_t ibufCount = 36;
  unsigned short faces[ibufCount] = {
    0,2,3,
    0,1,2,
    1,6,2,
    1,5,6,
    4,6,5,
    4,7,6,
    0,7,4,
    0,3,7,
    0,5,1,
    0,4,5,
    2,7,3,
    2,6,7
    };

  /// Create vertex data structure for 8 vertices shared between submeshes
  msh->sharedVertexData = new VertexData();
  msh->sharedVertexData->vertexCount = nVertices;

  /// Create declaration (memory format) of vertex data
  VertexDeclaration* decl = msh->sharedVertexData->vertexDeclaration;
  size_t offset = 0;
  // 1st buffer
  decl->addElement(0, offset, VET_FLOAT3, VES_POSITION);
  offset += VertexElement::getTypeSize(VET_FLOAT3);
  decl->addElement(0, offset, VET_FLOAT3, VES_NORMAL);
  offset += VertexElement::getTypeSize(VET_FLOAT3);
  /// Allocate vertex buffer of the requested number of vertices (vertexCount) 
  /// and bytes per vertex (offset)
  HardwareVertexBufferSharedPtr vbuf = 
    HardwareBufferManager::getSingleton().createVertexBuffer(
    offset, msh->sharedVertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY);
  /// Upload the vertex data to the card
  vbuf->writeData(0, vbuf->getSizeInBytes(), vertices, true);

  /// Set vertex buffer binding so buffer 0 is bound to our vertex buffer
  VertexBufferBinding* bind = msh->sharedVertexData->vertexBufferBinding; 
  bind->setBinding(0, vbuf);

  // 2nd buffer
  offset = 0;
  decl->addElement(1, offset, VET_COLOUR, VES_DIFFUSE);
  offset += VertexElement::getTypeSize(VET_COLOUR);
  /// Allocate vertex buffer of the requested number of vertices (vertexCount) 
  /// and bytes per vertex (offset)
  vbuf = HardwareBufferManager::getSingleton().createVertexBuffer(
    offset, msh->sharedVertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY);
  /// Upload the vertex data to the card
  vbuf->writeData(0, vbuf->getSizeInBytes(), colours, true);

  /// Set vertex buffer binding so buffer 1 is bound to our colour buffer
  bind->setBinding(1, vbuf);

  /// Allocate index buffer of the requested number of vertices (ibufCount) 
  HardwareIndexBufferSharedPtr ibuf = HardwareBufferManager::getSingleton().
    createIndexBuffer(
    HardwareIndexBuffer::IT_16BIT, 
    ibufCount, 
    HardwareBuffer::HBU_STATIC_WRITE_ONLY);

  /// Upload the index data to the card
  ibuf->writeData(0, ibuf->getSizeInBytes(), faces, true);

  /// Set parameters of the submesh
  sub->useSharedVertices = true;
  sub->indexData->indexBuffer = ibuf;
  sub->indexData->indexCount = ibufCount;
  sub->indexData->indexStart = 0;

  /// Set bounding information (for culling)
  msh->_setBounds(AxisAlignedBox(-100,-100,-100,100,100,100));
  msh->_setBoundingSphereRadius(Math::Sqrt(3*100*100));

  /// Notify -Mesh object that it has been loaded
  msh->load();
  }*/

void MonkeyScene::_CreateColourCubeMesh()
  {
  static bool initialized = false;
  if (initialized)
    return;
  initialized = true;
  using namespace Ogre;
  /// Create the mesh via the MeshManager
  MeshPtr msh = MeshManager::getSingleton().createManual("ColourCube", "General");

  /// Create one submesh
  SubMesh* sub = msh->createSubMesh();

  const float sqrt13 = 0.577350269f; /* sqrt(1/3) */

  /// Define the vertices (8 vertices, each consisting of 2 groups of 3 floats
  const size_t nVertices = 8;
  const size_t vbufCount = 3*2*nVertices;

  float vertices[vbufCount] = {
    -100.0,100.0,-100.0,        //0 position
    -sqrt13,sqrt13,-sqrt13,     //0 normal
    100.0,100.0,-100.0,         //1 position
    sqrt13,sqrt13,-sqrt13,      //1 normal
    100.0,-100.0,-100.0,        //2 position
    sqrt13,-sqrt13,-sqrt13,     //2 normal
    -100.0,-100.0,-100.0,       //3 position
    -sqrt13,-sqrt13,-sqrt13,    //3 normal
    -100.0,100.0,100.0,         //4 position
    -sqrt13,sqrt13,sqrt13,      //4 normal
    100.0,100.0,100.0,          //5 position
    sqrt13,sqrt13,sqrt13,       //5 normal
    100.0,-100.0,100.0,         //6 position
    sqrt13,-sqrt13,sqrt13,      //6 normal
    -100.0,-100.0,100.0,        //7 position
    -sqrt13,-sqrt13,sqrt13,     //7 normal
    };

  RenderSystem* rs = Root::getSingleton().getRenderSystem();
  RGBA colours[nVertices];
  RGBA *pColour = colours;
  // Use render system to convert colour value since colour packing varies
  rs->convertColourValue(ColourValue(1.0,0.0,0.0), pColour++); //0 colour
  rs->convertColourValue(ColourValue(1.0,1.0,0.0), pColour++); //1 colour
  rs->convertColourValue(ColourValue(0.0,1.0,0.0), pColour++); //2 colour
  rs->convertColourValue(ColourValue(0.0,0.0,0.0), pColour++); //3 colour
  rs->convertColourValue(ColourValue(1.0,0.0,1.0), pColour++); //4 colour
  rs->convertColourValue(ColourValue(1.0,1.0,1.0), pColour++); //5 colour
  rs->convertColourValue(ColourValue(0.0,1.0,1.0), pColour++); //6 colour
  rs->convertColourValue(ColourValue(0.0,0.0,1.0), pColour++); //7 colour

  /// Define 12 triangles (two triangles per cube face)
  /// The values in this table refer to vertices in the above table
  const size_t ibufCount = 36;
  unsigned short faces[ibufCount] = {
    0,2,3,
    0,1,2,
    1,6,2,
    1,5,6,
    4,6,5,
    4,7,6,
    0,7,4,
    0,3,7,
    0,5,1,
    0,4,5,
    2,7,3,
    2,6,7
    };

  /// Create vertex data structure for 8 vertices shared between submeshes
  msh->sharedVertexData = new VertexData();
  msh->sharedVertexData->vertexCount = nVertices;

  /// Create declaration (memory format) of vertex data
  VertexDeclaration* decl = msh->sharedVertexData->vertexDeclaration;
  size_t offset = 0;
  // 1st buffer
  decl->addElement(0, offset, VET_FLOAT3, VES_POSITION);
  offset += VertexElement::getTypeSize(VET_FLOAT3);
  decl->addElement(0, offset, VET_FLOAT3, VES_NORMAL);
  offset += VertexElement::getTypeSize(VET_FLOAT3);
  /// Allocate vertex buffer of the requested number of vertices (vertexCount) 
  /// and bytes per vertex (offset)
  HardwareVertexBufferSharedPtr vbuf = 
    HardwareBufferManager::getSingleton().createVertexBuffer(
    offset, msh->sharedVertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY);
  /// Upload the vertex data to the card
  vbuf->writeData(0, vbuf->getSizeInBytes(), vertices, true);

  /// Set vertex buffer binding so buffer 0 is bound to our vertex buffer
  VertexBufferBinding* bind = msh->sharedVertexData->vertexBufferBinding; 
  bind->setBinding(0, vbuf);

  // 2nd buffer
  offset = 0;
  decl->addElement(1, offset, VET_COLOUR, VES_DIFFUSE);
  offset += VertexElement::getTypeSize(VET_COLOUR);
  /// Allocate vertex buffer of the requested number of vertices (vertexCount) 
  /// and bytes per vertex (offset)
  vbuf = HardwareBufferManager::getSingleton().createVertexBuffer(
    offset, msh->sharedVertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY);
  /// Upload the vertex data to the card
  vbuf->writeData(0, vbuf->getSizeInBytes(), colours, true);

  /// Set vertex buffer binding so buffer 1 is bound to our colour buffer
  bind->setBinding(1, vbuf);

  /// Allocate index buffer of the requested number of vertices (ibufCount) 
  HardwareIndexBufferSharedPtr ibuf = HardwareBufferManager::getSingleton().
    createIndexBuffer(
    HardwareIndexBuffer::IT_16BIT, 
    ibufCount, 
    HardwareBuffer::HBU_STATIC_WRITE_ONLY);

  /// Upload the index data to the card
  ibuf->writeData(0, ibuf->getSizeInBytes(), faces, true);

  /// Set parameters of the submesh
  sub->useSharedVertices = true;
  sub->indexData->indexBuffer = ibuf;
  sub->indexData->indexCount = ibufCount;
  sub->indexData->indexStart = 0;

  /// Set bounding information (for culling)
  msh->_setBounds(AxisAlignedBox(-100,-100,-100,100,100,100));
  msh->_setBoundingSphereRadius(Math::Sqrt(3*100*100));

  /// Notify -Mesh object that it has been loaded
  msh->load();

 /* MaterialPtr material = MaterialManager::getSingleton().create(
    "Test/ColourTest", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  material->getTechnique(0)->getPass(0)->setVertexColourTracking(TVC_AMBIENT);*/
  }

void MonkeyScene::_CreateScene()
  {
  Ogre::SceneManager* p_scene_manager = m_ogre_framework.CreateSceneManager(Ogre::ST_GENERIC, "MonkeySceneManager");
  p_scene_manager->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

  Ogre::Camera* p_camera = m_ogre_framework.CreateCamera("MonkeyCamera");
  p_camera->setPosition(Ogre::Vector3(0, 0, 80));
  p_camera->lookAt(Ogre::Vector3(0, 0, -300));
  p_camera->setNearClipDistance(5);

  mp_camera_man.reset(new OgreBites::SdkCameraMan(p_camera));
  mp_camera_man->setStyle(OgreBites::CS_FREELOOK);
  mp_camera_man->setTopSpeed(100);

  m_ogre_framework.GetViewport()->setCamera(p_camera);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
  // Create a Light and set its position
  Ogre::Light* p_light = p_scene_manager->createLight("MainLight");
  p_light->setPosition(20.0f, 80.0f, 50.0f);
  
  p_light = p_scene_manager->createLight("MainLight_Back");
  p_light->setPosition(20.0f, 80.0f, -50.0f);

  // Create an Entity
  Ogre::Entity* p_ogre_head = p_scene_manager->createEntity("Head", "ogrehead.mesh");

  // Create a SceneNode and attach the Entity to it
  Ogre::SceneNode* p_head_node = p_scene_manager->getRootSceneNode()->createChildSceneNode("HeadNode");
  p_head_node->attachObject(p_ogre_head);
  p_head_node->yaw(Ogre::Degree(-90));
  //////////////////////////////////////////////////////////////////////////
  // custom cube
  
  Ogre::Entity* p_cube_entity = p_scene_manager->createEntity("cc", "ColourCube");
  p_cube_entity->setMaterialName("Test/ColourTest");
  Ogre::SceneNode* p_cube_node = p_scene_manager->getRootSceneNode()->createChildSceneNode();
  p_cube_node->setPosition(-35, 0, 0);
  p_cube_node->attachObject(p_cube_entity);

  p_cube_node->setInheritScale(true);
  p_cube_node->setScale(Ogre::Vector3(0.1f, 0.1f, 0.1f));
  
  _InitializeUI();
  }

void MonkeyScene::_InitializeUI()
  {
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage("TaharezLook/MouseArrow");
  CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
  mp_root_ui_window = wmgr.createWindow("DefaultWindow", "MenuScreen");

  CEGUI::Window* p_exit_button = wmgr.createWindow("TaharezLook/Button");
  p_exit_button->setSize(CEGUI::USize(CEGUI::UDim(0.15f, 0), CEGUI::UDim(0.05f, 0)));
  p_exit_button->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1f/*relational to screen*/, 0/*pixel mode*/), 
                          CEGUI::UDim(0.1f,0)));
  p_exit_button->setText("Exit");
  p_exit_button->setID(static_cast<CEGUI::uint>(UICommand::UC_EXIT));

  p_exit_button->subscribeEvent(CEGUI::PushButton::EventClicked,
    CEGUI::Event::Subscriber(&MonkeyScene::ButtonHandler, this));

  mp_root_ui_window->addChild(p_exit_button);

  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mp_root_ui_window);
  }

//////////////////////////////////////////////////////////////////////////

bool MonkeyScene::KeyPressed(const OIS::KeyEvent &keyEventRef)
  {
  mp_camera_man->injectKeyDown(keyEventRef);
  return true;
  }

bool MonkeyScene::KeyReleased(const OIS::KeyEvent &keyEventRef) 
  {
  mp_camera_man->injectKeyUp(keyEventRef);
  return true;
  }

bool MonkeyScene::MouseMoved(const OIS::MouseEvent &evt) 
  {
  mp_camera_man->injectMouseMove(evt);
  return true;
  }

bool MonkeyScene::MousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) 
  {
  mp_camera_man->injectMouseDown(evt, id);
  return true;
  }

bool MonkeyScene::MouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) 
  {
  mp_camera_man->injectMouseUp(evt, id);
  return true;
  }

bool MonkeyScene::ButtonHandler(const CEGUI::EventArgs &e)
  {
  const CEGUI::WindowEventArgs* args = static_cast<const CEGUI::WindowEventArgs*>(&e);
  UICommand ui_command = static_cast<UICommand>(args->window->getID());
  switch (ui_command)
    {
    case UICommand::UC_EXIT:
      m_application.Shutdown();
      break;
    }
  return true;
  }