// llgs-engine
// Copyright (c) 2013 Kalman Kiss, Zalaegerszeg Hungary
// All rights reserved.
// kiskami@freemail.hu
//

#include "stdafx.h"

#include "LLGSEngine.h"

#include "OGRE\Ogre.h"

#include <functional>
#include <locale>

#include "InputHandler.h"

LLGSEngine::~LLGSEngine() {
	r_shutdown();
}

void LLGSEngine::r_init(char *pluginsfile, char *configfile, char *logfile, char *rendersystem, char *resourcesfile) {
	root = new Ogre::Root(pluginsfile, configfile, logfile);
	Ogre::Root::getSingleton().setRenderSystem(Ogre::Root::getSingleton().getRenderSystemByName(rendersystem));
	locateResources(resourcesfile);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
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

void  LLGSEngine::r_cameralookat(void *camptr, float x, float y, float z) {
	if(camptr!=0) {
		((Ogre::Camera *)camptr)->lookAt(Ogre::Vector3(x,y,z));
	}
}

void  LLGSEngine::r_setcameraneraclipdist(void *camptr, float dist) {
	if(camptr!=0) {
		((Ogre::Camera *)camptr)->setNearClipDistance(dist);
	}
}

void  LLGSEngine::r_setcameraasviewport(void *camptr) {
	if(window!=0) {
		viewport = window->addViewport((Ogre::Camera *)camptr);
		((Ogre::Camera *)camptr)->setAspectRatio(viewport->getActualWidth()/(float)viewport->getActualHeight());
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
