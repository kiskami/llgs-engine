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

class btCollisionWorld;

class InputHandler;

#include "Bullet\LinearMath\btIDebugDraw.h"

struct CollisionObjectPair;

class LLGSEngine : public btIDebugDraw {
public:
	LLGSEngine(void) : guiinput_enabled(false), collisionDebugmode(0) {}
	~LLGSEngine();

	// Bullet btIDebugDraw functions
	virtual void drawLine(const btVector3& from,const btVector3& to,const btVector3& color);
	virtual void drawContactPoint (const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color);
	virtual void reportErrorWarning (const char *warningString);
	virtual void draw3dText (const btVector3 &location, const char *textString);
	virtual void setDebugMode (int debugMode);
	virtual int getDebugMode () const;

	void r_init(char *pluginsfile, char *configfile, char *logfile, char *rendersystem, char *resourcesfile);
	void r_shutdown();
	void r_createrenderwindow(char *title, int w, int h, bool fullscreen);
	void r_createscenemanager(char *type, char *name);

	void *r_createcamera(char *name);
	void  r_setcamerapos(void *camptr, float x, float y, float z);
	void  r_movecamerarel(void *camptr, float x, float y, float z);
	void  r_movecameraforward(void *camptr, float dist);
	void  r_cameralookat(void *camptr, float x, float y, float z);

	void  r_rotatecamerax(void *camptr, float radian);
	void  r_rotatecameray(void *camptr, float radian);
	void  r_rotatecameraz(void *camptr, float radian);

	void  r_setcameraneraclipdist(void *camptr, float dist);
	void  r_setcamerafarclipdist(void *camptr, float dist);
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

	void *r_simpletextpanel(char *txt, char *fontname, float x, float y, float w, float h);
	void  r_simpletextsetcolor(void *panelptr, float r, float g, float b);
	void  r_simpletextshow(void *panelptr);
	void  r_simpletexthide(void *panelptr);
	void  r_simpletextsettext(void *panelptr, char *txt);

	void *r_loadmesh(char *name, char *meshname);
	void  r_destroymesh(void *entityptr);

	void *r_clonemesh(void *entityptr, char *newname);
	void r_setmeshmaterial(void *entityptr, char *matname);

	void *r_createscenenode(char *name);
	void *r_getrootscenenode();
	void  r_destroyscenenode(void *nodeptr);

	void  r_setscenenodepos(void *nodeptr, float x, float y, float z);
	void  r_translatescenenode(void *nodeptr, float dx, float dy, float dz);
	void  r_setscenenodescale(void *nodeptr, float xs, float ys, float zs);

	void  r_rotatescenenodex(void *nodeptr, float radian);
	void  r_rotatescenenodey(void *nodeptr, float radian);
	void  r_rotatescenenodez(void *nodeptr, float radian);

	void  r_attachmoveable(void *nodeptr, void *moveableptr);
	void  r_detachmoveable(void *nodeptr, void *moveableptr);

	void *r_createchildscenenode(void *nodeptr, char *name);
	void *r_getparentscenenode(void *nodeptr);
	void r_addchild(void *nodeptr, void *childptr);
	void r_removechild(void *nodeptr, void *childptr);

	void  r_setscenenodevis(void *nodeptr, bool visible);

	void  r_setscenenodeuserobj(void *nodeptr, char *key, void *obj);
	void *r_getscenenodeuserobj(void *nodeptr, char *key);
	void  r_delscenenodeuserobj(void *nodeptr, char *key);

	void *r_createpartsys(char *name, char *templ);
	void  r_destroypartsys(void *partsysptr);
	void  r_setpartsysemitting(void *partsysptr, bool emit);
	void  r_setpartsysvis(void *partsysptr, bool visible);

	void *r_createlight(char *name);
	void  r_destroylight(void *lightptr);
	void  r_setlighttype(void *lightptr, char *type);
	void  r_setlightdiffusecolor(void *lightptr, float r, float g, float b);
	void  r_setlightspecularcolor(void *lightptr, float r, float g, float b);
	void  r_setlightpos(void *lightptr, float x, float y, float z);
	void  r_setlightdirection(void *lightptr, float x, float y, float z);

	void  c_init();
	void  c_shutdown();
	void  c_enabledebugdrawer(bool enable);

	void *c_addsphere(float x, float y, float z, float radius, float mass, int mygrp, int grpmask);
	void *c_addbox(float x, float y, float z, float halfext1, float halfext2, float halfext3, float mass, int mygrp, int grpmask);
	void *c_addcilinder(float x, float y, float z, float halfext1, float halfext2, float halfext3, float mass, int mygrp, int grpmask);

	void  c_synccolobjtoscenenode(void *colobjptr, void *scenenodeptr);

	int c_collisiondetection();
	void *c_getcollisionpairObjA(int index);
	void *c_getcollisionpairObjB(int index);

private:

	void locateResources(char *resources_cfg);

	Ogre::Root *root;
	Ogre::RenderWindow *window;
	Ogre::SceneManager *scenemanager;
	Ogre::Viewport *viewport;

	InputHandler *inputhandler;

	bool guiinput_enabled;

	btCollisionWorld* collisionWorld;
	int collisionDebugmode;
};
