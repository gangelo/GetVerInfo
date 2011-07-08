//-------------------------------------------------------------------------------
// Pointer class
// Acts like a pointer. Cleans memory in destructor.
//
// Designed and coded by Gene M. Angelo
// Copyright (c) 2001 Gene M. Angelo
//
// This code is made public domain by the author it may be used in products 
// commercial or otherwise as long as all copyright notices remain in tact.
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
#include "stdafx.h"
#include "VFXPointer.h"

IMPLEMENT_DYNAMIC(CVFXPointer, CObject)

//-------------------------------------------------------------------------------
CVFXPointer::CVFXPointer(void* pPtr /* = NULL*/, bool bAutoDelete /* = true*/)	
	: m_pPtr(pPtr)
	, m_bAutoDelete(bAutoDelete)
	{
	}

//-------------------------------------------------------------------------------
CVFXPointer::~CVFXPointer()
	{
	if(m_bAutoDelete)
		{
		delete [] m_pPtr;
		m_pPtr = NULL;
		}
	}

//-------------------------------------------------------------------------------
bool CVFXPointer::IsNull() const
	{
	return m_pPtr == (void*)NULL;
	}

//-------------------------------------------------------------------------------
void* CVFXPointer::GetPtr()
	{
	return m_pPtr;
	}

//-------------------------------------------------------------------------------
void CVFXPointer::operator = (void* pPtr)
	{
	if(m_pPtr)
		{
		delete [] m_pPtr;
		m_pPtr = NULL;
		}

	m_pPtr = pPtr;
	}