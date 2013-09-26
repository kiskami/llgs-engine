// simpletextpaneltest.cpp : Entry point for the console application.
//

#include "stdafx.h"

#include "llgs-engine.h"

#include <iostream>
#include <Windows.h>

#include "OGRE.h"

Ogre::OverlayElement* textBox;

void testSimpleText () {

	//auto p = r_simpletextpanel("x", "Tesztszoveg","DroidSans-Bold",16,0,20,500,20);
	//std::cout << "2" << std::endl;
	//r_simpletextshow("x");
	//std::cout << "3" << std::endl;

	Ogre::Overlay*           st_overlay;
	Ogre::OverlayContainer*  st_panel;

	st_overlay = Ogre::OverlayManager::getSingleton().create("myst_overlay");
	std::cout << "1.1" << std::endl;
	st_panel = static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "myst_container"));
//	st_panel->setMetricsMode(Ogre::GMM_PIXELS);
	st_panel->setPosition(0, 0);
	st_panel->setDimensions(1, 1);
	st_overlay->add2D(st_panel);
	st_overlay->show();

	textBox = Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea","x");
	textBox->setMetricsMode(Ogre::GMM_PIXELS);
	textBox->setPosition(25, 25);
	textBox->setDimensions(1, 1);
	textBox->setParameter("font_name", "DroidSans-Bold");
	textBox->setParameter("char_height", "16");
	textBox->setColour(Ogre::ColourValue::White);

	textBox->setCaption("Tesztszoveg");

	st_panel->addChild(textBox);

}

void testExplosion () {
	auto node = r_createchildscenenode(r_getrootscenenode(),"exptest",0,0);
//	r_setscenenodescale(node,2,2,2);

	auto billset = r_createbillboardset();
	r_setbillboarddefdims(billset,0.2,0.2);

	r_setbillboardmaterial(billset,"Explosion33");
	int stacks = 8, slices = 8;
	r_setbillboardsetstacksandslices(billset,stacks,slices);

//	r_setbillboardmaterial(billset,"Examples/Flare");

	r_attachmoveable(node,billset);

	auto billb = r_createbillboard(billset,0,0,0,1,1,1);
	r_setbillboardtextcoodrdindex(billset,billb,0);

	for(int i = 0; i < slices*stacks; ++i) {
		r_setbillboardtextcoodrdindex(billset,billb,i);
		r_renderoneframe();
		Sleep(1000/24);
	}

		r_renderoneframe();
		Sleep(3000);
}

int _tmain(int argc, _TCHAR* argv[])
{
	r_init("plugins_d.cfg" , "simpletextpaneltest.cfg", "simpletextpaneltest.log", "Direct3D9 Rendering Subsystem", "resources_d.cfg");

	r_createrenderwindow("simpletextpaneltest",800,600,false);

	r_createscenemanager("INTERIOR","simpletextpaneltest");

	testSimpleText();

	auto cam = r_createcamera("camera");

	r_setcamerapos(cam,1,1,0);
	r_cameralookat(cam,0,0,0);

	r_setcameranearclipdist(cam,0.01);
	r_setcamerafarclipdist(cam,15000);

	r_setcameraasviewport(cam);

	r_setviewportbackground(0.5,1,0.5);

	r_setambientlight(0.15,0.15,0.15);

	r_setskybox("backgrounds/FirstSimpleStarField");


//	textBox->hide();

	r_renderoneframe();

	Sleep( 5000 );

	//textBox->show();

	//r_renderoneframe();

	testExplosion();

	//Sleep( 5000 );

	r_shutdown();
	return 0;
}

