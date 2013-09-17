// llgs-engine
// Copyright (c) 2013 Kalman Kiss, Zalaegerszeg Hungary
// All rights reserved.
// kiskami@freemail.hu
//
#pragma once

#ifdef LLGSENGINE_EXPORTS
#define LLGSENGINE_API __declspec(dllexport)
#else
#define LLGSENGINE_API __declspec(dllimport)
#endif

extern "C" {

// -------------------------------
// Renderer api
LLGSENGINE_API void  r_init(char *pluginsfile, char *configfile, char *logfile, char *rendersystem, char *resourcesfile);
LLGSENGINE_API void  r_shutdown();
LLGSENGINE_API void  r_createrenderwindow(char *title, int w, int h, bool fullscreen);
LLGSENGINE_API void  r_createscenemanager(char *type, char *name);

LLGSENGINE_API void *r_createcamera(char *name);
LLGSENGINE_API void  r_setcamerapos(void *camptr, float x, float y, float z);
LLGSENGINE_API void  r_movecamerarel(void *camptr, float x, float y, float z);
LLGSENGINE_API void  r_movecameraforward(void *camptr, float dist);
LLGSENGINE_API void  r_cameralookat(void *camptr, float x, float y, float z);

LLGSENGINE_API void  r_rotatecamerax(void *camptr, float radian);
LLGSENGINE_API void  r_rotatecameray(void *camptr, float radian);
LLGSENGINE_API void  r_rotatecameraz(void *camptr, float radian);

LLGSENGINE_API void  r_setcameranearclipdist(void *camptr, float dist);
LLGSENGINE_API void  r_setcamerafarclipdist(void *camptr, float dist);
LLGSENGINE_API void  r_setcameraasviewport(void *camptr);

LLGSENGINE_API void  r_setviewportbackground(float r, float g, float b);

LLGSENGINE_API void  r_setambientlight(float r, float g, float b);

LLGSENGINE_API void  r_renderoneframe();

LLGSENGINE_API void  r_setskybox(char *materialname);

LLGSENGINE_API void  r_screenshottofile(char *namebase);

// -------------------------------
// Simple timer api
// after renderer init
LLGSENGINE_API void *t_createtimer();
LLGSENGINE_API void  t_resettimer(void *timerptr);
LLGSENGINE_API unsigned long   t_gettimermicroseconds(void *timerptr);

// -------------------------------
// Mesh api
LLGSENGINE_API void *r_loadmesh(char *name, char *meshname);
LLGSENGINE_API void  r_destroymesh(void *entityptr);

LLGSENGINE_API void *r_clonemesh(void *entityptr, char *newname);
LLGSENGINE_API void  r_setmeshmaterial(void *entityptr, char *matname);

// -------------------------------
// Scene node api
LLGSENGINE_API void *r_createscenenode(char *name);
LLGSENGINE_API void *r_getrootscenenode();
LLGSENGINE_API void  r_destroyscenenode(void *nodeptr);

LLGSENGINE_API void  r_setscenenodepos(void *nodeptr, float x, float y, float z);
LLGSENGINE_API void  r_translatescenenode(void *nodeptr, float dx, float dy, float dz, bool local);
LLGSENGINE_API void  r_setscenenodescale(void *nodeptr, float xs, float ys, float zs);

LLGSENGINE_API void  r_rotatescenenodex(void *nodeptr, float radian);
LLGSENGINE_API void  r_rotatescenenodey(void *nodeptr, float radian);
LLGSENGINE_API void  r_rotatescenenodez(void *nodeptr, float radian);

// add mesh, camera, particle, ...
LLGSENGINE_API void  r_attachmoveable(void *nodeptr, void *moveableptr);
LLGSENGINE_API void  r_detachmoveable(void *nodeptr, void *moveableptr);

LLGSENGINE_API void *r_createchildscenenode(void *nodeptr, char *name);
LLGSENGINE_API void *r_getparentscenenode(void *nodeptr);
LLGSENGINE_API void r_addchild(void *nodeptr, void *childptr);
LLGSENGINE_API void r_removechild(void *nodeptr, void *childptr);

LLGSENGINE_API void  r_setscenenodevis(void *nodeptr, bool visible);

LLGSENGINE_API void  r_setscenenodeuserobj(void *nodeptr, char *key, void *obj);
LLGSENGINE_API void *r_getscenenodeuserobj(void *nodeptr, char *key);
LLGSENGINE_API void  r_delscenenodeuserobj(void *nodeptr, char *key);


// -------------------------------
// Particle system api
LLGSENGINE_API void *r_createpartsys(char *name, char *templ);
LLGSENGINE_API void  r_destroypartsys(void *partsysptr);
LLGSENGINE_API void  r_setpartsysemitting(void *partsysptr, bool emit);
LLGSENGINE_API void  r_setpartsysvis(void *partsysptr, bool visible);

// -------------------------------
// Lights api
LLGSENGINE_API void *r_createlight(char *name);
LLGSENGINE_API void  r_destroylight(void *lightptr);
LLGSENGINE_API void  r_setlighttype(void *lightptr, char *type);
LLGSENGINE_API void  r_setlightdiffusecolor(void *lightptr, float r, float g, float b);
LLGSENGINE_API void  r_setlightspecularcolor(void *lightptr, float r, float g, float b);
LLGSENGINE_API void  r_setlightpos(void *lightptr, float x, float y, float z);
LLGSENGINE_API void  r_setlightdirection(void *lightptr, float x, float y, float z);

// -------------------------------
// User input api
LLGSENGINE_API void  i_init();
LLGSENGINE_API void  i_shutdown();
LLGSENGINE_API void  i_captureinput();
LLGSENGINE_API int  i_keypressed(int key);
LLGSENGINE_API void  i_guiinput(bool enable);
LLGSENGINE_API int  i_leftmouse();
LLGSENGINE_API int  i_middlemouse();
LLGSENGINE_API int  i_rightmouse();
LLGSENGINE_API int   i_mousex();
LLGSENGINE_API int   i_mousey();
LLGSENGINE_API int   i_mouserelx();
LLGSENGINE_API int   i_mouserely();

// ----------------------------
// simple text output functions
LLGSENGINE_API void  *r_simpletextpanel(char *id, char *txt, char *fontname, int fontsize, float x, float y, float w, float h);
LLGSENGINE_API void  r_simpletextsetcolor(char *id, float r, float g, float b);
LLGSENGINE_API void  r_simpletextshow(char *id);
LLGSENGINE_API void  r_simpletexthide(char *id);
LLGSENGINE_API void  r_simpletextsettext(char *id, char *txt);

// -------------------------------
// (CE)GUI api

// -------------------------------
// Collision detection (Bullet) api
LLGSENGINE_API void  c_init();
LLGSENGINE_API void  c_shutdown();
LLGSENGINE_API void  c_setdebugdrawmode(int mode);

LLGSENGINE_API void *c_addsphere(float x, float y, float z, float radius, float mass, short mygrp, short grpmask);
LLGSENGINE_API void *c_addbox(float x, float y, float z, float halfext1, float halfext2, float halfext3, float mass, short mygrp, short grpmask);
LLGSENGINE_API void *c_addcilinder(float x, float y, float z, float halfext1, float halfext2, float halfext3, float mass, short mygrp, short grpmask);
LLGSENGINE_API void *c_addmeshgeom(float x, float y, float z, void *entityptr, float mass, short mygrp, short grpmask);

LLGSENGINE_API void c_setlocalscaling(void *colobjptr, float xs, float ys, float zs);
LLGSENGINE_API void c_setdynamic(void *colobjptr, int dynamic);
LLGSENGINE_API void  c_synccolobjtoscenenode(void *colobjptr, void *scenenodeptr);

LLGSENGINE_API int c_collisiondetection();

LLGSENGINE_API void *c_getcollisionpairObjA(int index);
LLGSENGINE_API void *c_getcollisionpairObjB(int index);

// -------------------------------
// Physics (Bullet) api


// -------------------------------
// Sound (OpenAL) api

}; // extern "C"
