// llgs-engine
// Copyright (c) 2013 Kalman Kiss, Zalaegerszeg Hungary
// All rights reserved.
// kiskami@freemail.hu
//

#include "stdafx.h"

#include "LLGSEngine.h"

#include "OGRE\OgreRoot.h"

LLGSEngine::~LLGSEngine() {
	if(root!=0) {
		root = 0;
	}
}


void LLGSEngine::r_init(char *pluginsfile, char *configfile, char *logfile, char *rendersystem) {
	root = new Ogre::Root(pluginsfile, configfile, logfile);
	Ogre::Root::getSingleton().setRenderSystem(Ogre::Root::getSingleton().getRenderSystemByName(rendersystem));
}
