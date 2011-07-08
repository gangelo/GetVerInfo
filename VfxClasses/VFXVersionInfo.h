//-------------------------------------------------------------------------------
// Get Module Version Information class
// Get the module version information block information.
//
// Designed and coded by Gene M. Angelo
// Copyright (c) 2001 Gene M. Angelo
//
// This code is made public domain by the author it may be used in products 
// commercial or otherwise as long as all copyright notices remain in tact.
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
#ifndef _VFXVERSIONINFO_H_
#define _VFXVERSIONINFO_H_

//-------------------------------------------------------------------------------
#pragma comment(lib, "version.lib")
#pragma comment(lib, "shlwapi.lib")

//-------------------------------------------------------------------------------
class CVFXVersionRes
	{
	public:
		CVFXVersionRes() 
			{
			Empty();
			}

		virtual ~CVFXVersionRes() {}

	public:
		virtual void Display(bool bToStdOut = false)
			{
			CString sDisplay = GetDisplay();			

			// Display it
			if(bToStdOut)
				::printf("%s", (LPCTSTR)sDisplay);
			else
				AfxMessageBox(sDisplay, MB_OK | MB_ICONINFORMATION);
			}

		virtual void Empty()
			{
			m_sModuleName		= _T("");
			m_nFileVersion[0]	= 0;
			m_nFileVersion[1]	= 0;
			m_nFileVersion[2]	= 0;
			m_nFileVersion[3]	= 0;
			m_nProdVersion[0]	= 0;
			m_nProdVersion[1]	= 0;
			m_nProdVersion[2]	= 0;
			m_nProdVersion[3]	= 0;
			m_sFileVersion		= _T("");
			m_sProdVersion		= _T("");
			m_sCompanyName		= _T("");
			m_sFileDescription	= _T("");
			m_sInternalName		= _T("");
			m_sLegalCopyright	= _T("");
			m_sOriginalFileName = _T("");
			m_sProductName		= _T("");
			m_sComments			= _T("");
			m_sLegalTradeMarks	= _T("");
			m_sPrivateBuild		= _T("");
			m_sSpecialBuild		= _T("");
			}

		virtual bool IsEmpty()
			{
			if(	m_sModuleName		== _T("") &&
				m_nFileVersion[0]	== 0 &&
				m_nFileVersion[1]	== 0 &&
				m_nFileVersion[2]	== 0 &&
				m_nFileVersion[3] 	== 0 &&
				m_nProdVersion[0]	== 0 &&
				m_nProdVersion[1]	== 0 &&
				m_nProdVersion[2]	== 0 &&
				m_nProdVersion[3]	== 0 &&
				m_sFileVersion		== _T("") &&
				m_sProdVersion		== _T("") &&
				m_sCompanyName		== _T("") &&
				m_sFileDescription	== _T("") &&
				m_sInternalName		== _T("") &&
				m_sLegalCopyright	== _T("") &&
				m_sOriginalFileName == _T("") &&
				m_sProductName		== _T("") &&
				m_sComments			== _T("") &&
				m_sLegalTradeMarks	== _T("") &&
				m_sPrivateBuild		== _T("") &&
				m_sSpecialBuild		== _T(""))
				return true;
			else
				return false;
			}

		virtual void operator = (const CVFXVersionRes& VersionRes)
			{
			m_sModuleName		= VersionRes.m_sModuleName;
			m_nFileVersion[0]	= VersionRes.m_nFileVersion[0];
			m_nFileVersion[1]	= VersionRes.m_nFileVersion[1];
			m_nFileVersion[2]	= VersionRes.m_nFileVersion[2];
			m_nFileVersion[3]	= VersionRes.m_nFileVersion[3];
			m_nProdVersion[0]	= VersionRes.m_nProdVersion[0];
			m_nProdVersion[1]	= VersionRes.m_nProdVersion[1];
			m_nProdVersion[2]	= VersionRes.m_nProdVersion[2];
			m_nProdVersion[3]	= VersionRes.m_nProdVersion[3];
			m_sFileVersion		= VersionRes.m_sFileVersion;
			m_sProdVersion		= VersionRes.m_sProdVersion;
			m_sCompanyName		= VersionRes.m_sCompanyName;
			m_sFileDescription	= VersionRes.m_sFileDescription;
			m_sInternalName		= VersionRes.m_sInternalName;
			m_sLegalCopyright	= VersionRes.m_sLegalCopyright;
			m_sOriginalFileName = VersionRes.m_sOriginalFileName;
			m_sProductName		= VersionRes.m_sProductName;
			m_sComments			= VersionRes.m_sComments;
			m_sLegalTradeMarks	= VersionRes.m_sPrivateBuild;
			m_sPrivateBuild		= VersionRes.m_sPrivateBuild;
			m_sSpecialBuild		= VersionRes.m_sSpecialBuild;
			}

	private:
		virtual CString GetDisplay()
			{
			CString sDisplay;

			if(IsEmpty())
				sDisplay = _T("No version information is available");
			else
				{
				sDisplay.Format(_T(
					"VS_VERSION_INFO for %s:\n\n"					
					"FileVersion: %s\n"
					"ProductVersion: %s\n"
					"CompanyName: %s\n"
					"FileDescription: %s\n"
					"InternalName: %s\n"
					"LegalCopyright: %s\n"
					"OriginalFileName: %s\n"
					"ProductName: %s\n"
					"Comments %s\n"
					"LegalTradeMarks: %s\n"
					"PrivateBuild: %s\n"
					"SpecialBuild: %s\n"),
					m_sModuleName,
					m_sFileVersion,
					m_sProdVersion,
					m_sCompanyName,
					m_sFileDescription,
					m_sInternalName,
					m_sLegalCopyright,
					m_sOriginalFileName,
					m_sProductName,
					m_sComments,
					m_sLegalTradeMarks,
					m_sPrivateBuild,
					m_sSpecialBuild);
				}

			return sDisplay;
			}

	public:
		CString m_sModuleName;			// NOT from the VS_VERSION_INFO block. This is the original module name queried.
		WORD m_nFileVersion[4];			// From the FILEVERSION of the version info resource.	
		WORD m_nProdVersion[4];			// From the PRODUCTVERSION of the version info resource.
		CString m_sFileVersion;			// From the StringFileInfo\\FileVersion block of the version info resource.
		CString m_sProdVersion;			// From the StringFileInfo\\ProductVersion block of the version info resource.	
		CString m_sCompanyName;			// From the StringFileInfo\\CompanyName block of the version info resource.	
		CString m_sFileDescription;		// From the StringFileInfo\\FileDescription block of the version info resource.	
		CString m_sInternalName;		// From the StringFileInfo\\InternalName block of the version info resource.	
		CString m_sLegalCopyright;		// From the StringFileInfo\\LegalCopyright block of the version info resource.	
		CString m_sOriginalFileName;	// From the StringFileInfo\\OriginalFilename  block of the version info resource.	
		CString m_sProductName;			// From the StringFileInfo\\ProductName block of the version info resource.	
		CString m_sComments;			// From the StringFileInfo\\Comments block of the version info resource.	
		CString m_sLegalTradeMarks;		// From the StringFileInfo\\LegalTrademarks block of the version info resource.	
		CString m_sPrivateBuild;		// From the StringFileInfo\\PrivateBuild block of the version info resource.	
		CString m_sSpecialBuild;		// From the StringFileInfo\\PrivateBuild block of the version info resource.		
	};

