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
// MfcSaver.h : main header file for the MFCSAVER application
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

#ifndef __MFCSAVER_H__
#define __MFCSAVER_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////

#include "ScreenSaverWnd.h"

#define NUMSTARS 10000

class CMfcSaver : public CScreenSaverWnd
{
// Construction
public:
	CMfcSaver();

// Overrides
public:
	virtual void OnDraw(CDC* pDC);
	virtual void OnInitialUpdate();
//	virtual void SaveOptions();
//	virtual void RestoreOptions();
	//{{AFX_VIRTUAL(CMfcSaver)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfcSaver();
	void MoveStars();

	HWND pWnd;
	RECT myrect;
	struct {
		double x, y, z;
		int oldx, oldy;
	} Star[NUMSTARS];
	int xoff, yoff;
	UINT myTimer;
	UINT RndTimer;
	double x,y,r,rs;
	int hoff, woff;


protected:
	//{{AFX_MSG(CMfcSaver)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	double m_vara;
	double m_varb;
	double m_varc;
	double m_vard;
	double m_vare;
	double m_varf;
	BOOL m_center;
	double m_timeStep;
	double m_xSpeed;
	double m_ySpeed;
	double m_rotateSpeed;
	int m_rotate;
	short m_warpSpeed;
	BOOL m_direction;

};

/////////////////////////////////////////////////////////////////////////////

#endif // __MFCSAVER_H__
