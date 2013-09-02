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
LLGSENGINE_API void  r_createrenderwindow(char *title, int w, int h, bool fullscreen);
LLGSENGINE_API void  r_createscenemanager(char *type, char *name);

LLGSENGINE_API void *r_createcamera(char *name);
LLGSENGINE_API void  r_setcamerapos(void *camptr, float x, float y, float z);
LLGSENGINE_API void  r_cameralookat(void *camptr, float x, float y, float z);
LLGSENGINE_API void  r_setcameraneraclipdist(void *camptr, int dist);
LLGSENGINE_API void  r_setcameraasviewport(void *camptr);
LLGSENGINE_API void  r_setviewportbackground(void *camptr, float r, float g, float b);

LLGSENGINE_API void  r_setambientlight(float r, float g, float b);

LLGSENGINE_API void  r_renderoneframe();

LLGSENGINE_API void  r_setskybox(char *materialname);

LLGSENGINE_API void  r_screenshottofile(char *namebase);

// simple text output functions
LLGSENGINE_API void  r_simpletextpanel(char *id, char *txt, char *fontname, float x, float y, float w, float h);
LLGSENGINE_API void  r_simpletextsetcolor(char *id, float r, float g, float b);
LLGSENGINE_API void  r_simpletextshow(char *id);
LLGSENGINE_API void  r_simpletexthide(char *id);
LLGSENGINE_API void  r_simpletextsettext(char *id, char *txt);

// -------------------------------
// Simple timer api
// after renderer init
LLGSENGINE_API void *t_createtimer();
LLGSENGINE_API void  t_resettimer(void *timerptr);
LLGSENGINE_API int   t_gettimermicroseconds(void *timerptr);

// -------------------------------
// User input api
LLGSENGINE_API void  i_init();
LLGSENGINE_API void  i_shutdown();
LLGSENGINE_API void  i_captureinput();
LLGSENGINE_API bool  i_keypressed(int key);
LLGSENGINE_API void  i_guiinput(bool enable);
LLGSENGINE_API bool  i_leftmouse();
LLGSENGINE_API bool  i_rightmouse();
LLGSENGINE_API int   i_mousex();
LLGSENGINE_API int   i_mousey();
LLGSENGINE_API int   i_mouserelx();
LLGSENGINE_API int   i_mouserely();

// -------------------------------
// (CE)GUI api

// -------------------------------
// Physics (Bullet) api

// -------------------------------
// Sound (OpenAL) api

}; // extern "C"
