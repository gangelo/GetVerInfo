//-------------------------------------------------------------------------------
// Get Module Name class
// Get the module name given a module handle and process id.
//
// Designed and coded by Gene M. Angelo
// Copyright (c) 2001 Gene M. Angelo
//
// This code is made public domain by the author it may be used in products 
// commercial or otherwise as long as all copyright notices remain in tact.
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
#ifndef _VFXGETMODULENAME_H_
#define _VFXGETMODULENAME_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//-------------------------------------------------------------------------------
#pragma comment(lib, "Psapi.lib")

//-------------------------------------------------------------------------------
class CVFXGetModuleName : public CObject  
	{
	public:
		CVFXGetModuleName();
		virtual ~CVFXGetModuleName();

	public:
		bool GetModuleName(CString& sModuleName, HANDLE hProcess = NULL, HMODULE hModule = NULL);
	};

#endif // #ifndef _VFXGETMODULENAME_H_
