// llgs-engine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "llgs-engine.h"


// This is an example of an exported variable
//LLGSENGINE_API int nllgsengine=0;

// This is an example of an exported function.
LLGSENGINE_API int fnllgsengine(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see llgs-engine.h for the class definition
//Cllgsengine::Cllgsengine()
//{
//	return;
//}
