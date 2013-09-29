// llgs-engine
// Copyright (c) 2013 Kalman Kiss, Zalaegerszeg Hungary
// All rights reserved.
// kiskami@freemail.hu
//

#pragma once

#include "OGRE\Ogre.h"
#include "OIS\OIS.h"

class InputHandler : public OIS::KeyListener, public OIS::MouseListener , 
	public Ogre::WindowEventListener {
public:
	InputHandler(Ogre::RenderWindow* mWindow_);
	~InputHandler();

	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowMoved(Ogre::RenderWindow* rw);
	virtual bool windowClosing(Ogre::RenderWindow* rw);
	virtual void windowClosed(Ogre::RenderWindow* rw);
	virtual void windowFocusChange(Ogre::RenderWindow* rw);

	virtual bool keyPressed(const OIS::KeyEvent& evt);
	virtual bool keyReleased(const OIS::KeyEvent& evt);
	virtual bool mouseMoved(const OIS::MouseEvent& evt);
	virtual bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id);

	void i_captureinput();

	int i_keypressed(int key);
	int i_anykeypressed();

	int  i_leftmouse();
	int  i_middlemouse();
	int  i_rightmouse();
	int   i_mousex();
	int   i_mousey();
	int   i_mouserelx();
	int   i_mouserely();

private:

	void shutdown();

	Ogre::RenderWindow* mWindow;    // render window
	OIS::InputManager* mInputMgr;   // OIS input manager

	OIS::Keyboard* mKeyboard;       // keyboard device
	OIS::Mouse* mMouse;             // mouse device 

#define MAX_MOUSEBTN OIS::MB_Middle+1

	// a 3 standard egérgombot támogatjuk
	bool mousebuttons[MAX_MOUSEBTN];

	int mousex, mousey
		, relmousex, relmousey;

#define MAX_KEYS OIS::KC_MEDIASELECT+1

	bool keys[MAX_KEYS];
};
