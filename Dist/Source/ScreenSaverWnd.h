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
// ScreenSaverWnd.h : header file
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

#ifndef __SCREENSAVERWND_H__
#define __SCREENSAVERWND_H__

/////////////////////////////////////////////////////////////////////////////

// CScreenSaverWnd:
// A Win95, Win98, WinNT3, WinNT4, WinNT5 compliant screen saver.
//
// There are several requirements to be a compliant screen saver.
// These are very arbitrary, but have their historical roots to Windows 3.0
// and the Microsoft Entertainment Pack 1.0 (IdleWild), as well as the
// competing products also vying for a standard.
//
// For all screen savers,
// * The name or description of the screen saver is in string 1.
// * The icon for the screen saver is ID_APP, defined in <scrnsave.h> to 100.
// * The WINAPI ScreenSaverProc() must be defined and exported.
//   (The CScreenSaverWnd module implements this API for you.)
// * The executable should be named with a .SCR file extension.
//
// For configurable screen savers,
// * The dialog for configuring the screen saver is DLG_SCRNSAVECONFIGURE,
//   defined in <scrnsave.h> to 2003.
// * The WINAPI ScreenSaverConfigureDialog() must be defined and exported.
// * The WINAPI RegisterDialogClasses() must be defined and exported.
//   (The CScreenSaverDlg module implements these APIs for you.)
//
// Supporting configuration, by using CScreenSaverDlg or other methods,
// is optional for compliant screen savers.  The RestoreOptions() member
// function is called upon startup, but calling SaveOptions() is up to
// the derived class; neither function does anything in the base definition.
//
// There should be no CWinApp object instantiated.  Instead, instantiate one
// CScreenSaverWnd-derived object.  For configurable savers, instantiate one
// CScreenSaverDlg-derived object also.  These can be done as globals.
//
// Win32 screen savers support password protection without supplying their
// own dialogs, through a built-in feature of the operating system.  This
// makes the password more secure than having each screen saver solve the
// same problems in different ways.

/////////////////////////////////////////////////////////////////////////////

#include <scrnsave.h>

extern int VarAMin, VarAMax;
extern int VarBMin, VarBMax;
extern int VarCMin, VarCMax;
extern int VarDMin, VarDMax;
extern int VarEMin, VarEMax;
extern int VarFMin, VarFMax;
extern int TimeStepMin, TimeStepMax;
extern int XSpeedMin, XSpeedMax;
extern int YSpeedMin, YSpeedMax;
extern int RotateMin, RotateMax;
extern int WarpSpeedMin, WarpSpeedMax;
extern int VarCenter, VarRotate, VarDirection;
extern int ChangeTime, size;
void LoadSettings();
void SaveSettings();

class CScreenSaverWnd : public CWnd
{
	DECLARE_DYNAMIC(CScreenSaverWnd)
public:
	CScreenSaverWnd();

// Attributes
protected:
	BOOL m_bAutoBlack;
	CPalette* m_pPalette;
public:
	BOOL IsAutoBlack() const;
	void SetAutoBlack(BOOL bAutoBlack = TRUE);
	//
	CPalette* GetPalette() const;
	CPalette* SetPalette(CPalette* pPalette);

// Operations
public:

// Overridables
public:
	virtual void OnDraw(CDC* pDC);
	virtual void OnInitialUpdate();

// Overrides
public:
	//{{AFX_VIRTUAL(CScreenSaverWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScreenSaverWnd();
	static CScreenSaverWnd* sm_pTheScreenSaver;

protected:
	virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//{{AFX_MSG(CScreenSaverWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

//friend LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT uMsg,
//                                      WPARAM wParam, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////

inline CScreenSaverWnd* AfxGetScreenSaverWnd()
	{
		return CScreenSaverWnd::sm_pTheScreenSaver;
	}

/////////////////////////////////////////////////////////////////////////////

LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT uMsg,
                               WPARAM wParam, LPARAM lParam);

/////////////////////////////////////////////////////////////////////////////

#endif // __SCREENSAVERWND_H__
