//
// (C) 2004 Mike Brent aka Tursi aka HarmlessLion.com
// This software is provided AS-IS. No warranty
// express or implied is provided.
//
// This notice defines the entire license for this code.
// All rights not explicity granted here are reserved by the
// author.
//
// You may redistribute this software provided the original
// archive is UNCHANGED and a link back to my web page,
// http://harmlesslion.com, is provided as the author's site.
// It is acceptable to link directly to a subpage at harmlesslion.com
// provided that page offers a URL for that purpose
//
// Source code, if available, is provided for educational purposes
// only. You are welcome to read it, learn from it, mock
// it, and hack it up - for your own use only.
//
// Please contact me before distributing derived works or
// ports so that we may work out terms. I don't mind people
// using my code but it's been outright stolen before. In all
// cases the code must maintain credit to the original author(s).
//
// -COMMERCIAL USE- Contact me first. I didn't make
// any money off it - why should you? ;) If you just learned
// something from this, then go ahead. If you just pinched
// a routine or two, let me know, I'll probably just ask
// for credit. If you want to derive a commercial tool
// or use large portions, we need to talk. ;)
//
// If this, itself, is a derived work from someone else's code,
// then their original copyrights and licenses are left intact
// and in full force.
//
// http://harmlesslion.com - visit the web page for contact info
//
// ScreenSaverDlg.h : header file
//
//////////
//
// Copyright (C) 1991-98 Ed Halley.
//   http://www.explorati.com/people/ed/
//   ed@explorati.com
//
// This published source code represents original intellectual
// property, owned and copyrighted by Ed Halley.
//
// The owner has authorized this source code for general public
// use without royalty, under two conditions:
//    * The source code maintains this copyright notice in full.
//    * The source code is only distributed for free or
//      reasonable duplication cost, not for distribution profit.
//
// Unauthorized use, copying or distribution is a violation of
// U.S. and international laws and is strictly prohibited.
//
//////////
//

#ifndef __SCREENSAVERDLG_H__
#define __SCREENSAVERDLG_H__

/////////////////////////////////////////////////////////////////////////////

// CScreenSaverDlg:
// A configuration dialog for Win95+, WinNT3+ compliant screen savers.
// For use with CScreenSaverWnd, usually found in ScreenSaverWnd.cpp and .h.
// See documentation in those files for more information on screen savers.

/////////////////////////////////////////////////////////////////////////////

#include <scrnsave.h>

// Note: the dialog resource should be DLG_SCRNSAVECONFIGURE.
// Note: the icon resource should be ID_APP.

class CScreenSaverDlg : public CDialog
{
	DECLARE_DYNAMIC(CScreenSaverDlg)
public:
	CScreenSaverDlg();

// Attributes
protected:
public:

// Operations
public:

// Overridables
public:

// Overrides
public:
	//{{AFX_VIRTUAL(CScreenSaverDlg)
	//}}AFX_VIRTUAL
	virtual BOOL OnInitDialog();

// Implementation
public:
	virtual ~CScreenSaverDlg();
	static CScreenSaverDlg* sm_pTheConfigureDialog;

protected:
	virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//{{AFX_MSG(CScreenSaverDlg)
	afx_msg void OnNcDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

//friend BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT uMsg,
//                                              WPARAM wParam,
//                                              LPARAM lParam);

};

/////////////////////////////////////////////////////////////////////////////

inline CScreenSaverDlg* AfxGetScreenSaverDialog()
	{
		return CScreenSaverDlg::sm_pTheConfigureDialog;
	}

/////////////////////////////////////////////////////////////////////////////

BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT uMsg,
                                       WPARAM wParam, LPARAM lParam);
BOOL WINAPI RegisterDialogClasses(HANDLE hInstance);

/////////////////////////////////////////////////////////////////////////////

#endif // __SCREENSAVERDLG_H__
