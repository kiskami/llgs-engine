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

LLGSEngine::~LLGSEngine() {
	if(root!=0) {
		root = 0;
	}
}


void LLGSEngine::r_init(char *pluginsfile, char *configfile, char *logfile, char *rendersystem, char *resourcesfile) {
	root = new Ogre::Root(pluginsfile, configfile, logfile);
	Ogre::Root::getSingleton().setRenderSystem(Ogre::Root::getSingleton().getRenderSystemByName(rendersystem));
	locateResources(resourcesfile);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	Ogre::Root::getSingleton().initialise(false);
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
