// GetVerInfoDemoDlg.h : header file
//

#if !defined(AFX_GETVERINFODEMODLG_H__2A32B5B1_E883_426A_A410_D62ABC130B5B__INCLUDED_)
#define AFX_GETVERINFODEMODLG_H__2A32B5B1_E883_426A_A410_D62ABC130B5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGetVerInfoDemoDlg dialog

class CGetVerInfoDemoDlg : public CDialog
{
// Construction
public:
	CGetVerInfoDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGetVerInfoDemoDlg)
	enum { IDD = IDD_GETVERINFODEMO_DIALOG };
	CListBox	m_listVsVersionInfo;
	CEdit	m_editModuleName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetVerInfoDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGetVerInfoDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButtonClearListBox();
	afx_msg void OnButtonOpenModule();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETVERINFODEMODLG_H__2A32B5B1_E883_426A_A410_D62ABC130B5B__INCLUDED_)