//-------------------------------------------------------------------------------
class CVFXVersionInfo : public CObject
	{
	DECLARE_DYNAMIC(CVFXVersionInfo);
	public:			
		enum 
			{
			// Codepages to use. use these enums as the uCodePage parameters in the 
			// constructor.  Other code pages may be used. Please add any valid code 
			// page below as needed. Please adhere to the naming convention below
			ENGLISH_UNICODE_US		=0x04b0,
			ENGLISH_UNICODE_UK		=0x04b0,
			ENGLISH_MULTILINGUAL_US	=0x04e4,
			ENGLISH_MULTILINGUAL_UK	=0x04e4					
			};

	public:
		CVFXVersionInfo(UINT uCodePage = ENGLISH_UNICODE_US, LANGID nLangId = MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US));
		virtual ~CVFXVersionInfo();

	public:		
		// Passing NULL gets the version of the current module
		bool GetVersionInfo(CVFXVersionRes& VersionRes, LPCTSTR pModuleName = NULL);
		
	private:		
		bool GetFileVersionInfo(CString& sModuleName, DWORD nBufSize, PVOID pBuf);	
		bool GetStringFileInfo(VS_FIXEDFILEINFO* pFixedInfo, PVOID pBuf, LPCTSTR pResource, LPTSTR pString, UINT nStringLen);
		DWORD GetFileVersionInfoSize(CString& sModuleName);	
		PVOID AllocPtr(DWORD nVerInfoBlockSize);
				
	private:	
		LANGID m_nLangId;
		UINT m_uCodePage;
		LCID m_nOldLocale;
		LCID m_nNewLocale;
		
	private:
		static const int m_nMaxBuf;
	};

#endif // _VFXVERSIONINFO_H_
