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
#include "stdafx.h"
#include "VFXVersionInfo.h"
#include "VFXGetModuleName.h"
#include "VFXPointer.h"
#include "Shlwapi.h"

//-------------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(CVFXVersionInfo,CObject);

//-------------------------------------------------------------------------------
const int CVFXVersionInfo::m_nMaxBuf = 256;

//-------------------------------------------------------------------------------
// Note: Pass the language id and code page of the resource you want to query.
CVFXVersionInfo::CVFXVersionInfo(UINT uCodePage /* = ENGLISH_UNICODE_US*/, LANGID nLangId /* = MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US)*/)
	{
	LCID lcid = MAKELCID(MAKELANGID(PRIMARYLANGID(nLangId), SUBLANGID(nLangId)), SORT_DEFAULT);	
	m_nLangId = nLangId;	
	m_nNewLocale = (! ::IsValidLocale(lcid, LCID_INSTALLED)) ? ::GetThreadLocale() : lcid;	
	m_nOldLocale = ::GetThreadLocale();		

	if (::SetThreadLocale(m_nNewLocale) == 0 /*error*/)	
		::SetThreadLocale(m_nOldLocale);	

	// Note: we are not worrying about whether or not the code page is valid
	// or not. The calling application should know this. Even though the
	// code page may not be valid (installed) if there is a resource available
	// for the code page, it will be found regardless.	
	// m_uCodePage = ! ::IsValidCodePage(uCodePage) ? ::GetACP() : uCodePage;
	m_uCodePage = uCodePage;	
	}

//-------------------------------------------------------------------------------
// Destructor
CVFXVersionInfo::~CVFXVersionInfo()
	{
	// Reset the default language settings.
	::SetThreadLocale(m_nOldLocale);
	}

//-------------------------------------------------------------------------------
// Allocates memory for the version infomation resources that will be needed
// based on the resource size.
PVOID CVFXVersionInfo::AllocPtr(DWORD nVerInfoBlockSize)
	{
	if(! nVerInfoBlockSize)
		return (PVOID)NULL;	
	return (PVOID)new char[nVerInfoBlockSize];
	}

//-------------------------------------------------------------------------------
// Obtain a string resource from the VERSIONINFO block.
bool CVFXVersionInfo::GetStringFileInfo(VS_FIXEDFILEINFO* pFixedInfo, PVOID pBuf, LPCTSTR pResource, LPTSTR pString, UINT nStringLen)
	{
	char s[m_nMaxBuf];
	unsigned int uInfoSize = 0;

	// Initializs the string buffer right off the bat.
	::ZeroMemory(pString, nStringLen);

	// Get the internal name from the StringFileInfo\\InternalName block of the version info resource.
	::sprintf((LPTSTR)s, _T("\\StringFileInfo\\%04x%04x\\%s"), m_nLangId, m_uCodePage, pResource);

	// Query the string resource.
	if(::VerQueryValue(pBuf, (LPTSTR)s, (void**)&pFixedInfo, &uInfoSize) == 0 /*not found*/)			
		return false;
	// Do we have a valid string?
	if(! AfxIsValidString((LPCSTR)pFixedInfo))
		return false;
	
	// Make sure we dont leak any memory.
	if(::strlen((LPCSTR)pFixedInfo) < nStringLen)
		::strcpy(pString, (LPCSTR)pFixedInfo);	// The dest buffer can hold the src string.	
	else		
		::strncpy(pString, (LPCSTR)pFixedInfo, nStringLen - 1);	// The dest buffer is smaller than the src string.	

	return true;
	}

