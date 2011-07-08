// GetVerInfoDemo.h : main header file for the GETVERINFODEMO application
//

#if !defined(AFX_GETVERINFODEMO_H__51C83110_E35F_4A40_BA41_4402D54C58A9__INCLUDED_)
#define AFX_GETVERINFODEMO_H__51C83110_E35F_4A40_BA41_4402D54C58A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGetVerInfoDemoApp:
// See GetVerInfoDemo.cpp for the implementation of this class
//

class CGetVerInfoDemoApp : public CWinApp
{
public:
	CGetVerInfoDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetVerInfoDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGetVerInfoDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETVERINFODEMO_H__51C83110_E35F_4A40_BA41_4402D54C58A9__INCLUDED_)
