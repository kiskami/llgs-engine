// llgs-engine
// Copyright (c) 2013 Kalman Kiss, Zalaegerszeg Hungary
// All rights reserved.
// kiskami@freemail.hu
//
// llgs-engine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "llgs-engine.h"
#include "LLGSEngine.h"

// dll globális engine példány
LLGSEngine engine;

LLGSENGINE_API void r_init(char *pluginsfile, char *configfile, char *logfile, char *rendersystem, char *resourcesfile) {
	engine.r_init(pluginsfile, configfile, logfile, rendersystem, resourcesfile);
}

LLGSENGINE_API void  r_shutdown() {
	engine.r_shutdown();
}

LLGSENGINE_API void  r_createrenderwindow(char *title, int w, int h, bool fullscreen) {
	engine.r_createrenderwindow(title, w, h, fullscreen);
}

LLGSENGINE_API void  r_createscenemanager(char *type, char *name) {
	engine.r_createscenemanager(type,name);
}

LLGSENGINE_API void *r_createcamera(char *name) {
	return engine.r_createcamera(name);
}

LLGSENGINE_API void  r_setcamerapos(void *camptr, float x, float y, float z) {
	engine.r_setcamerapos(camptr,x,y,z);
}

LLGSENGINE_API void  r_movecamerarel(void *camptr, float x, float y, float z) {
	engine.r_movecamerarel(camptr, x, y, z);
}

LLGSENGINE_API void  r_cameralookat(void *camptr, float x, float y, float z) {
	engine.r_cameralookat(camptr,x,y,z);
}

LLGSENGINE_API void  r_rotatecamerax(void *camptr, float radian) {
	engine.r_rotatecamerax(camptr, radian);
}

LLGSENGINE_API void  r_rotatecameray(void *camptr, float radian) {
	engine.r_rotatecameray(camptr, radian);
}

LLGSENGINE_API void  r_rotatecameraz(void *camptr, float radian) {
	engine.r_rotatecameraz(camptr, radian);
}

LLGSENGINE_API void  r_setcameranearclipdist(void *camptr, float dist) {
	engine.r_setcameraneraclipdist(camptr,dist);
}

LLGSENGINE_API void  r_setcamerafarclipdist(void *camptr, float dist) {
	engine.r_setcamerafarclipdist(camptr, dist);

}

LLGSENGINE_API void  r_setcameraasviewport(void *camptr) {
	engine.r_setcameraasviewport(camptr);
}

LLGSENGINE_API void  r_setviewportbackground(float r, float g, float b) {
	engine.r_setviewportbackground(r,g,b);
}

LLGSENGINE_API void  r_setambientlight(float r, float g, float b) {
	engine.r_setambientlight(r,g,b);
}

LLGSENGINE_API void  r_renderoneframe() {
	engine.r_renderoneframe();
}

LLGSENGINE_API void  r_setskybox(char *materialname) {
	engine.r_setskybox(materialname);
}

LLGSENGINE_API void  r_screenshottofile(char *basename) {
	engine.r_screenshottofile(basename);
}

// -------------------------------
// Simple timer api
// after renderer init
LLGSENGINE_API void *t_createtimer() {
	return engine.t_createtimer();
}

LLGSENGINE_API void  t_resettimer(void *timerptr) {
	engine.t_resettimer(timerptr);
}

LLGSENGINE_API unsigned long   t_gettimermicroseconds(void *timerptr) {
	return engine.t_gettimermicroseconds(timerptr);
}

// -------------------------------
// User input api
LLGSENGINE_API void  i_init() {
	engine.i_init();
}

LLGSENGINE_API void  i_shutdown() {
	engine.i_shutdown();
}

LLGSENGINE_API void  i_captureinput() {
	engine.i_captureinput();
}

LLGSENGINE_API int  i_keypressed(int key) {
	return engine.i_keypressed(key);
}

LLGSENGINE_API void  i_guiinput(bool enable) {
	engine.i_guiinput(enable);
}

LLGSENGINE_API int  i_leftmouse() {
	return engine.i_leftmouse();
}

LLGSENGINE_API int  i_middlemouse() {
	return engine.i_middlemouse();
}

LLGSENGINE_API int  i_rightmouse() {
	return engine.i_rightmouse();
}

