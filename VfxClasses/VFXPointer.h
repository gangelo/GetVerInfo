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
#ifndef _VFXPOINTER_H_
#define _VFXPOINTER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//-------------------------------------------------------------------------------
class CVFXPointer : public CObject  
	{
	DECLARE_DYNAMIC(CVFXPointer)
	public:
		CVFXPointer(void* pPtr = NULL, bool bAutoDelete = true);
		virtual ~CVFXPointer();

	public:
		void* GetPtr();
		bool IsNull() const;
		void operator = (void* pPtr);

	private:
		void* m_pPtr;
		bool m_bAutoDelete;
	};

#endif // #ifndef _VFXPOINTER_H_
