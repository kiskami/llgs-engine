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

LLGSENGINE_API void  r_createrenderwindow(char *title, int w, int h, bool fullscreen) {
	engine.r_createrenderwindow(title, w, h, fullscreen);
}

LLGSENGINE_API void  r_createscenemanager(char *type, char *name) {

}

LLGSENGINE_API void *r_createcamera(char *name) {
	return 0;
}

LLGSENGINE_API void  r_setcamerapos(void *camptr, float x, float y, float z) {

}

LLGSENGINE_API void  r_cameralookat(void *camptr, float x, float y, float z) {

}

LLGSENGINE_API void  r_setcameraneraclipdist(void *camptr, int dist) {

}

LLGSENGINE_API void  r_setcameraasviewport(void *camptr) {

}

LLGSENGINE_API void  r_setviewportbackground(void *camptr, float r, float g, float b) {

}

LLGSENGINE_API void  r_setambientlight(float r, float g, float b) {

}

LLGSENGINE_API void  r_renderoneframe() {

}

LLGSENGINE_API void  r_setskybox(char *materialname) {

}

LLGSENGINE_API void  r_screenshottofile(char *basename) {
	engine.r_screenshottofile(basename);
}

// -------------------------------
// Simple timer api
// after renderer init
LLGSENGINE_API void *t_createtimer() {
	return 0;
}

LLGSENGINE_API void  t_resettimer(void *timerptr) {

}

LLGSENGINE_API int   t_gettimermicroseconds(void *timerptr) {
	return 0;
}

// -------------------------------
// User input api
LLGSENGINE_API void  i_init() {

}

LLGSENGINE_API void  i_shutdown() {

}

LLGSENGINE_API void  i_captureinput() {

}

LLGSENGINE_API bool  i_keypressed(int key) {
	return false;
}

LLGSENGINE_API void  i_guiinput(bool enable) {

}

LLGSENGINE_API bool  i_leftmouse() {
	return false;
}

LLGSENGINE_API bool  i_rightmouse() {
	return false;
}

LLGSENGINE_API int   i_mousex() {
	return 0;
}

LLGSENGINE_API int   i_mousey() {
	return 0;
}

LLGSENGINE_API int   i_mouserelx() {
	return 0;
}

LLGSENGINE_API int   i_mouserely() {
	return 0;
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
