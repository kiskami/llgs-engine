// llgs-engine
// Copyright (c) 2013 Kalman Kiss, Zalaegerszeg Hungary
// All rights reserved.
// kiskami@freemail.hu
//

#include "stdafx.h"

#include "LLGSEngine.h"

#include "Bullet\btBulletCollisionCommon.h"
#include "Bullet\BulletCollision\Gimpact\btGImpactShape.h"
#include "Bullet\BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"

#include "OGRE\OgreFontManager.h"

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

void LLGSEngine::r_createrenderwindow(char *title, int w, int h, int fullscreen) {
	if(root!=0) {
		window = Ogre::Root::getSingleton().createRenderWindow(title, w, h, fullscreen>0?true:false);
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

		auto iter = Ogre::FontManager::getSingleton().getResourceIterator();
		while (iter.hasMoreElements()) { iter.getNext()->load(); }

		st_overlay = Ogre::OverlayManager::getSingleton().create("st_overlay");
		st_panel = static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "st_container"));
		st_panel->setPosition(0, 0);
		st_panel->setDimensions(1, 1);
		st_overlay->add2D(st_panel);
		st_overlay->show();
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
	Ogre::WindowEventUtilities::messagePump();
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

void  *LLGSEngine::r_simpletextpanel(char *id, char *txt, char *fontname, float fontsize, float x, float y, float w, float h, int pixelmetrics) {
	if(st_overlay!=0) {
		Ogre::OverlayElement* textBox = Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea",id);
		if(pixelmetrics>0) textBox->setMetricsMode(Ogre::GuiMetricsMode::GMM_PIXELS);
		textBox->setPosition(x, y);
	    textBox->setDimensions(w, h);
		textBox->setParameter("font_name", fontname);
		textBox->setParameter("char_height", Ogre::StringConverter::toString(fontsize));
		textBox->setColour(Ogre::ColourValue::White);
	    textBox->setCaption(txt);
	    st_panel->addChild(textBox);
		return textBox;
	}
	return 0;
}

void  LLGSEngine::r_simpletextsetcolor(char *id, float r, float g, float b) {
	auto e = Ogre::OverlayManager::getSingleton().getOverlayElement(id);
	assert(e);
	e->setColour(Ogre::ColourValue(r,g,b));
}

void  LLGSEngine::r_simpletextshow(char *id) {
	auto e = Ogre::OverlayManager::getSingleton().getOverlayElement(id);
	assert(e);
	e->show();
}

void  LLGSEngine::r_simpletexthide(char *id) {
	auto e = Ogre::OverlayManager::getSingleton().getOverlayElement(id);
	assert(e);
	e->hide();
}

