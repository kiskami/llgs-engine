// simpletextpaneltest.cpp : Entry point for the console application.
//

#include "stdafx.h"

#include "llgs-engine.h"

#include <iostream>
#include <Windows.h>

#include "OGRE.h"

Ogre::OverlayElement* textBox;

void test () {
	std::cout << "1" << std::endl;

	//auto p = r_simpletextpanel("x", "Tesztszoveg","DroidSans-Bold",16,0,20,500,20);
	//std::cout << "2" << std::endl;
	//r_simpletextshow("x");
	//std::cout << "3" << std::endl;

	Ogre::Overlay*           st_overlay;
	Ogre::OverlayContainer*  st_panel;

	st_overlay = Ogre::OverlayManager::getSingleton().create("myst_overlay");
	std::cout << "1.1" << std::endl;
	st_panel = static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "myst_container"));
	std::cout << "1.2" << std::endl;
//	st_panel->setMetricsMode(Ogre::GMM_PIXELS);
	st_panel->setPosition(0, 0);
	std::cout << "1.3" << std::endl;
	st_panel->setDimensions(1, 1);
	std::cout << "1.4" << std::endl;
	st_overlay->add2D(st_panel);
	std::cout << "1.5" << std::endl;
	st_overlay->show();
	std::cout << "2" << std::endl;

	textBox = Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea","x");
	std::cout << "2.1" << std::endl;
	textBox->setMetricsMode(Ogre::GMM_PIXELS);
	std::cout << "2.2" << std::endl;
	textBox->setPosition(25, 25);
	std::cout << "2.3" << std::endl;
	textBox->setDimensions(1, 1);
	std::cout << "2.4" << std::endl;
	textBox->setParameter("font_name", "DroidSans-Bold");
	std::cout << "2.5" << std::endl;
	textBox->setParameter("char_height", "16");
	std::cout << "2.6" << std::endl;
	textBox->setColour(Ogre::ColourValue::White);
	std::cout << "2.7" << std::endl;

	textBox->setCaption("Tesztszoveg");
	std::cout << "2.8" << std::endl;

	st_panel->addChild(textBox);
	std::cout << "3" << std::endl;

}

int _tmain(int argc, _TCHAR* argv[])
{
	r_init("plugins_d.cfg" , "simpletextpaneltest.cfg", "simpletextpaneltest.log", "Direct3D9 Rendering Subsystem", "resources_d.cfg");

	r_createrenderwindow("simpletextpaneltest",640,480,false);

	r_createscenemanager("INTERIOR","simpletextpaneltest");

	test();

	auto cam = r_createcamera("camera");

	r_cameralookat(cam,0,0,0);

	r_setcameranearclipdist(cam,0.01);
	r_setcamerafarclipdist(cam,15000);

	r_setcameraasviewport(cam);

	r_setviewportbackground(0.5,1,0.5);

	r_setambientlight(0.15,0.15,0.15);

	r_setskybox("backgrounds/FirstSimpleStarField");


//	textBox->hide();

	r_renderoneframe();
	std::cout << "4" << std::endl;

	Sleep( 5000 );

	//textBox->show();

	//r_renderoneframe();

	//Sleep( 5000 );

	r_shutdown();
	return 0;
}

