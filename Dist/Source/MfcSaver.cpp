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
// MfcSaver.cpp : Defines the class behaviors for the application.
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

#include "StdAfx.h"
#include <math.h>
#include <windows.h>

#include "MfcSaver.h"
#include "MfcSaverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Some bad non-object oriented stuff. Wah!
/////////////////////////////////////////////////////////////////////////////
int VarAMin, VarAMax;
int VarBMin, VarBMax;
int VarCMin, VarCMax;
int VarDMin, VarDMax;
int VarEMin, VarEMax;
int VarFMin, VarFMax;
int TimeStepMin, TimeStepMax;
int XSpeedMin, XSpeedMax;
int YSpeedMin, YSpeedMax;
int RotateMin, RotateMax;
int WarpSpeedMin, WarpSpeedMax;
int VarCenter, VarRotate, VarDirection;
int ChangeTime;
int size;

void GetString(int &var, char *varname, int def) {
	char buf[128];
	char buf2[128];
	sprintf(buf2, "%d", def);
	GetPrivateProfileString("FunkyStars", varname, buf2, buf, 128, "funkystars.ini"); 
	var=atoi(buf);
}

void SetString(int &var, char *varname) {
	char buf[128];
	
	sprintf(buf, "%d", var); 
	WritePrivateProfileString("FunkyStars", varname, buf, "funkystars.ini");
}

#define GET(VAR,DEF) GetString(VAR, #VAR, DEF)
#define SET(VAR)     SetString(VAR, #VAR)

void LoadSettings() {
	// Populate the above vars
	GET(VarAMin, -999999);
	GET(VarAMax, 999999);
	if (VarAMin>=VarAMax) VarAMin=VarAMax-1;
	GET(VarBMin, -999999);
	GET(VarBMax, 999999);
	if (VarBMin>=VarBMax) VarBMin=VarBMax-1;
	GET(VarCMin, 0);
	GET(VarCMax, 999);
	if (VarCMin>=VarCMax) VarCMin=VarCMax-1;
	GET(VarDMin, -999999);
	GET(VarDMax, 999999);
	if (VarDMin>=VarDMax) VarDMin=VarDMax-1;
	GET(VarEMin, -999999);
	GET(VarEMax, 999999);
	if (VarEMin>=VarEMax) VarEMin=VarEMax-1;
	GET(VarFMin, 0);
	GET(VarFMax, 999);
	if (VarFMin>=VarFMax) VarFMin=VarFMax-1;
	GET(TimeStepMin, 0);
	GET(TimeStepMax, 10000);
	if (TimeStepMin>=TimeStepMax) TimeStepMin=TimeStepMax-1;
	GET(XSpeedMin, 0);
	GET(XSpeedMax, 99);
	if (XSpeedMin>=XSpeedMax) XSpeedMin=XSpeedMax-1;
	GET(YSpeedMin, 0);
	GET(YSpeedMax, 99);
	if (YSpeedMin>=YSpeedMax) YSpeedMin=YSpeedMax-1;
	GET(RotateMin, 0);
	GET(RotateMax, 499);
	if (RotateMin>=RotateMax) RotateMin=RotateMax-1;
	GET(WarpSpeedMin, 1);
	GET(WarpSpeedMax, 200);
	if (WarpSpeedMin>=WarpSpeedMax) WarpSpeedMin=WarpSpeedMax-1;
	GET(VarCenter, 2);
	GET(VarRotate, 2);
	GET(VarDirection, 2);
	GET(ChangeTime, 30);
	GET(size, 3);

}

void SaveSettings() {
	// save the above vars
	SET(VarAMin);
	SET(VarAMax);
	SET(VarBMin);
	SET(VarBMax);
	SET(VarCMin);
	SET(VarCMax);
	SET(VarDMin);
	SET(VarDMax);
	SET(VarEMin);
	SET(VarEMax);
	SET(VarFMin);
	SET(VarFMax);
	SET(TimeStepMin);
	SET(TimeStepMax);
	SET(XSpeedMin);
	SET(XSpeedMax);
	SET(YSpeedMin);
	SET(YSpeedMax);
	SET(RotateMin);
	SET(RotateMax);
	SET(WarpSpeedMin);
	SET(WarpSpeedMax);
	SET(VarCenter);
	SET(VarRotate);
	SET(VarDirection);
	SET(ChangeTime);
	SET(size);
}

/////////////////////////////////////////////////////////////////////////////

//
// The screen saver controls a number of icon graphics that bounce around
// on a black background.  Set some basic defaults and initialize the random
// number generator with srand().  Later, our RestoreOptions() will be called
// to recall earlier option settings.
//

