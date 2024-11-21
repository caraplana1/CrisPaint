
// CrisPaint.h : main header file for the CrisPaint application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCrisPaintApp:
// See CrisPaint.cpp for the implementation of this class
//

class CCrisPaintApp : public CWinAppEx
{
public:
	CCrisPaintApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCrisPaintApp theApp;