//-------------------------------------------------------------------------------
// Retrieve the version information from the version information resource. The 
// VERINFOBLOCK returns 2 Product Version and 2 File Version resource values. See
// below comments and comments in the header file for details. This version returns 
// the info for a given file
bool CVFXVersionInfo::GetVersionInfo(CVFXVersionRes& VersionRes, LPCTSTR pModuleName /* = NULL*/)		
	{	
	CVFXPointer Pointer;
	unsigned int uInfoSize	= 0;	
	VS_FIXEDFILEINFO FixedFileInfo;
	VS_FIXEDFILEINFO* pFixedInfo = &FixedFileInfo;	
	CString sModuleName(pModuleName);

	VersionRes.Empty();	

	// Trim any spaces
	sModuleName.TrimLeft();
	sModuleName.TrimRight();
	
	// Use the passed module name or this module name?
	if(! sModuleName.IsEmpty())
		{		
		// Check if module exists
		if(! ::PathFileExists(sModuleName))
			return false;
		}
	else
		{
		// Get this module
		CVFXGetModuleName GetModuleName;
		if(! GetModuleName.GetModuleName(sModuleName))			
			return false;			
		}	

	// Get the size of the Version Information Block
	// so that w can allocate memory for the Block pointer
	DWORD nVerInfoBlockSize = GetFileVersionInfoSize(sModuleName);

	if(nVerInfoBlockSize == 0)
		return false;

	// Allocate the Block pointer
	Pointer = AllocPtr(nVerInfoBlockSize);	

	if(Pointer.IsNull())
		return false;

	// Initialize the Block pointer with the address of the
	// Version Information Block of the module
	if(GetFileVersionInfo(sModuleName, nVerInfoBlockSize, Pointer.GetPtr()) == 0)
		return false;
		
	// Query the PRODUCTVERSION string of the Version Information Block resource
	if (::VerQueryValue(Pointer.GetPtr(), (LPTSTR)_T("\\"), (void**)&pFixedInfo, &uInfoSize) == 0)
		return false;

	// Populate the module name
	VersionRes.m_sModuleName = sModuleName;
		
	// Product version from the FILEVERSION of the version info resource	
	VersionRes.m_nProdVersion[0] = HIWORD(pFixedInfo->dwProductVersionMS);	
	VersionRes.m_nProdVersion[1] = LOWORD(pFixedInfo->dwProductVersionMS);
	VersionRes.m_nProdVersion[2] = HIWORD(pFixedInfo->dwProductVersionLS);
	VersionRes.m_nProdVersion[3] = LOWORD(pFixedInfo->dwProductVersionLS);	

	// File version from the PRODUCTVERSION of the version info resource
	VersionRes.m_nFileVersion[0] = HIWORD(pFixedInfo->dwFileVersionMS);		
	VersionRes.m_nFileVersion[1] = LOWORD(pFixedInfo->dwFileVersionMS);
	VersionRes.m_nFileVersion[2] = HIWORD(pFixedInfo->dwFileVersionLS);
	VersionRes.m_nFileVersion[3] = LOWORD(pFixedInfo->dwFileVersionLS);	

	// Get some of the string resources
	GetStringFileInfo(pFixedInfo, Pointer.GetPtr(), _T("ProductVersion"),	(LPTSTR)VersionRes.m_sProdVersion.GetBuffer(m_nMaxBuf),			m_nMaxBuf);
	GetStringFileInfo(pFixedInfo, Pointer.GetPtr(), _T("FileVersion"),		(LPTSTR)VersionRes.m_sFileVersion.GetBuffer(m_nMaxBuf),			m_nMaxBuf);
	GetStringFileInfo(pFixedInfo, Pointer.GetPtr(), _T("CompanyName"),		(LPTSTR)VersionRes.m_sCompanyName.GetBuffer(m_nMaxBuf),			m_nMaxBuf);
	GetStringFileInfo(pFixedInfo, Pointer.GetPtr(), _T("FileDescription"),	(LPTSTR)VersionRes.m_sFileDescription.GetBuffer(m_nMaxBuf),		m_nMaxBuf);
	GetStringFileInfo(pFixedInfo, Pointer.GetPtr(), _T("InternalName"),		(LPTSTR)VersionRes.m_sInternalName.GetBuffer(m_nMaxBuf),		m_nMaxBuf);
	GetStringFileInfo(pFixedInfo, Pointer.GetPtr(), _T("LegalCopyright"),	(LPTSTR)VersionRes.m_sLegalCopyright.GetBuffer(m_nMaxBuf),		m_nMaxBuf);
	GetStringFileInfo(pFixedInfo, Pointer.GetPtr(), _T("OriginalFilename"),	(LPTSTR)VersionRes.m_sOriginalFileName.GetBuffer(m_nMaxBuf),	m_nMaxBuf);
	GetStringFileInfo(pFixedInfo, Pointer.GetPtr(), _T("ProductName"),		(LPTSTR)VersionRes.m_sProductName.GetBuffer(m_nMaxBuf),			m_nMaxBuf);
	GetStringFileInfo(pFixedInfo, Pointer.GetPtr(), _T("Comments"),			(LPTSTR)VersionRes.m_sComments.GetBuffer(m_nMaxBuf),			m_nMaxBuf);
	GetStringFileInfo(pFixedInfo, Pointer.GetPtr(), _T("LegalTrademarks"),	(LPTSTR)VersionRes.m_sLegalTradeMarks.GetBuffer(m_nMaxBuf),		m_nMaxBuf);
	GetStringFileInfo(pFixedInfo, Pointer.GetPtr(), _T("PrivateBuild"),		(LPTSTR)VersionRes.m_sPrivateBuild.GetBuffer(m_nMaxBuf),		m_nMaxBuf);
	GetStringFileInfo(pFixedInfo, Pointer.GetPtr(), _T("SpecialBuild"),		(LPTSTR)VersionRes.m_sSpecialBuild.GetBuffer(m_nMaxBuf),		m_nMaxBuf);	

	// Release the buffers
	VersionRes.m_sProdVersion.ReleaseBuffer();
	VersionRes.m_sFileVersion.ReleaseBuffer();
	VersionRes.m_sCompanyName.ReleaseBuffer();
	VersionRes.m_sFileDescription.ReleaseBuffer();
	VersionRes.m_sInternalName.ReleaseBuffer();
	VersionRes.m_sLegalCopyright.ReleaseBuffer();
	VersionRes.m_sOriginalFileName.ReleaseBuffer();
	VersionRes.m_sProductName.ReleaseBuffer();
	VersionRes.m_sComments.ReleaseBuffer();
	VersionRes.m_sLegalTradeMarks.ReleaseBuffer();
	VersionRes.m_sPrivateBuild.ReleaseBuffer();
	VersionRes.m_sSpecialBuild.ReleaseBuffer();	

	return true;
	}

//-------------------------------------------------------------------------------
// Retrieve the size of the version information resource block. We will need this
// to allocate enough memory to hold the resource.
DWORD CVFXVersionInfo::GetFileVersionInfoSize(CString& sModuleName)
	{
	DWORD nSize;
	DWORD nReserved;

	nSize = ::GetFileVersionInfoSize(sModuleName.GetBuffer(m_nMaxBuf), &nReserved);	
	sModuleName.ReleaseBuffer();

	return nSize;
	}

//-------------------------------------------------------------------------------
// Initializes the pBuf pointer to point to the version information block resource.
bool CVFXVersionInfo::GetFileVersionInfo(CString& sModuleName,DWORD nBufSize, PVOID pBuf)
	{
	bool rc;
	DWORD nReserved = 0;

	rc = ::GetFileVersionInfo(sModuleName.GetBuffer(m_nMaxBuf), nReserved, nBufSize, pBuf) ? true : false;
	sModuleName.ReleaseBuffer();

	return rc;
	}