BEGIN_MESSAGE_MAP(CMfcSaver, CScreenSaverWnd)
	//{{AFX_MSG_MAP(CMfcSaver)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// As required of CScreenSaverWnd-based screen savers, these are the two
// global instances of screen saver objects.  One is the saver itself,
// and one is the dialog for configuring the options of the screen saver.
//
// Unlike most MFC applications, there is no instance of any CWinApp object.
//
CMfcSaver theSaver;
CMfcSaverDlg theSaverDialog;

CMfcSaver::CMfcSaver()
{
	pWnd=NULL;
	x=0; y=0; r=0; rs=0;
	RndTimer=0;

	LoadSettings();

	srand((unsigned int)time(NULL));
}

CMfcSaver::~CMfcSaver()
{
}

/////////////////////////////////////////////////////////////////////////////

void CMfcSaver::OnDraw(	CDC* pdc)
{
	int idx;
	
	if (NULL == pWnd)
	{
		pWnd=(HWND)GetSafeHwnd();
		myTimer=::SetTimer(pWnd, 1, 30, NULL);
		RndTimer=::SetTimer(pWnd, 2, ChangeTime*1000, NULL);
		OnTimer(2);
		GetWindowRect(&myrect);
		for (idx=0; idx<NUMSTARS; idx++) 
		{
			Star[idx].x=rand()%10000-5000;
			Star[idx].y=rand()%10000-5000;
			Star[idx].z=idx+1;
			Star[idx].oldx=(int)Star[idx].x;
			Star[idx].oldy=(int)Star[idx].y;
		}
		xoff=0; yoff=0;
		woff=(myrect.right-myrect.left)/2+1;
		hoff=(myrect.bottom-myrect.top)/2+1;

		CRect rcClient;
		GetClientRect(&rcClient);
		pdc->FillSolidRect(&rcClient, RGB(0, 0, 0));
	}
}


/////////////////////////////////////////////////////////////////////////////

//
// While this is just demonstrating how to override the virtual functions of
// CScreenSaverWnd, it also shows something about using CImageList to
// draw from a library of simple images.
//
// When our timer goes off, we just invalidate the window.  The OnDraw()
// override will be called appropriately when the system has some free cycles
// to spend on drawing.  Remember:  a screen saver should share the CPU, so
// the computer can work on other tasks like downloading or numbercrunching.
//

void CMfcSaver::OnInitialUpdate()
{
}

void CMfcSaver::OnTimer(UINT nIDEvent) 
{
	CScreenSaverWnd::OnTimer(nIDEvent);

	if (nIDEvent==1) {
		// Tick expired
		MoveStars();
	}
	if (nIDEvent==2) {
		// Random state change
		m_vara=(rand()%(VarAMax-VarAMin)+VarAMin)/1000.0;
		m_varb=(rand()%(VarBMax-VarBMin)+VarBMin)/1000.0;
		m_varc=(rand()%(VarCMax-VarCMin)+VarCMin)/1000.0;
		m_vard=(rand()%(VarDMax-VarDMin)+VarDMin)/1000.0;
		m_vare=(rand()%(VarEMax-VarEMin)+VarEMin)/1000.0;
		m_varf=(rand()%(VarFMax-VarFMin)+VarFMin)/1000.0;
		
		switch (VarCenter) {
		case 0:	m_center=1; break;
		case 1: m_center=0; break;
		default:m_center=rand()%2; break;
		}

		m_timeStep=(rand()%(TimeStepMax-TimeStepMin)+TimeStepMin)/1000.0;
		m_xSpeed=(rand()%(XSpeedMax-XSpeedMin)+XSpeedMin)/10000.0;
		m_ySpeed=(rand()%(YSpeedMax-YSpeedMin)+YSpeedMin)/10000.0;
		m_rotateSpeed=(rand()%(RotateMax-RotateMin)+RotateMin);

		switch (VarRotate) {
		case 0: m_rotate=0; break;
		case 1: m_rotate=1; break;
		case 2: m_rotate=2;	break;	// continuous
		default: m_rotate=rand()%3; break;
		}

		if (m_rotate != 2) {
			m_rotateSpeed /= 10000.0;
		}

		m_warpSpeed=(short)(rand()%(WarpSpeedMax-WarpSpeedMin)+WarpSpeedMin+1);		
		switch (VarDirection) {
		case 0: m_direction=1; break;
		case 1: m_direction=0; break;
		default:m_direction=rand()%2; break;
		}
	}
}

