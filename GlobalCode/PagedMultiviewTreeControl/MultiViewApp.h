// MultiViewApp.h : main header file for the MULTIVIEW application
//

#if !defined(AFX_MultiViewApp_INCLUDED)
#define AFX_MultiViewApp_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MultiviewPrecompile.h"

#ifndef __AFXWIN_H__
	#error include 'MultiviewPrecompile.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "BasicMultiviewTemplate.h"

#include "MainFrm.h"
#include "OtherView.h"

/////////////////////////////////////////////////////////////////////////////
// CMultiViewApp:
// See MultiView.cpp for the implementation of this class
//

class MultiViewApp : public BasicMultiviewTemplate<MainFrame, OtherView, CView, CFrameWnd>
{
public:
	MultiViewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiViewApp)
	//public:
	//virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMultiViewApp)
	//afx_msg void OnAppAbout();
	//afx_msg void OnViewOtherview();
	//afx_msg void OnViewFirstview();
	////}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern MultiViewApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif