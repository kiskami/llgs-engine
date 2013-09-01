// llgs-engine
// Copyright (c) 2013 Kalman Kiss, Zalaegerszeg Hungary
// All rights reserved.
// kiskami@freemail.hu
//

#pragma once

namespace Ogre {
	class Root;
};

class LLGSEngine {
public:
	LLGSEngine(void) {}
	~LLGSEngine();

	void r_init(char *pluginsfile, char *configfile, char *logfile, char *rendersystem);

private:

	Ogre::Root *root;
};