void  LLGSEngine::r_simpletextsettext(char *id, char *txt) {
	auto e = Ogre::OverlayManager::getSingleton().getOverlayElement(id);
	assert(e);
	e->setCaption(txt);
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

void  LLGSEngine::r_translatescenenode(void *nodeptr, float dx, float dy, float dz, bool local) {
	static_cast<Ogre::SceneNode *>(nodeptr)->translate(dx,dy,dz,local?Ogre::Node::TS_LOCAL:Ogre::Node::TS_PARENT);
}

void  LLGSEngine::r_setscenenodescale(void *nodeptr, float xs, float ys, float zs) {
	static_cast<Ogre::SceneNode *>(nodeptr)->scale(xs,ys,zs);
}

void  LLGSEngine::r_rotatescenenodex(void *nodeptr, float radian) {
	static_cast<Ogre::SceneNode *>(nodeptr)->rotate(Ogre::Quaternion(Ogre::Radian(radian),Ogre::Vector3::UNIT_X));
}

void  LLGSEngine::r_rotatescenenodey(void *nodeptr, float radian) {
	static_cast<Ogre::SceneNode *>(nodeptr)->rotate(Ogre::Quaternion(Ogre::Radian(radian),Ogre::Vector3::UNIT_Y));
}

void  LLGSEngine::r_rotatescenenodez(void *nodeptr, float radian) {
	static_cast<Ogre::SceneNode *>(nodeptr)->rotate(Ogre::Quaternion(Ogre::Radian(radian),Ogre::Vector3::UNIT_Z));
}

void  LLGSEngine::r_attachmoveable(void *nodeptr, void *moveableptr) {
	static_cast<Ogre::SceneNode *>(nodeptr)->attachObject(static_cast<Ogre::MovableObject *>(moveableptr));
}

void  LLGSEngine::r_detachmoveable(void *nodeptr, void *moveableptr) {
	static_cast<Ogre::SceneNode *>(nodeptr)->detachObject(static_cast<Ogre::MovableObject *>(moveableptr));
}

void *LLGSEngine::r_createchildscenenode(void *nodeptr, char *name, int inheritori, int inheritscale) {
	auto n = static_cast<Ogre::SceneNode *>(nodeptr)->createChildSceneNode(name);
	n->setInheritOrientation(inheritori>0?true:false);
	n->setInheritScale(inheritscale>0?true:false);
	return n;
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
	auto collisionConfiguration = new btDefaultCollisionConfiguration;
	collisionWorld = new btCollisionWorld(
		new btCollisionDispatcher(collisionConfiguration)
		,new btDbvtBroadphase
		,collisionConfiguration);
	collisionWorld->setDebugDrawer(this);
	btGImpactCollisionAlgorithm::registerAlgorithm(static_cast<btCollisionDispatcher *>(collisionWorld->getDispatcher()));
	colldebugnode = scenemanager->getRootSceneNode()->createChildSceneNode();
}

void  LLGSEngine::c_shutdown() {
	if(collisionWorld!=0) {
		delete collisionWorld;
		collisionWorld = 0;
		if(colldebugnode!=0) {
			if(scenemanager!=0) {
				scenemanager->destroySceneNode(colldebugnode);
			}
			colldebugnode = 0;
		}
	}
}

void  LLGSEngine::c_setdebugdrawmode(int mode) {
	if(collisionWorld!=0) {
		collisionDebugmode = mode;
	}
}

void LLGSEngine::createDebugManuals() {
	if(colldebugmat.isNull()) {
		colldebugmat = Ogre::MaterialManager::getSingleton().create("colldebugmat","Common"); 
		colldebugmat->setReceiveShadows(false);
		colldebugmat->getTechnique(0)->setLightingEnabled(true); 
		colldebugmat->getTechnique(0)->getPass(0)->setDiffuse(0,0,1,0); 
		colldebugmat->getTechnique(0)->getPass(0)->setAmbient(0,0,1); 
		colldebugmat->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,1); 
//		colldebugmat.setNull();  // dispose pointer, not the material 
	}

	if(debugManualObj==0) {
		debugManualObj =  scenemanager->createManualObject();
	}
}

void LLGSEngine::drawLine(const btVector3& from,const btVector3& to,const btVector3& color) {
		createDebugManuals();

		debugManualObj->begin("colldebugmat", Ogre::RenderOperation::OT_LINE_LIST); 
		debugManualObj->position(from.getX(),from.getY(),from.getZ()); 
		debugManualObj->position(to.getX(),to.getY(),to.getZ()); 
		debugManualObj->colour(color.getX(),color.getY(),color.getZ());
		debugManualObj->end(); 
}

