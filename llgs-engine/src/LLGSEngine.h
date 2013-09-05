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
	class Viewport;
};

class InputHandler;

class LLGSEngine {
public:
	LLGSEngine(void) : guiinput_enabled(false) {}
	~LLGSEngine();

	void r_init(char *pluginsfile, char *configfile, char *logfile, char *rendersystem, char *resourcesfile);
	void r_shutdown();
	void r_createrenderwindow(char *title, int w, int h, bool fullscreen);
	void r_createscenemanager(char *type, char *name);

	void *r_createcamera(char *name);
	void  r_setcamerapos(void *camptr, float x, float y, float z);
	void  r_cameralookat(void *camptr, float x, float y, float z);
	void  r_setcameraneraclipdist(void *camptr, float dist);
	void  r_setcameraasviewport(void *camptr);
	void  r_setviewportbackground(float r, float g, float b);

	void  r_setambientlight(float r, float g, float b);

	void  r_renderoneframe();

	void  r_setskybox(char *materialname);
	
	void  r_screenshottofile(char *basename);

	void *t_createtimer();
	void  t_resettimer(void *timerptr);
	unsigned long   t_gettimermicroseconds(void *timerptr);

	void  i_init();
	void  i_shutdown();
	void  i_captureinput();
	int  i_keypressed(int key);
	void  i_guiinput(bool enable);
	int  i_leftmouse();
	int  i_middlemouse();
	int  i_rightmouse();
	int   i_mousex();
	int   i_mousey();
	int   i_mouserelx();
	int   i_mouserely();

private:

	void locateResources(char *resources_cfg);

	Ogre::Root *root;
	Ogre::RenderWindow *window;
	Ogre::SceneManager *scenemanager;
	Ogre::Viewport *viewport;

	InputHandler *inputhandler;

	bool guiinput_enabled;
};
