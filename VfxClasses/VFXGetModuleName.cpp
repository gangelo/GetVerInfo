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
#include "stdafx.h"
#include <Psapi.h>
#include "VFXGetModuleName.h"

//-------------------------------------------------------------------------------
CVFXGetModuleName::CVFXGetModuleName()
	{
	}

//-------------------------------------------------------------------------------
CVFXGetModuleName::~CVFXGetModuleName()
	{
	}

//-------------------------------------------------------------------------------
bool CVFXGetModuleName::GetModuleName(CString& sModuleName, HANDLE hHandle /* = NULL*/, HMODULE hModule /* = NULL*/)
	{
	sModuleName = "";

	// Get the process handle
	if(! hHandle)		
		hHandle = ::GetCurrentProcess();
		
	// Get the module handle
	if(! hModule)		
		hModule = ::GetModuleHandle(NULL);
	
	// Have to have process and module handle
	if(! hHandle && ! hModule)
		return false;

	// Get the module name
	LPTSTR p = sModuleName.GetBuffer(MAX_PATH + 1);	
	DWORD rc = GetModuleFileNameEx(hHandle, hModule, p, (DWORD)MAX_PATH);	

	// Release buffer
	sModuleName.ReleaseBuffer();

	return rc > 0;
	}



