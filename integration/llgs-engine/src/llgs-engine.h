// llgs-engine dll header
// Copyright (c) 2013 Kalman Kiss, Zalaegerszeg Hungary
// All rights reserved.
// kiskami@freemail.hu
//
#ifdef LLGSENGINE_EXPORTS
#define LLGSENGINE_API __declspec(dllexport)
#else
#define LLGSENGINE_API __declspec(dllimport)
#endif

extern "C" {

// This class is exported from the llgs-engine.dll
//class LLGSENGINE_API Cllgsengine {
//public:
//	Cllgsengine(void);
//	// TODO: add your methods here.
//};

//extern LLGSENGINE_API int nllgsengine;

LLGSENGINE_API int fnllgsengine(void);

};
