// llgs-engine
// Copyright (c) 2013 Kalman Kiss, Zalaegerszeg Hungary
// All rights reserved.
// kiskami@freemail.hu
//

#include "stdafx.h"

#include "LLGSEngine.h"

#include "OGRE\Ogre.h"

#include "Bullet\btBulletCollisionCommon.h"

#include <functional>
#include <locale>

#include "InputHandler.h"

#include "llgs-engine.h"

LLGSEngine::~LLGSEngine() {
	r_shutdown();
}

void LLGSEngine::r_init(char *pluginsfile, char *configfile, char *logfile, char *rendersystem, char *resourcesfile) {
	root = new Ogre::Root(pluginsfile, configfile, logfile);
	Ogre::Root::getSingleton().setRenderSystem(Ogre::Root::getSingleton().getRenderSystemByName(rendersystem));
	locateResources(resourcesfile);
	Ogre::Root::getSingleton().initialise(false);
}

void  LLGSEngine::r_shutdown() {
	i_shutdown();
	if(root!=0) {
		Ogre::Root::getSingleton().shutdown();
		root = 0;
		window = 0;
		scenemanager = 0;
		viewport = 0;
	}
}

void LLGSEngine::r_createrenderwindow(char *title, int w, int h, bool fullscreen) {
	if(root!=0) {
		window = Ogre::Root::getSingleton().createRenderWindow(title, w, h, fullscreen);
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
}

void LLGSEngine::r_createscenemanager(char *type, char *name) {
	if(window!=0) {
		Ogre::SceneType sctype = Ogre::ST_GENERIC;
		std::string pt = type;
		std::transform(pt.begin(), pt.end(), pt.begin(), std::bind2nd(std::ptr_fun(&std::toupper<char>), std::locale("")));

		if(pt.compare("EXTERIOR_CLOSE")==0) sctype = Ogre::ST_EXTERIOR_CLOSE;
		if(pt.compare("EXTERIOR_FAR")==0) sctype = Ogre::ST_EXTERIOR_FAR;
		if(pt.compare("EXTERIOR_REAL_FAR")==0) sctype = Ogre::ST_EXTERIOR_REAL_FAR;
		if(pt.compare("INTERIOR")==0) sctype = Ogre::ST_INTERIOR;

 		scenemanager = Ogre::Root::getSingleton().createSceneManager(sctype, name);
	}
}

void *LLGSEngine::r_createcamera(char *name) {
	if(scenemanager!=0) {
		return (void *)scenemanager->createCamera(name);
	}
	return 0;
}

void  LLGSEngine::r_setcamerapos(void *camptr, float x, float y, float z) {
	if(camptr!=0) {
		((Ogre::Camera *)camptr)->setPosition(Ogre::Vector3(x,y,z));
	}
}

void  LLGSEngine::r_movecamerarel(void *camptr, float x, float y, float z) {
	if(camptr!=0) {
		((Ogre::Camera *)camptr)->moveRelative(Ogre::Vector3(x,y,z));
	}
}

void  LLGSEngine::r_cameralookat(void *camptr, float x, float y, float z) {
	if(camptr!=0) {
		((Ogre::Camera *)camptr)->lookAt(Ogre::Vector3(x,y,z));
	}
}

void  LLGSEngine::r_rotatecamerax(void *camptr, float radian) {
	if(camptr!=0) {
		((Ogre::Camera *)camptr)->pitch(Ogre::Radian(radian));
	}
}

void  LLGSEngine::r_rotatecameray(void *camptr, float radian) {
	if(camptr!=0) {
		((Ogre::Camera *)camptr)->yaw(Ogre::Radian(radian));
	}
}

void  LLGSEngine::r_rotatecameraz(void *camptr, float radian) {
	if(camptr!=0) {
		((Ogre::Camera *)camptr)->roll(Ogre::Radian(radian));
	}
}

void  LLGSEngine::r_setcameraneraclipdist(void *camptr, float dist) {
	if(camptr!=0) {
		((Ogre::Camera *)camptr)->setNearClipDistance(dist);
	}
}

void  LLGSEngine::r_setcamerafarclipdist(void *camptr, float dist) {
	if(camptr!=0) {
		((Ogre::Camera *)camptr)->setFarClipDistance(dist);
	}
}

void  LLGSEngine::r_setcameraasviewport(void *camptr) {
	if(window!=0) {
		((Ogre::Camera *)camptr)->setAutoAspectRatio(true);
		viewport = window->addViewport((Ogre::Camera *)camptr);
//		((Ogre::Camera *)camptr)->setAspectRatio(viewport->getActualWidth()/(float)viewport->getActualHeight());
	}
}

void  LLGSEngine::r_setviewportbackground(float r, float g, float b) {
	viewport->setBackgroundColour(Ogre::ColourValue(r,g,b));
}

void  LLGSEngine::r_setambientlight(float r, float g, float b) {
	if(scenemanager!=0) {
		scenemanager->setAmbientLight(Ogre::ColourValue(r,g,b));
	}
}

void  LLGSEngine::r_renderoneframe() {
	if(root!=0) {
		Ogre::Root::getSingleton().renderOneFrame();
	}
}

void  LLGSEngine::r_setskybox(char *materialname) {
	if(scenemanager!=0) {
		scenemanager->setSkyBox(true,materialname);
	}
}

void LLGSEngine::r_screenshottofile(char *basename) {
	if(window!=0) window->writeContentsToTimestampedFile(basename,".png");
}

void LLGSEngine::locateResources(char *resources_cfg) {
	// load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(resources_cfg);

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	Ogre::String sec, type, arch;

	// go through all specified resource groups
	while (seci.hasMoreElements())
	{
		sec = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		// go through all resource paths
		for (i = settings->begin(); i != settings->end(); i++)
		{
			type = i->first;
			arch = i->second;

			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}
}

void *LLGSEngine::t_createtimer() {
	return (void *)new Ogre::Timer();
}

void  LLGSEngine::t_resettimer(void *timerptr) {
	((Ogre::Timer *)timerptr)->reset();
}

unsigned long LLGSEngine::t_gettimermicroseconds(void *timerptr) {
	return ((Ogre::Timer *)timerptr)->getMicroseconds();
}

void  LLGSEngine::i_init() {
	if(window!=0)
		inputhandler = new InputHandler(window);
}

void  LLGSEngine::i_shutdown() {
	if(inputhandler!=0) {
		delete inputhandler;
		inputhandler = 0;
	}
}

void  LLGSEngine::i_captureinput() {
	if(inputhandler!=0)
		inputhandler->i_captureinput();
}

int  LLGSEngine::i_keypressed(int key) {
	if(inputhandler!=0)
		return inputhandler->i_keypressed(key);
	return false;
}

void  LLGSEngine::i_guiinput(bool enable) {
	guiinput_enabled = enable;
}

int  LLGSEngine::i_leftmouse() {
	if(inputhandler!=0)
		return inputhandler->i_leftmouse();
	return false;
}

int  LLGSEngine::i_middlemouse() {
	if(inputhandler!=0)
		return inputhandler->i_middlemouse();
	return false;
}

int  LLGSEngine::i_rightmouse() {
	if(inputhandler!=0)
		return inputhandler->i_rightmouse();
	return false;
}

int   LLGSEngine::i_mousex() {
	if(inputhandler!=0)
		return inputhandler->i_mousex();
	return 0;
}

int   LLGSEngine::i_mousey() {
	if(inputhandler!=0)
		return inputhandler->i_mousey();
	return 0;
}

int   LLGSEngine::i_mouserelx() {
		if(inputhandler!=0)
			return inputhandler->i_mouserelx();
		return 0;
}

int   LLGSEngine::i_mouserely() {
	if(inputhandler!=0)
		return inputhandler->i_mouserely();
	return 0;
}

void  *LLGSEngine::r_simpletextpanel(char *txt, char *fontname, float x, float y, float w, float h) {
	return 0;
}

void  LLGSEngine::r_simpletextsetcolor(void *id, float r, float g, float b) {

}

void  LLGSEngine::r_simpletextshow(void *id) {

}

void  LLGSEngine::r_simpletexthide(void *id) {

}

void  LLGSEngine::r_simpletextsettext(void *id, char *txt) {

}

void *LLGSEngine::r_loadmesh(char *name, char *meshname) {
	if(scenemanager!=0)
		return scenemanager->createEntity(name,meshname);
	return 0;
}

void  LLGSEngine::r_destroymesh(void *entityptr) {
	if(scenemanager!=0)
		scenemanager->destroyEntity(static_cast<Ogre::Entity *>(entityptr));
}

void *LLGSEngine::r_clonemesh(void *entityptr, char *newname) {
	return (void *)(static_cast<Ogre::Entity *>(entityptr)->clone(newname));
}

void LLGSEngine::r_setmeshmaterial(void *entityptr, char *matname) {
	static_cast<Ogre::Entity *>(entityptr)->setMaterialName(matname);
}

void *LLGSEngine::r_createscenenode(char *name) {
	if(scenemanager!=0)
		return scenemanager->createSceneNode(name);
	return 0;
}

void *LLGSEngine::r_getrootscenenode() {
	if(scenemanager!=0)
		return scenemanager->getRootSceneNode();
	return 0;
}

void  LLGSEngine::r_destroyscenenode(void *nodeptr) {
	if(scenemanager!=0)
		scenemanager->destroySceneNode(static_cast<Ogre::SceneNode *>(nodeptr));
}

void  LLGSEngine::r_setscenenodepos(void *nodeptr, float x, float y, float z) {
	static_cast<Ogre::SceneNode *>(nodeptr)->setPosition(x,y,z);
}

void  LLGSEngine::r_translatescenenode(void *nodeptr, float dx, float dy, float dz) {
	static_cast<Ogre::SceneNode *>(nodeptr)->translate(dx,dy,dz);
}

void  LLGSEngine::r_setscenenodescale(void *nodeptr, float xs, float ys, float zs) {
	static_cast<Ogre::SceneNode *>(nodeptr)->scale(xs,ys,zs);
}

void  LLGSEngine::r_rotatescenenodex(void *nodeptr, float radian) {
	static_cast<Ogre::SceneNode *>(nodeptr)->pitch(Ogre::Radian(radian));
}

void  LLGSEngine::r_rotatescenenodey(void *nodeptr, float radian) {
	static_cast<Ogre::SceneNode *>(nodeptr)->yaw(Ogre::Radian(radian));
}

void  LLGSEngine::r_rotatescenenodez(void *nodeptr, float radian) {
	static_cast<Ogre::SceneNode *>(nodeptr)->roll(Ogre::Radian(radian));
}

void  LLGSEngine::r_attachmoveable(void *nodeptr, void *moveableptr) {
	static_cast<Ogre::SceneNode *>(nodeptr)->attachObject(static_cast<Ogre::MovableObject *>(moveableptr));
}

void  LLGSEngine::r_detachmoveable(void *nodeptr, void *moveableptr) {
	static_cast<Ogre::SceneNode *>(nodeptr)->detachObject(static_cast<Ogre::MovableObject *>(moveableptr));
}

void *LLGSEngine::r_createchildscenenode(void *nodeptr, char *name) {
	return static_cast<Ogre::SceneNode *>(nodeptr)->createChildSceneNode(name);
}

void *LLGSEngine::r_getparentscenenode(void *nodeptr) {
	return static_cast<Ogre::SceneNode *>(nodeptr)->getParentSceneNode();
}

void LLGSEngine::r_addchild(void *nodeptr, void *childptr) {
	static_cast<Ogre::SceneNode *>(nodeptr)->addChild(static_cast<Ogre::SceneNode *>(childptr));
}

void LLGSEngine::r_removechild(void *nodeptr, void *childptr) {
	static_cast<Ogre::SceneNode *>(nodeptr)->removeChild(static_cast<Ogre::SceneNode *>(childptr));
}

void  LLGSEngine::r_setscenenodevis(void *nodeptr, bool visible) {
	static_cast<Ogre::SceneNode *>(nodeptr)->setVisible(visible);
}

void  LLGSEngine::r_setscenenodeuserobj(void *nodeptr, char *key, void *obj) {
	static_cast<Ogre::SceneNode *>(nodeptr)->getUserObjectBindings().setUserAny(key,Ogre::Any(obj));
}

void *LLGSEngine::r_getscenenodeuserobj(void *nodeptr, char *key) {
	return static_cast<Ogre::SceneNode *>(nodeptr)->getUserObjectBindings().getUserAny(key).get<void *>();
}

void  LLGSEngine::r_delscenenodeuserobj(void *nodeptr, char *key) {
	return static_cast<Ogre::SceneNode *>(nodeptr)->getUserObjectBindings().eraseUserAny(key);
}

void *LLGSEngine::r_createpartsys(char *name, char *templ) {
	if(scenemanager!=0)
		return scenemanager->createParticleSystem(name,templ);
	return 0;
}

void  LLGSEngine::r_destroypartsys(void *partsysptr) {
	if(scenemanager!=0)
		return scenemanager->destroyParticleSystem(static_cast<Ogre::ParticleSystem*>(partsysptr));
}

void  LLGSEngine::r_setpartsysemitting(void *partsysptr, bool emit) {
	static_cast<Ogre::ParticleSystem*>(partsysptr)->setEmitting(emit);
}

void  LLGSEngine::r_setpartsysvis(void *partsysptr, bool visible) {
	static_cast<Ogre::ParticleSystem*>(partsysptr)->setVisible(visible);
}

void  LLGSEngine::c_init() {
	auto collisionConfiguration = new btDefaultCollisionConfiguration();
	collisionWorld = new btCollisionWorld(
		new btCollisionDispatcher(collisionConfiguration)
		,new btDbvtBroadphase()
		,collisionConfiguration);
}

void  LLGSEngine::c_shutdown() {
	if(collisionWorld!=0) {
		delete collisionWorld;
		collisionWorld = 0;
	}
}

void  LLGSEngine::c_enabledebugdrawer(bool enable) {
	if(collisionWorld!=0) {
		if(enable)
			collisionWorld->setDebugDrawer(this);
		else
			collisionWorld->setDebugDrawer(0);
	}
}

Ogre::MaterialPtr colldebugmat;

void createManualMat() {
	if(colldebugmat.isNull()) {
		colldebugmat = Ogre::MaterialManager::getSingleton().create("colldebugmat","Common"); 
		colldebugmat->setReceiveShadows(false);
		colldebugmat->getTechnique(0)->setLightingEnabled(true); 
		colldebugmat->getTechnique(0)->getPass(0)->setDiffuse(0,0,1,0); 
		colldebugmat->getTechnique(0)->getPass(0)->setAmbient(0,0,1); 
		colldebugmat->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,1); 
//		colldebugmat.setNull();  // dispose pointer, not the material 
	}
}

void LLGSEngine::drawLine(const btVector3& from,const btVector3& to,const btVector3& color) {
	if(collisionDebugmode!=btIDebugDraw::DBG_NoDebug) {
		Ogre::ManualObject* myManualObject =  scenemanager->createManualObject();
		//	Ogre::SceneNode* myManualObjectNode = scenemanager->getRootSceneNode()->createChildSceneNode("manual1_node"); 

		createManualMat();

		myManualObject->begin("colldebugmat", Ogre::RenderOperation::OT_LINE_LIST); 
		myManualObject->position(from.getX(),from.getY(),from.getZ()); 
		myManualObject->position(to.getX(),to.getY(),to.getZ()); 
		myManualObject->colour(color.getX(),color.getY(),color.getZ());
		myManualObject->end(); 

		scenemanager->getRootSceneNode()->createChildSceneNode()->attachObject(myManualObject);
	}
}

void LLGSEngine::drawContactPoint (const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color) {
	if(collisionDebugmode &  btIDebugDraw::DBG_DrawContactPoints) {
		Ogre::ManualObject* myManualObject =  scenemanager->createManualObject();

		createManualMat();

		myManualObject->begin("manual1Material", Ogre::RenderOperation::OT_POINT_LIST);
		myManualObject->position(PointOnB.getX(),PointOnB.getY(),PointOnB.getZ());
		myManualObject->normal(normalOnB.getX(),normalOnB.getY(),normalOnB.getZ());
		myManualObject->colour(color.getX(),color.getY(),color.getZ());
		myManualObject->end(); 

		scenemanager->getRootSceneNode()->createChildSceneNode()->attachObject(myManualObject);
	}
}

void LLGSEngine::reportErrorWarning (const char *warningString) {
	Ogre::LogManager::getSingleton().logMessage("Bullet message: "+Ogre::String(warningString));
}

void LLGSEngine::draw3dText (const btVector3 &location, const char *textString) {
}

void LLGSEngine::setDebugMode (int debugMode) {
	collisionDebugmode = debugMode;
}

int LLGSEngine::getDebugMode () const {
	return collisionDebugmode;
}

void setCollObjStaticFlag(btCollisionObject *co, int mass) {
	if(mass==0) {
		co->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
	}
}

btCollisionObject *createCollisionObject(float x, float y, float z, float mass) {
	auto co = new btCollisionObject();
	btTransform t;
	t.setOrigin(btVector3(x,y,z));
	co->setWorldTransform(t);
	setCollObjStaticFlag(co,mass);
	return co;
}

void *LLGSEngine::c_addsphere(float x, float y, float z, float radius, float mass, int mygrp, int grpmask) {
	if(collisionWorld!=0) {
		auto cs = new btSphereShape(radius);
		auto co = createCollisionObject(x,y,z,mass);
		co->setCollisionShape(cs);
		collisionWorld->addCollisionObject(co,mygrp,grpmask);
		return (void *)co;
	}
	return 0;
}

void *LLGSEngine::c_addbox(float x, float y, float z, float halfext1, float halfext2, float halfext3, float mass, int mygrp, int grpmask) {
	if(collisionWorld!=0) {
		auto cs = new btBoxShape(btVector3(halfext1, halfext2, halfext3));
		auto co = createCollisionObject(x,y,z,mass);
		co->setCollisionShape(cs);
		collisionWorld->addCollisionObject(co,mygrp,grpmask);
		return (void *)co;
	}
	return 0;
}

void *LLGSEngine::c_addcilinder(float x, float y, float z, float halfext1, float halfext2, float halfext3, float mass, int mygrp, int grpmask) {
	if(collisionWorld!=0) {
		auto cs = new btCylinderShape(btVector3(halfext1, halfext2, halfext3));
		auto co = createCollisionObject(x,y,z,mass);
		co->setCollisionShape(cs);
		collisionWorld->addCollisionObject(co,mygrp,grpmask);
		return (void *)co;
	}
	return 0;
}

void  LLGSEngine::c_synccolobjtoscenenode(void *colobjptr, void *scenenodeptr) {
	auto co = static_cast<btCollisionObject *>(colobjptr);
	auto sn = static_cast<Ogre::SceneNode *>(scenenodeptr);
	btTransform t;
	Ogre::Vector3 snp = sn->getPosition();
	t.setOrigin(btVector3(snp.x,snp.y,snp.z));
	Ogre::Quaternion snq = sn->getOrientation();
	t.setRotation(btQuaternion(snq.x,snq.y,snq.z,snq.w));
	co->setWorldTransform(t);
}

int LLGSEngine::c_collisiondetection() {
	if(collisionWorld!=0) {
		collisionWorld->performDiscreteCollisionDetection();
		collisionWorld->debugDrawWorld();

		return collisionWorld->getDispatcher()->getNumManifolds();
	}
	return 0;
}

void *LLGSEngine::c_getcollisionpairObjA(int index) {
	if(collisionWorld!=0) {
		btPersistentManifold* contactManifold = collisionWorld->getDispatcher()->getManifoldByIndexInternal(index);
		if(contactManifold!=0) {
			return contactManifold->getBody0();
		}
	}
	return 0;
}

void *LLGSEngine::c_getcollisionpairObjB(int index) {
	if(collisionWorld!=0) {
		btPersistentManifold* contactManifold = collisionWorld->getDispatcher()->getManifoldByIndexInternal(index);
		if(contactManifold!=0) {
			return contactManifold->getBody1();
		}
	}
	return 0;
}

void  LLGSEngine::r_movecameraforward(void *camptr, float dist) {
	if(camptr!=0) {
		auto ptr = (Ogre::Camera *)camptr;
		ptr->move(ptr->getDirection().normalisedCopy()*dist);
	}
}

void *LLGSEngine::r_createlight(char *name) {
	if(scenemanager!=0) {
		return scenemanager->createLight(name);
	}
	return 0;
}

void  LLGSEngine::r_destroylight(void *lightptr) {
	if(scenemanager!=0) {
		scenemanager->destroyLight((Ogre::Light *)lightptr);
	}
}

void  LLGSEngine::r_setlighttype(void *lightptr, char *type) {
	if(lightptr!=0) {
		Ogre::Light::LightTypes sctype = Ogre::Light::LT_POINT;
		std::string pt = type;
		std::transform(pt.begin(), pt.end(), pt.begin(), std::bind2nd(std::ptr_fun(&std::toupper<char>), std::locale("")));

		if(pt.compare("DIRECTIONAL")==0) sctype = Ogre::Light::LT_DIRECTIONAL;
		((Ogre::Light *)lightptr)->setType(sctype);
	}
}

void  LLGSEngine::r_setlightdiffusecolor(void *lightptr, float r, float g, float b) {
	if(lightptr!=0) {
		((Ogre::Light *)lightptr)->setDiffuseColour(Ogre::ColourValue(r,g,b));
	}
}

void  LLGSEngine::r_setlightspecularcolor(void *lightptr, float r, float g, float b) {
	if(lightptr!=0) {
		((Ogre::Light *)lightptr)->setSpecularColour(Ogre::ColourValue(r,g,b));
	}
}

void  LLGSEngine::r_setlightpos(void *lightptr, float x, float y, float z) {
		if(lightptr!=0) {
			((Ogre::Light *)lightptr)->setPosition(x,y,z);
		}
}

void  LLGSEngine::r_setlightdirection(void *lightptr, float x, float y, float z) {
		if(lightptr!=0) {
			((Ogre::Light *)lightptr)->setDirection(x,y,z);
		}
}