void CMfcSaver::MoveStars()
{
	int idx;
	double sinr, cosr;
	static double nTime=0;
	double tmpc, tmpf;
	int oldx[NUMSTARS], oldy[NUMSTARS], oldtmp[NUMSTARS];
	
	HANDLE hThread=GetCurrentThread();
	int oldPri=GetThreadPriority(hThread);
	//SetThreadPriority(hThread, THREAD_PRIORITY_BELOW_NORMAL);

// size of a circle
#define TWOPI 6.2830
// number of steps we want
#define CIRCLEDIV (TWOPI/90.0)

	x+=m_xSpeed;
	y+=m_ySpeed;

	if (m_rotate != 2) {
		rs+=m_rotateSpeed;
		r=sin(rs)*CIRCLEDIV;
		sinr=sin(r);		// if you put rs in these, and m_rotateSpeed is between 0.0 and 1.0, interesting things happen
		cosr=cos(r);
	} else {
		r=sin(m_rotateSpeed)*CIRCLEDIV;
		sinr=sin(r);
		cosr=cos(r);
	}

	if (m_center) {
		xoff=woff;
		yoff=hoff;
	} else {
		xoff=(int)(sin(x)*(woff+woff))+woff;
		yoff=(int)(sin(y)*(hoff+hoff))+hoff;
	}

	// Do the math...
	tmpc=m_varc*5000.0;
	tmpf=m_varf*5000.0;
	int scale=1000*(6-size);
	for (idx=0; idx<NUMSTARS; idx++)
	{
		oldtmp[idx]=(int)(10000.0-Star[idx].z)/scale;
		if (oldtmp[idx]<1) oldtmp[idx]=1;
		oldx[idx]=Star[idx].oldx;
		oldy[idx]=Star[idx].oldy;
		
		if (m_rotate) {
			// rotate star
			Star[idx].x= ((Star[idx].x*cosr)-(Star[idx].y*sinr));
			Star[idx].y= ((Star[idx].x*sinr)+(Star[idx].y*cosr));
		}

		// move star
		if (m_direction) {
			Star[idx].z+=m_warpSpeed;
		} else {
			Star[idx].z-=m_warpSpeed;
		}
		if (Star[idx].z==0) Star[idx].z=1;

		if (((m_direction)&&(Star[idx].z > 10000)) || ((!m_direction)&&(Star[idx].z < 2)))
		{
			// New star
			nTime+=m_timeStep;

			if (m_direction) {
				Star[idx].z-=10000;
			} else {
				Star[idx].z+=10000;
			}
 
			Star[idx].x=(sin(m_vara*nTime+m_varb)*tmpc);
			Star[idx].y=(cos(m_vard*nTime+m_vare)*tmpf);
		}

		Star[idx].oldx=(int)((Star[idx].x * 1024.0) / Star[idx].z + xoff);
		Star[idx].oldy=(int)((Star[idx].y * 1024.0) / Star[idx].z + yoff);
	}

	// Update the screen
#if 1
	// blitting 10000 stars gets slow, but many tend to be blocked together, so we try to
	// do it in blocks of 256x256 (works MUCH better!)
	CDC *pDC=GetDC();
	CRect rcClient;
	GetClientRect(&rcClient);
	CDC *pWorkDC = new CDC();
	pWorkDC->CreateCompatibleDC(pDC);
	CBitmap *pBMP = new CBitmap();
	pBMP->CreateCompatibleBitmap(pDC, 256, 256);
	CBitmap *pOldBMP = pWorkDC->SelectObject(pBMP);

	for (int x=0; x<rcClient.right; x+=256) {
		for (int y=0; y<rcClient.bottom; y+=256) {
			pWorkDC->FillSolidRect(0,0,256,256, RGB(0, 0, 0));
			for (idx=0; idx<NUMSTARS; idx++) {
				if ((Star[idx].oldx>=x)&&(Star[idx].oldx<x+256)&&(Star[idx].oldy>=y)&&(Star[idx].oldy<y+256)) {
					int tmp=(int)(10000-Star[idx].z) / scale;
					if (tmp<1) tmp=1;
					pWorkDC->FillSolidRect(Star[idx].oldx-x, Star[idx].oldy-y, tmp, tmp, RGB(255,255,255));
				}
			}
			pDC->BitBlt(x,y,256,256,pWorkDC,0,0,SRCCOPY);
		}
	}

	pWorkDC->SelectObject(pOldBMP);
	delete pBMP;
	delete pWorkDC;
	ReleaseDC(pDC);
#else
	// old per-star method
	CDC *pDC=GetDC();
	for (idx=0; idx<NUMSTARS; idx++) {
		int tmp=(int)(10000-Star[idx].z) / scale;
		if (tmp<1) tmp=1;
		pDC->BitBlt(oldx[idx], oldy[idx], oldtmp[idx], oldtmp[idx], NULL, 0, 0, BLACKNESS);
		pDC->BitBlt(Star[idx].oldx, Star[idx].oldy, tmp, tmp, NULL, 0, 0, WHITENESS);
	}
#endif

	SetThreadPriority(hThread, oldPri);
}