LLGSENGINE_API int   i_mousex() {
	return engine.i_mousex();
}

LLGSENGINE_API int   i_mousey() {
	return engine.i_mousey();
}

LLGSENGINE_API int   i_mouserelx() {
	return engine.i_mouserelx();
}

LLGSENGINE_API int   i_mouserely() {
	return engine.i_mouserely();
}

// simple text output functions
LLGSENGINE_API void *r_simpletextpanel(char *txt, char *fontname, float x, float y, float w, float h) {
	return engine.r_simpletextpanel(txt,fontname,x,y,w,h);
}

LLGSENGINE_API void  r_simpletextsetcolor(void *id, float r, float g, float b) {
	engine.r_simpletextsetcolor(id,r,g,b);
}

LLGSENGINE_API void  r_simpletextshow(void *id) {
	engine.r_simpletextshow(id);
}

LLGSENGINE_API void  r_simpletexthide(void *id) {
	engine.r_simpletexthide(id);
}

LLGSENGINE_API void  r_simpletextsettext(void *id, char *txt) {
	engine.r_simpletextsettext(id,txt);
}

LLGSENGINE_API void *r_loadmesh(char *name, char *meshname) {
	return engine.r_loadmesh(name,meshname);
}

LLGSENGINE_API void  r_destroymesh(void *entityptr) {
	engine.r_destroymesh(entityptr);
}

LLGSENGINE_API void *r_clonemesh(void *entityptr, char *newname) {
	return engine.r_clonemesh(entityptr,newname);
}

LLGSENGINE_API void r_setmeshmaterial(void *entityptr, char *matname) {
	engine.r_setmeshmaterial(entityptr,matname);
}

LLGSENGINE_API void *r_createscenenode(char *name) {
	return engine.r_createscenenode(name);
}

LLGSENGINE_API void *r_getrootscenenode() {
	return engine.r_getrootscenenode();
}

LLGSENGINE_API void  r_destroyscenenode(void *nodeptr) {
	engine.r_destroyscenenode(nodeptr);
}

LLGSENGINE_API void  r_setscenenodepos(void *nodeptr, float x, float y, float z) {
	engine.r_setscenenodepos(nodeptr,x,y,z);
}

LLGSENGINE_API void  r_translatescenenode(void *nodeptr, float dx, float dy, float dz) {
	engine.r_translatescenenode(nodeptr,dx,dy,dz);
}

LLGSENGINE_API void  r_setscenenodescale(void *nodeptr, float xs, float ys, float zs) {
	engine.r_setscenenodescale(nodeptr,xs,ys,zs);
}

LLGSENGINE_API void  r_rotatescenenodex(void *nodeptr, float radian) {
	engine.r_rotatescenenodex(nodeptr,radian);
}

LLGSENGINE_API void  r_rotatescenenodey(void *nodeptr, float radian) {
	engine.r_rotatescenenodey(nodeptr,radian);
}

LLGSENGINE_API void  r_rotatescenenodez(void *nodeptr, float radian) {
	engine.r_rotatescenenodez(nodeptr,radian);
}

// add mesh, camera, particle, ...
LLGSENGINE_API void  r_attachmoveable(void *nodeptr, void *moveableptr) {
	engine.r_attachmoveable(nodeptr,moveableptr);
}

LLGSENGINE_API void  r_detachmoveable(void *nodeptr, void *moveableptr) {
	engine.r_detachmoveable(nodeptr,moveableptr);
}

LLGSENGINE_API void *r_createchildscenenode(void *nodeptr, char *name) {
	return engine.r_createchildscenenode(nodeptr, name);
}

LLGSENGINE_API void *r_getparentscenenode(void *nodeptr) {
	return engine.r_getparentscenenode(nodeptr);
}

LLGSENGINE_API void r_addchild(void *nodeptr, void *childptr) {
	engine.r_addchild(nodeptr,childptr);
}

LLGSENGINE_API void r_removechild(void *nodeptr, void *childptr) {
	engine.r_removechild(nodeptr,childptr);
}

LLGSENGINE_API void  r_setscenenodevis(void *nodeptr, bool visible) {
	engine.r_setscenenodevis(nodeptr,visible);
}

