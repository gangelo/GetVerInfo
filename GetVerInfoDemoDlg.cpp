// GetVerInfoDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GetVerInfoDemo.h"
#include "GetVerInfoDemoDlg.h"

#include "VFXVersionInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetVerInfoDemoDlg dialog

CGetVerInfoDemoDlg::CGetVerInfoDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetVerInfoDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetVerInfoDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetVerInfoDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetVerInfoDemoDlg)
	DDX_Control(pDX, IDC_LIST_VS_VERSION_INFO, m_listVsVersionInfo);
	DDX_Control(pDX, IDC_EDIT_MODULE_NAME, m_editModuleName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGetVerInfoDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CGetVerInfoDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClearListBox)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_MODULE, OnButtonOpenModule)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetVerInfoDemoDlg message handlers

BOOL CGetVerInfoDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	m_listVsVersionInfo.SetHorizontalExtent(500);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGetVerInfoDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGetVerInfoDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGetVerInfoDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGetVerInfoDemoDlg::OnOK() 
	{
	// TODO: Add extra validation here
	CString sModuleName;
	CVFXVersionRes VersionRes;
	CVFXVersionInfo VersionInfo;

	m_editModuleName.GetWindowText(sModuleName);

	sModuleName.TrimLeft();
	sModuleName.TrimRight();

	// Note: passing NULL as a module name here will return the 
	// version information for the current module
	if(VersionInfo.GetVersionInfo(VersionRes, 
		sModuleName.IsEmpty() ? (LPCTSTR)NULL : (LPCTSTR)sModuleName))
		{
        // Display the whole VS_VERSION_INFO block   		
		m_listVsVersionInfo.AddString("*---------------------------------------------------------*");
		m_listVsVersionInfo.AddString("ModuleName: " + VersionRes.m_sModuleName);
		m_listVsVersionInfo.AddString("FileVersion: " + VersionRes.m_sFileVersion);
		m_listVsVersionInfo.AddString("ProdVersion: " + VersionRes.m_sProdVersion);
		m_listVsVersionInfo.AddString("CompanyName: " + VersionRes.m_sCompanyName);
		m_listVsVersionInfo.AddString("FileDescription: " + VersionRes.m_sFileDescription);
		m_listVsVersionInfo.AddString("InternalName: " + VersionRes.m_sInternalName);
		m_listVsVersionInfo.AddString("LegalCopyright: " + VersionRes.m_sLegalCopyright);
		m_listVsVersionInfo.AddString("OriginalFileName: " + VersionRes.m_sOriginalFileName);
		m_listVsVersionInfo.AddString("ProductName: " + VersionRes.m_sProductName);
		m_listVsVersionInfo.AddString("Comments: " + VersionRes.m_sComments);
		m_listVsVersionInfo.AddString("PrivateBuild: " + VersionRes.m_sPrivateBuild);
		m_listVsVersionInfo.AddString("PrivateBuild: " + VersionRes.m_sPrivateBuild);
		m_listVsVersionInfo.AddString("SpecialBuild: " + VersionRes.m_sSpecialBuild);

		int nCount = m_listVsVersionInfo.GetCount();
		if(nCount > 0)
			m_listVsVersionInfo.SetCurSel(nCount - 1);
		}
	else
		AfxMessageBox("Module not found, or version info not found", MB_OK | MB_ICONERROR);
		
	// CDialog::OnOK();
	}

void CGetVerInfoDemoDlg::OnButtonClearListBox() 
	{
	m_listVsVersionInfo.ResetContent();	
	}

void CGetVerInfoDemoDlg::OnButtonOpenModule() 
	{
	DWORD nFlags;
	static char szFilter[] = "*.exe (Exe Files)|*.exe|*.dll (Dll Files)|*.dll|*.* (All Files)|*.*||";
 	
	// Set our flags.
	nFlags = OFN_HIDEREADONLY | OFN_NOCHANGEDIR | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	
	// Set the dialog title.	
	CFileDialog FileDialog(true,  _T("exe"), NULL, nFlags, szFilter, AfxGetMainWnd());

	
	FileDialog.m_ofn.lpstrTitle = _T("Open Module");

	// Display the dialog.
	int nLastUserButton = FileDialog.DoModal();

	if(CommDlgExtendedError() != 0)
		{
		AfxMessageBox("Error Common Control: CFileDialog", MB_OK | MB_ICONERROR);
		return;
		}

	if(nLastUserButton == IDOK)
		m_editModuleName.SetWindowText(FileDialog.GetPathName());	
	}
