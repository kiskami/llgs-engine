// llgs-engine
// Copyright (c) 2013 Kalman Kiss, Zalaegerszeg Hungary
// All rights reserved.
// kiskami@freemail.hu
//

#include "stdafx.h"

#include "InputHandler.h"

InputHandler::InputHandler(Ogre::RenderWindow* mWindow_) 
	: mWindow(mWindow_)
	, mousex(0), mousey(0), relmousex(0), relmousey(0)
	, mKeyboard(0)
	, mMouse(0) {
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	OIS::ParamList pl;
	size_t winHandle = 0;
	std::ostringstream winHandleStr;

	mWindow->getCustomAttribute("WINDOW", &winHandle);
	winHandleStr << winHandle;

	pl.insert(std::make_pair("WINDOW", winHandleStr.str()));

	mInputMgr = OIS::InputManager::createInputSystem(pl);

	mKeyboard = static_cast<OIS::Keyboard*>(mInputMgr->createInputObject(OIS::OISKeyboard, true));
	// we use Unicode for character input!
	mKeyboard->setTextTranslation(OIS::Keyboard::TextTranslationMode::Unicode);
	mMouse = static_cast<OIS::Mouse*>(mInputMgr->createInputObject(OIS::OISMouse, true));

	for(int i = 0; i<MAX_KEYS; ++i) keys[i] = false;
	for(int i = 0; i<MAX_MOUSEBTN; ++i) mousebuttons[i] = false;

	mKeyboard->setEventCallback(this);
	mMouse->setEventCallback(this);

	windowResized(mWindow);    // do an initial adjustment of mouse area
}

InputHandler::~InputHandler() {
	if (mInputMgr) {
		shutdown();
	}
}

void InputHandler::windowResized(Ogre::RenderWindow* rw) {
		const OIS::MouseState& ms = mMouse->getMouseState();
		ms.width = rw->getWidth();
		ms.height = rw->getHeight();
}

// window event callbacks

void InputHandler::windowMoved(Ogre::RenderWindow* rw) {

}

bool InputHandler::windowClosing(Ogre::RenderWindow* rw) {
		return true;
}

void InputHandler::windowClosed(Ogre::RenderWindow* rw)	{

		//Only close for window that created OIS (the main window in these demos)
		if( rw == mWindow )
		{
			shutdown();
		}
	}

void InputHandler::shutdown() {
		// remove window event listener before shutting down OIS
		Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);

		if (mInputMgr) {
			mInputMgr->destroyInputObject(mKeyboard);
			mInputMgr->destroyInputObject(mMouse);

			OIS::InputManager::destroyInputSystem(mInputMgr);
			mInputMgr = 0;
		}
}

void InputHandler::windowFocusChange(Ogre::RenderWindow* rw) {
}

bool InputHandler::keyPressed(const OIS::KeyEvent& evt)	{
	if(evt.key>MAX_KEYS) return false;
	keys[evt.key] = true;
	return true;
}

bool InputHandler::keyReleased(const OIS::KeyEvent& evt) {
	if(evt.key>MAX_KEYS) return false;
	keys[evt.key] = false;
	return true;
}

bool InputHandler::mouseMoved(const OIS::MouseEvent& evt) {
	mousex = evt.state.X.abs;
	mousey = evt.state.Y.abs;
	relmousex = evt.state.X.rel;
	relmousey = evt.state.Y.rel;
	return true;
}

bool InputHandler::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id) {
	if(id>MAX_MOUSEBTN) return false;
	mousebuttons[id] = true;
	return true;
}

bool InputHandler::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id) {
	if(id>MAX_MOUSEBTN) return false;
	mousebuttons[id] = false;
	return true;
}

void InputHandler::i_captureinput() {
		mKeyboard->capture();
		mMouse->capture();
}

//#include <iostream>

int InputHandler::i_keypressed(int key) {
	if(key>MAX_KEYS) return false;
//	std::cout << "InputHandler::i_keypressed " << key << " => " << keys[key] << std::endl;
	return keys[key]?1:0;
}

int  InputHandler::i_leftmouse() {
	return mousebuttons[OIS::MB_Left]?1:0;
}

int  InputHandler::i_middlemouse() {
	return mousebuttons[OIS::MB_Middle]?1:0;
}

int  InputHandler::i_rightmouse() {
	return mousebuttons[OIS::MB_Right]?1:0;
}

int   InputHandler::i_mousex() {
	return mousex;
}

int   InputHandler::i_mousey() {
	return mousey;
}

int   InputHandler::i_mouserelx() {
	return relmousex;
}

int   InputHandler::i_mouserely() {
	return relmousey;
}