void LLGSEngine::drawContactPoint (const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color) {
		createDebugManuals();

		debugManualObj->begin("colldebugmat", Ogre::RenderOperation::OT_POINT_LIST);
		debugManualObj->position(PointOnB.getX(),PointOnB.getY(),PointOnB.getZ());
		debugManualObj->normal(normalOnB.getX(),normalOnB.getY(),normalOnB.getZ());
		debugManualObj->colour(color.getX(),color.getY(),color.getZ());
		debugManualObj->end(); 

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

//void setCollObjStaticFlag(btCollisionObject *co, int mass) {
//	if(mass==0) {
//		co->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
//	}
//}

btCollisionObject *LLGSEngine::createCollisionObject(float x, float y, float z) {
	auto co = new btCollisionObject();
	btTransform t;
	t.setIdentity();
	t.setOrigin(btVector3(x,y,z));
	co->setWorldTransform(t);
	co->activate();
	return co;
}

void *LLGSEngine::c_addsphere(float x, float y, float z, float radius, short mygrp, short grpmask) {
	if(collisionWorld!=0) {
		auto cs = new btSphereShape(radius);
		auto co = createCollisionObject(x,y,z);
		co->setCollisionShape(cs);
		collisionWorld->addCollisionObject(co,mygrp,grpmask);
		return (void *)co;
	}
	return 0;
}

void *LLGSEngine::c_addbox(float x, float y, float z, float halfext1, float halfext2, float halfext3, short mygrp, short grpmask) {
	if(collisionWorld!=0) {
		auto cs = new btBoxShape(btVector3(halfext1, halfext2, halfext3));
		auto co = createCollisionObject(x,y,z);
		co->setCollisionShape(cs);
		collisionWorld->addCollisionObject(co,mygrp,grpmask);
		return co;
	}
	return 0;
}

void *LLGSEngine::c_addcilinder(float x, float y, float z, float halfext1, float halfext2, float halfext3, short mygrp, short grpmask) {
	if(collisionWorld!=0) {
		auto cs = new btCylinderShape(btVector3(halfext1, halfext2, halfext3));
		auto co = createCollisionObject(x,y,z);
		co->setCollisionShape(cs);
		collisionWorld->addCollisionObject(co,mygrp,grpmask);
		return (void *)co;
	}
	return 0;
}

btGImpactMeshShape *toGImpactMeshShape(btCollisionObject *obj) {
	if(obj->getCollisionShape()->getShapeType() == GIMPACT_SHAPE_PROXYTYPE)
			return (btGImpactMeshShape *)obj->getCollisionShape();
	return 0;
}

void LLGSEngine::c_setlocalscaling(void *colobjptr, float xs, float ys, float zs) {
	auto co = static_cast<btCollisionObject *>(colobjptr);
	co->getCollisionShape()->setLocalScaling(btVector3(xs,ys,zs));
	btGImpactMeshShape *ms = toGImpactMeshShape(co);
	if(ms) {
//		Ogre::LogManager::getSingleton().logMessage("setlocalscaling: updating bounds");
		ms->updateBound();
	}
}

void checkCollisionShapeSize(btCollisionObject *co, Ogre::String name) {
		// from Bullet source
		btVector3 minAabb,maxAabb;
		co->getCollisionShape()->getAabb(co->getWorldTransform(), minAabb, maxAabb);
		if((maxAabb-minAabb).length2() >= btScalar(1e12)) {
			Ogre::LogManager::getSingleton().stream() 
				<< "Warning: mesh is too big (("<< minAabb.getX() << "," << minAabb.getY() << "," << minAabb.getZ() << "),("
				<< maxAabb.getX() << "," << maxAabb.getY() << "," << maxAabb.getZ() << ")) -> "			
				<< (maxAabb-minAabb).length2() << ") for a kinetic object for Bullet: " << name;
		}
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

	btGImpactMeshShape *ms = toGImpactMeshShape(co);
	if(ms) {
//		Ogre::LogManager::getSingleton().logMessage("synccolobjtoscenenode: updating bounds");
		ms->postUpdate();
		ms->updateBound();
	}

	checkCollisionShapeSize(co,sn->getName());
}

int LLGSEngine::c_collisiondetection() {
	if(collisionWorld!=0) {
		collisionWorld->performDiscreteCollisionDetection();

		if(debugManualObj) {
			if(debugManualObj->isAttached()) {
				colldebugnode->detachObject(debugManualObj);
			}
			scenemanager->destroyManualObject(debugManualObj);
			debugManualObj = 0;
		}

		collisionWorld->debugDrawWorld();

		if(debugManualObj) {
			colldebugnode->attachObject(debugManualObj);
		}

		return collisionWorld->getDispatcher()->getNumManifolds();
	}
	return 0;
}

void *LLGSEngine::c_getcollisionpairObjA(int index) {
	if(collisionWorld!=0) {
		btPersistentManifold* contactManifold = collisionWorld->getDispatcher()->getManifoldByIndexInternal(index);
		if(contactManifold!=0) {
			return (void *)contactManifold->getBody0();
		}
	}
	return 0;
}

void *LLGSEngine::c_getcollisionpairObjB(int index) {
	if(collisionWorld!=0) {
		btPersistentManifold* contactManifold = collisionWorld->getDispatcher()->getManifoldByIndexInternal(index);
		if(contactManifold!=0) {
			return (void *)contactManifold->getBody1();
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

/// Shares vertices/indexes between Ogre and Bullet
class MeshStrider : public btStridingMeshInterface {
 
public:
    MeshStrider( Ogre::Mesh * m = 0 ) : mMesh(m){
		//auto corners = m->getBounds().getAllCorners();
		//Ogre::LogManager::getSingleton().logMessage("MeshStrider: binding Ogre::Mesh "+ m->getName() +" to Bullet. Bounds: ");
		//for(int i=0; i < 8; ++i)
		//	Ogre::LogManager::getSingleton().stream() << i << ". (" << corners->x << "," << corners->y << "," << corners++->z << ")";
	}
 
    void set( Ogre::Mesh * m ) { mMesh = m; }
    // inherited interface
    virtual int        getNumSubParts() const;
 
    virtual void    getLockedVertexIndexBase(unsigned char **vertexbase, int& numverts,PHY_ScalarType& type, int& stride,unsigned char **indexbase,int & indexstride,int& numfaces,PHY_ScalarType& indicestype,int subpart=0);
    virtual void    getLockedReadOnlyVertexIndexBase(const unsigned char **vertexbase, int& numverts,PHY_ScalarType& type, int& stride,const unsigned char **indexbase,int & indexstride,int& numfaces,PHY_ScalarType& indicestype,int subpart=0) const;
 
    virtual void    unLockVertexBase(int subpart);
    virtual void    unLockReadOnlyVertexBase(int subpart) const;
 
    virtual void    preallocateVertices(int numverts);
    virtual void    preallocateIndices(int numindices);
private:
    Ogre::Mesh * mMesh;
};

int MeshStrider::getNumSubParts() const {
    int ret = mMesh->getNumSubMeshes();
    return ret;
}
 
void MeshStrider::getLockedReadOnlyVertexIndexBase ( 
    const unsigned char **vertexbase, 
    int& numverts,
    PHY_ScalarType& type, 
    int& stride,
    const unsigned char **indexbase,
    int & indexstride,
    int& numfaces,
    PHY_ScalarType& indicestype,
    int subpart/*=0*/ ) const {
    Ogre::SubMesh* submesh = mMesh->getSubMesh(subpart);
 
    Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mMesh->sharedVertexData : submesh->vertexData;
 
    const Ogre::VertexElement* posElem =
        vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
 
    Ogre::HardwareVertexBufferSharedPtr vbuf =
        vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());
 
    *vertexbase =
        reinterpret_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
    // There is _no_ baseVertexPointerToElement() which takes an Ogre::Real or a double
    //  as second argument. So make it float, to avoid trouble when Ogre::Real will
    //  be comiled/typedefed as double:
    //Ogre::Real* pReal;
    float* pReal;
    posElem->baseVertexPointerToElement((void*) *vertexbase, &pReal);
    *vertexbase = (unsigned char*) pReal;
 
    stride = (int) vbuf->getVertexSize();
 
    numverts = (int) vertex_data->vertexCount;
	assert( numverts );

    type = PHY_FLOAT;
 
    Ogre::IndexData* index_data = submesh->indexData;
    Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;
 
    if (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT) {
        indicestype = PHY_INTEGER;
    }
    else {
//        ASSERT(ibuf->getType() == Ogre::HardwareIndexBuffer::IT_16BIT);
		assert(ibuf->getType() == Ogre::HardwareIndexBuffer::IT_16BIT);
        indicestype = PHY_SHORT;
    }
 
    if ( submesh->operationType == Ogre::RenderOperation::OT_TRIANGLE_LIST ) {
        numfaces = (int) index_data->indexCount / 3;
        indexstride = (int) ibuf->getIndexSize()*3;
    }
    else
    if ( submesh->operationType == Ogre::RenderOperation::OT_TRIANGLE_STRIP ) {
        numfaces = (int) index_data->indexCount -2;
        indexstride = (int) ibuf->getIndexSize();
    }
    else {
//        ASSERT( 0 ); // not supported
		assert(0);
    }
 
    *indexbase = reinterpret_cast<unsigned char*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

//	Ogre::LogManager::getSingleton().stream() << "MeshStrider::getLockedReadOnlyVertexIndexBase numverts=" << numverts << " stride=" << stride << " indexstride=" << indexstride
//											  << " numfaces=" << numfaces << " subpart=" << subpart;
}
 
void MeshStrider::getLockedVertexIndexBase( unsigned char **vertexbase, int& numverts,PHY_ScalarType& type, int& stride,unsigned char **indexbase,int & indexstride,int& numfaces,PHY_ScalarType& indicestype,int subpart/*=0*/ ) {
//    ASSERT( 0 );
	assert(0);
}
 
void MeshStrider::unLockReadOnlyVertexBase( int subpart ) const {
    Ogre::SubMesh* submesh = mMesh->getSubMesh(subpart);
 
    Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mMesh->sharedVertexData : submesh->vertexData;
 
    const Ogre::VertexElement* posElem =
        vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
 
    Ogre::HardwareVertexBufferSharedPtr vbuf =
        vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());
 
    vbuf->unlock();
 
    Ogre::IndexData* index_data = submesh->indexData;
    Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;
    ibuf->unlock();
}
 
void MeshStrider::unLockVertexBase( int subpart ) {
//    ASSERT( 0 );
	assert(0);
}
 
void MeshStrider::preallocateVertices( int numverts ) {
//    ASSERT( 0 );
	assert(0);
}
 
void MeshStrider::preallocateIndices( int numindices ) {
//    ASSERT( 0 );
	assert(0);
}

void *LLGSEngine::c_addmeshgeom(float x, float y, float z, void *entityptr, short mygrp, short grpmask) {
	if(collisionWorld!=0) {
		auto co = createCollisionObject(x,y,z);
		auto trimesh = new btGImpactMeshShape(new MeshStrider(((Ogre::Entity *)entityptr)->getMesh().get()));
//		Ogre::LogManager::getSingleton().logMessage("addmeshgeom: updating bounds");
		trimesh->updateBound();
		co->setCollisionShape(trimesh);
		checkCollisionShapeSize(co,((Ogre::Entity *)entityptr)->getName());

		collisionWorld->addCollisionObject(co,mygrp,grpmask);
		return (void *)co;
	}
	return 0;
}

float LLGSEngine::r_actfps() {
	if(window!=0) {
		return window->getLastFPS();
	}
	return 0;
}

float LLGSEngine::r_minfps() {
	if(window!=0) {
		return window->getWorstFPS();
	}
	return 0;
}

float LLGSEngine::r_maxfps() {
	if(window!=0) {
		return window->getBestFPS();
	}
	return 0;
}

long LLGSEngine::r_trianglecount() {
	if(window!=0) {
		return window->getTriangleCount();
	}
	return 0;
}

long LLGSEngine::r_batchcount() {
	if(window!=0) {
		return window->getBatchCount();
	}
	return 0;
}

float LLGSEngine::r_getscenenodeposx(void *nodeptr) {
	if(nodeptr!=0) {
		return ((Ogre::SceneNode *)nodeptr)->getPosition().x;
	}
	return 0;
}

float LLGSEngine::r_getscenenodeposy(void *nodeptr) {
	if(nodeptr!=0) {
		return ((Ogre::SceneNode *)nodeptr)->getPosition().y;
	}
	return 0;
}

float LLGSEngine::r_getscenenodeposz(void *nodeptr) {
	if(nodeptr!=0) {
		return ((Ogre::SceneNode *)nodeptr)->getPosition().z;
	}
	return 0;
}

void LLGSEngine::c_setcolobjpos(void *colobjptr, float x, float y, float z) {
	auto co = static_cast<btCollisionObject *>(colobjptr);
	btTransform t = co->getWorldTransform();
	t.setOrigin(btVector3(x,y,z));
	co->setWorldTransform(t);

	btGImpactMeshShape *ms = toGImpactMeshShape(co);
	if(ms) {
//		Ogre::LogManager::getSingleton().logMessage("synccolobjtoscenenode: updating bounds");
		ms->postUpdate();
		ms->updateBound();
	}
}

void *LLGSEngine::r_createbillboardset() {
	if(scenemanager!=0) {
		auto res = scenemanager->createBillboardSet(64);
//		res->setVisible(true);
		res->setAutoextend(true);
		res->setBillboardsInWorldSpace(true);
		res->setAutoUpdate(true);
		res->setCullIndividually(true);
		return res;
	}
	return 0;
}

void LLGSEngine::r_clearbillboardset(void *ptr) {
	((Ogre::BillboardSet *)ptr)->clear();
}

void LLGSEngine::r_destroybillboardset(void *ptr) {
	if(scenemanager!=0) {
		scenemanager->destroyBillboardSet((Ogre::BillboardSet *)ptr);
	}
}

void *LLGSEngine::r_createbillboard(void *owner, float x, float y, float z, float r, float g, float b) {
	return ((Ogre::BillboardSet *)owner)->createBillboard(x,y,z,Ogre::ColourValue(r,g,b));
}

void LLGSEngine::r_removebillboard(void *setptr, void *billptr) {
	((Ogre::BillboardSet *)setptr)->removeBillboard((Ogre::Billboard *)billptr);
}

void LLGSEngine::r_setbillboardmaterial(void *setptr, char *matname) {
	((Ogre::BillboardSet *)setptr)->setMaterialName(matname);
}

void LLGSEngine::r_setbillboarddefdims(void *setptr, float w, float h) {
	((Ogre::BillboardSet *)setptr)->setDefaultDimensions(w,h);
}

void LLGSEngine::r_setbillboardpos(void *setptr, void *billprt, float x, float y, float z) {
	if(setptr!=0) {
		((Ogre::Billboard *)billprt)->setPosition(x,y,z);
	}
}

void LLGSEngine::r_movebillboard(void *setptr, void *billprt, float x, float y, float z, float w, float dist) {
	if(setptr!=0) {
		Ogre::Billboard *b = (Ogre::Billboard *)billprt;
		Ogre::Vector3 deltav = -Ogre::Quaternion(w,x,y,z).yAxis() * dist;
		auto oripos = b->getPosition();
//		Ogre::LogManager::getSingleton().stream() << "r_movebillboard oripos: (" << oripos.x << "," << oripos.y << "," << oripos.z << ")";
//		Ogre::LogManager::getSingleton().stream() << "r_movebillboard deltav: (" << deltav.x << "," << deltav.y << "," << deltav.z << ")";
		b->setPosition(oripos + deltav);
//		oripos = b->getPosition();
//		Ogre::LogManager::getSingleton().stream() << "r_movebillboard newpos: (" << oripos.x << "," << oripos.y << "," << oripos.z << ")";
	}
}

float LLGSEngine::r_getscenenodeorix(void *nodeptr) {
	return ((Ogre::SceneNode *)nodeptr)->getOrientation().x;
}

float LLGSEngine::r_getscenenodeoriy(void *nodeptr) {
	return ((Ogre::SceneNode *)nodeptr)->getOrientation().y;
}

float LLGSEngine::r_getscenenodeoriz(void *nodeptr) {
	return ((Ogre::SceneNode *)nodeptr)->getOrientation().z;
}

float LLGSEngine::r_getscenenodeoriw(void *nodeptr) {
	return ((Ogre::SceneNode *)nodeptr)->getOrientation().w;
}

float LLGSEngine::r_getbillboardx(void *setptr, void *billprt) {
	if(setptr!=0) {
		return ((Ogre::Billboard *)billprt)->getPosition().x;
	}
	return 0;
}

float LLGSEngine::r_getbillboardy(void *setptr, void *billprt) {
	if(setptr!=0) {
		return ((Ogre::Billboard *)billprt)->getPosition().y;
	}
	return 0;
}

float LLGSEngine::r_getbillboardz(void *setptr, void *billprt) {
	if(setptr!=0) {
		return ((Ogre::Billboard *)billprt)->getPosition().z;
	}
	return 0;
}

void LLGSEngine::c_delcolobj(void *colobjptr) {
	if(collisionWorld!=0) {
		collisionWorld->removeCollisionObject((btCollisionObject *)colobjptr);
	}
}