LLGSENGINE_API void  r_setscenenodeuserobj(void *nodeptr, char *key, void *obj) {
	engine.r_setscenenodeuserobj(nodeptr,key,obj);
}

LLGSENGINE_API void *r_getscenenodeuserobj(void *nodeptr, char *key) {
	return engine.r_getscenenodeuserobj(nodeptr,key);
}

LLGSENGINE_API void  r_delscenenodeuserobj(void *nodeptr, char *key) {
	return engine.r_delscenenodeuserobj(nodeptr,key);
}

LLGSENGINE_API void *r_createpartsys(char *name, char *templ) {
	return engine.r_createpartsys(name,templ);
}

LLGSENGINE_API void  r_destroypartsys(void *partsysptr) {
	engine.r_destroypartsys(partsysptr);
}

LLGSENGINE_API void  r_setpartsysemitting(void *partsysptr, bool emit) {
	engine.r_setpartsysemitting(partsysptr,emit);
}

LLGSENGINE_API void  r_setpartsysvis(void *partsysptr, bool visible) {
	engine.r_setpartsysvis(partsysptr,visible);
}

LLGSENGINE_API void  c_init() {
	engine.c_init();
}

LLGSENGINE_API void  c_shutdown() {
	engine.c_shutdown();
}

LLGSENGINE_API void  c_enabledebugdrawer(bool enable) {
	engine.c_enabledebugdrawer(enable);
}

LLGSENGINE_API void *c_addsphere(float x, float y, float z, float radius, float mass, int mygrp, int grpmask) {
	return engine.c_addsphere(x,y,z,radius,mass,mygrp,grpmask);
}

LLGSENGINE_API void *c_addbox(float x, float y, float z, float halfext1, float halfext2, float halfext3, float mass, int mygrp, int grpmask) {
	return engine.c_addbox(x,y,z,halfext1,halfext2,halfext3,mass,mygrp,grpmask);
}

LLGSENGINE_API void *c_addcilinder(float x, float y, float z, float halfext1, float halfext2, float halfext3, float mass, int mygrp, int grpmask) {
	return engine.c_addcilinder(x,y,z,halfext1,halfext2,halfext3,mass,mygrp,grpmask);
}

LLGSENGINE_API void  c_synccolobjtoscenenode(void *colobjptr, void *scenenodeptr) {
	engine.c_synccolobjtoscenenode(colobjptr,scenenodeptr);
}

LLGSENGINE_API int c_collisiondetection() {
	return engine.c_collisiondetection();
}

LLGSENGINE_API void *c_getcollisionpairObjA(int index) {
	return engine.c_getcollisionpairObjA(index);
}

LLGSENGINE_API void *c_getcollisionpairObjB(int index) {
	return engine.c_getcollisionpairObjB(index);
}

LLGSENGINE_API void *r_createlight(char *name) {
	return engine.r_createlight(name);
}

LLGSENGINE_API void  r_destroylight(void *lightptr) {
	engine.r_destroylight(lightptr);
}

LLGSENGINE_API void  r_setlighttype(void *lightptr, char *type) {
	engine.r_setlighttype(lightptr,type);
}

LLGSENGINE_API void  r_setlightdiffusecolor(void *lightptr, float r, float g, float b) {
	engine.r_setlightdiffusecolor(lightptr,r,g,b);
}

LLGSENGINE_API void  r_setlightspecularcolor(void *lightptr, float r, float g, float b) {
	engine.r_setlightspecularcolor(lightptr,r,g,b);
}

LLGSENGINE_API void  r_setlightpos(void *lightptr, float x, float y, float z) {
	engine.r_setlightpos(lightptr,x,y,z);
}

LLGSENGINE_API void  r_setlightdirection(void *lightptr, float x, float y, float z) {
	engine.r_setlightdirection(lightptr,x,y,z);
}

LLGSENGINE_API void  r_movecameraforward(void *camptr, float dist) {
	engine.r_movecameraforward(camptr, dist);
}

LLGSENGINE_API void *c_addmeshgeom(float x, float y, float z, void *meshptr, float mass, int mygrp, int grpmask) {
	return engine.c_addmeshgeom(x,y,z,meshptr,mass,mygrp,grpmask);
}

