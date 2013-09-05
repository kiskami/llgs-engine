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

LLGSENGINE_API void  r_cameralookat(void *camptr, float x, float y, float z) {
	engine.r_cameralookat(camptr,x,y,z);
}

LLGSENGINE_API void  r_setcameraneraclipdist(void *camptr, float dist) {
	engine.r_setcameraneraclipdist(camptr,dist);
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
LLGSENGINE_API void  r_simpletextpanel(char *id, char *txt, char *fontname, float x, float y, float w, float h) {

}

LLGSENGINE_API void  r_simpletextsetcolor(char *id, float r, float g, float b) {

}

LLGSENGINE_API void  r_simpletextshow(char *id) {

}

LLGSENGINE_API void  r_simpletexthide(char *id) {

}

LLGSENGINE_API void  r_simpletextsettext(char *id, char *txt) {

}
