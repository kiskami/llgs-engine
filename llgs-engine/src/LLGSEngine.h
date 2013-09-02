// llgs-engine
// Copyright (c) 2013 Kalman Kiss, Zalaegerszeg Hungary
// All rights reserved.
// kiskami@freemail.hu
//

#pragma once

namespace Ogre {
	class Root;
	class RenderWindow;
	class SceneManager;
};

class LLGSEngine {
public:
	LLGSEngine(void) {}
	~LLGSEngine();

	void r_init(char *pluginsfile, char *configfile, char *logfile, char *rendersystem, char *resourcesfile);
	void r_createrenderwindow(char *title, int w, int h, bool fullscreen);
	void r_createscenemanager(char *type, char *name);

	void  r_screenshottofile(char *basename);

private:

	void locateResources(char *resources_cfg);

	Ogre::Root *root;
	Ogre::RenderWindow *window;
	Ogre::SceneManager *scenemanager;
};
