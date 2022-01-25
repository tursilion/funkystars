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
#include <cmath>
#include <ppl.h>

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
int GravityMin, GravityMax;
int WarpSpeedMin, WarpSpeedMax;
int VarRotate, VarDirection;
int ChangeTime, CenterDesktop;
int size;

void GetString(int &var, char *varname, int def) {
	char buf[128];
	char buf2[128];
	DWORD type, size;
	sprintf(buf2, "SOFTWARE\\TursiSoft\\FunkyStars\\");
	size = sizeof(buf);
	SHGetValue(HKEY_CURRENT_USER, buf2, varname, &type, buf, &size);
	if ((size == 0)||(buf[0]=='\0')) {
		var = def;
	} else {
		var=atoi(buf);
	}
}

void SetString(int &var, char *varname) {
	char buf[128];
	char buf2[128];
	sprintf(buf2, "SOFTWARE\\TursiSoft\\FunkyStars\\");
	sprintf(buf, "%d", var); 
	SHSetValue(HKEY_CURRENT_USER, buf2, varname, REG_SZ, buf, strlen(buf)+1);
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
	GET(GravityMin, 0);
	GET(GravityMax, 10000);
	if (GravityMin>=GravityMax) GravityMin=GravityMax-1;
	GET(WarpSpeedMin, 1);
	GET(WarpSpeedMax, 200);
	if (WarpSpeedMin>=WarpSpeedMax) WarpSpeedMin=WarpSpeedMax-1;
	GET(VarRotate, 2);
	GET(VarDirection, 2);
	GET(CenterDesktop, 1);
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
	SET(GravityMin);
	SET(GravityMax);
	SET(YSpeedMin);
	SET(YSpeedMax);
	SET(RotateMin);
	SET(RotateMax);
	SET(WarpSpeedMin);
	SET(WarpSpeedMax);
	SET(VarRotate);
	SET(CenterDesktop);
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
	r=0; rs=0;
	RndTimer=0;

	LoadSettings();

	srand((unsigned int)time(NULL));
}

CMfcSaver::~CMfcSaver()
{
}

/////////////////////////////////////////////////////////////////////////////
// just a callback check for negative monitor offsets
BOOL CALLBACK checkAllMonitors(HMONITOR mon, HDC hdc, LPRECT pRect, LPARAM saver) {
	CMfcSaver *pSaver = reinterpret_cast<CMfcSaver*>(saver);

	if (pRect->left < pSaver->minX) pSaver->minX = pRect->left;
	if (pRect->top < pSaver->minY) pSaver->minY = pRect->top;
	
	// keep working on it till we check them all
	return TRUE;
}

void CMfcSaver::OnDraw(	CDC* pdc)
{
	int idx;
	
	if (NULL == pWnd)
	{
		// this 'init' only happens once
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
//			Star[idx].xd = 0;
//			Star[idx].yd = 0;
			// stars can be red, blue, white or yellow
			switch (rand()%4) {
				case 0:
					Star[idx].col = RGB(255,255,255); break;
				case 1:
					Star[idx].col = RGB(255,0,0); break;
				case 2:
					Star[idx].col = RGB(0,0,255); break;
				case 3:
					Star[idx].col = RGB(255,255,0); break;
			}
		}

		if (m_centerDesktop) {
			// this is easy, the paint function handed it all to us
			woff=(myrect.right-myrect.left)/2+1;
			hoff=(myrect.bottom-myrect.top)/2+1;
		} else {
			// center on primary monitor. No difference on single monitor
			// First get the size of the main monitor, then enumerate and
			// see if there are any negative coordinates we need to account for
			woff=GetSystemMetrics(SM_CXSCREEN)/2+1;
			hoff=GetSystemMetrics(SM_CYSCREEN)/2+1;
			minX=0;
			minY=0;
			EnumDisplayMonitors(NULL, NULL, checkAllMonitors, (LPARAM)this);
			woff-=minX;	// should be negative or 0
			hoff-=minY;	// should be negative or 0
		}

#ifdef _DEBUG
		// force into the window in debug mode
		woff=(myrect.right-myrect.left)/2+1;
		hoff=(myrect.bottom-myrect.top)/2+1;
#endif

		// Don't need to erase, we re-paint the entire screen each update
		//CRect rcClient;
		//GetClientRect(&rcClient);
		//pdc->FillSolidRect(&rcClient, RGB(0, 0, 0));
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
		
		m_timeStep=(rand()%(TimeStepMax-TimeStepMin)+TimeStepMin)/1000.0;
		m_rotateSpeed=(rand()%(RotateMax-RotateMin)+RotateMin);
		m_gravity=(rand()%(GravityMax-GravityMin));
		m_centerDesktop = CenterDesktop!=0;

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
	
	HANDLE hThread=GetCurrentThread();
	int oldPri=GetThreadPriority(hThread);
	//SetThreadPriority(hThread, THREAD_PRIORITY_BELOW_NORMAL);

// size of a circle
#define TWOPI 6.2830
// number of steps we want
#define CIRCLEDIV (TWOPI/90.0)

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

	// always center, never liked the panning

	// Do the math...
	tmpc=m_varc*5000.0;
	tmpf=m_varf*5000.0;
	int scale=(1000*(6-size))/2;	// we take out the 2 when applying it to get 2x1 and such
	if (m_direction) {
		m_warpSpeed = abs(m_warpSpeed);
	} else {
		m_warpSpeed = -abs(m_warpSpeed);
	}
	// it's okay that they affect each other out of sequence, so use multiple cores here
	//for (idx=0; idx<NUMSTARS; idx++)
	concurrency::parallel_for (int(0), NUMSTARS, [&](int idx)
	{
		if (m_rotate) {
			// rotate star
			Star[idx].x= ((Star[idx].x*cosr)-(Star[idx].y*sinr));
			Star[idx].y= ((Star[idx].x*sinr)+(Star[idx].y*cosr));
		}

		// move star
		Star[idx].z+=m_warpSpeed;
		if (Star[idx].z==0) Star[idx].z=1;

		// apply gravity. We really should also apply inertia, but we'll just do
		// XY gravity and ignore z motion (which is warpspeed)
		// this means a nasty lookup against every other star, but maybe since this is 15 years old,
		// PCs are quick enough ;)
		// Nope: they are not. Threadripper with multi-threading gets about 2 seconds per frame.
		// So will change it to only look at the nearest slices
		// BTW: this is whoa.
		double vecx=0,vecy=0;
		for (int idx2=idx-100; idx2<idx+100; ++idx2) {
			if (idx2 == idx) continue;
			int i2=idx2;
			// Make sure we're always in the array
			if (i2<0) i2+=NUMSTARS;
			if (i2>=NUMSTARS) i2-=NUMSTARS;
			// just skip if it's across the wraparound point
			if (abs(Star[idx].z-Star[i2].z) > 100) continue;
			// inverted square of the distance is the pull, and we'll ignore the Z part of the vector (but keep it for distance)
			double range = (std::pow(Star[idx].x-Star[i2].x,2)+std::pow(Star[idx].y-Star[i2].y,2)+std::pow(Star[idx].z-Star[i2].z,2)); 
			if (range > 0.0) {
				double pull=1/range;
				// 2d vector of pull added to data
				// I tried anti-grav, but everything just tries to settle into a median distance from each other,
				// and you end up with very little in the way of patterns or obvious movement
				// Inertia with anti-grav looks a little better, but just busy, no patterns
				vecx += (Star[i2].x-Star[idx].x)*pull*m_gravity;
				vecy += (Star[i2].y-Star[idx].y)*pull*m_gravity;
			}
		}
		// should be impossible to be pulled OFF the cube
#if 0
		// Inertia just makes it look like noise or smoke or embers, which is cool but wrong
		// well, except inertia might now, but I /think/ that should still be okay...
		Star[idx].xd += vecx;
		Star[idx].x+=Star[idx].xd;
		Star[idx].yd += vecy;
		Star[idx].y+=Star[idx].yd;

		//m_warpSpeed = 0;	// intertia without movement hack
		//m_rotateSpeed = 0;
		// still change gravity?
		//KillTimer(2);
#else
		// this creates the nice spirals I always wanted nicely...
		Star[idx].x+=vecx;
		Star[idx].y+=vecy;
#endif

		if (((m_direction)&&(Star[idx].z > NUMSTARS)) || ((!m_direction)&&(Star[idx].z < 2)))
		{
			// New star
			nTime+=m_timeStep;

			if (m_direction) {
				Star[idx].z-=NUMSTARS;
			} else {
				Star[idx].z+=NUMSTARS;
			}
 
			Star[idx].x=(sin(m_vara*nTime+m_varb)*tmpc);
			Star[idx].y=(cos(m_vard*nTime+m_vare)*tmpf);
		}

		Star[idx].oldx=(int)((Star[idx].x * 1024.0) / Star[idx].z + woff);
		Star[idx].oldy=(int)((Star[idx].y * 1024.0) / Star[idx].z + hoff);
	}
	);	// end parallel_for lambda

	// Update the screen
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

	// draw back to front
	double lowest = 0;
	int lowidx = NUMSTARS;
	for (idx=0; idx<NUMSTARS; ++idx) {
		if (Star[idx].z > lowest) {
			lowest = Star[idx].z;
			lowidx = idx;
		}
	}

	for (int x=0; x<rcClient.right; x+=256) {
		for (int y=0; y<rcClient.bottom; y+=256) {
			pWorkDC->FillSolidRect(0,0,256,256, RGB(0, 0, 0));
			idx = lowest;
			for (int cnt=0; cnt<NUMSTARS; ++cnt) {
#if 1
				// render normal view
				if ((Star[idx].oldx>=x)&&(Star[idx].oldx<x+256)&&(Star[idx].oldy>=y)&&(Star[idx].oldy<y+256)) {
					int tmp=(int)(NUMSTARS-Star[idx].z) / scale;
					if (tmp<2) tmp=2;
					int tmpx=(tmp+1)/2;
					int tmpy=tmp/2;
					
					// fading color
					COLORREF xx = Star[idx].col;
					int var = (int)((Star[idx].z)/(NUMSTARS/255));
					if (var > 254) var=254;
					if (xx&0xff) xx-=var;
					if (xx&0xff00) xx-=var<<8;
					if (xx&0xff0000) xx-=var<<16;

					pWorkDC->FillSolidRect(Star[idx].oldx-x, Star[idx].oldy-y, tmpx, tmpy, xx);
				}
#else
				// render side view (z is now x) - this is not correct projection but you get the point...
				int tmpz = Star[idx].z * (rcClient.right/200000.0);
				if ((Star[idx].z>=x)&&(Star[idx].z<x+256)&&(Star[idx].oldy>=y)&&(Star[idx].oldy<y+256)) {
					int tmp=(int)(NUMSTARS-Star[idx].x) / scale;
					if (tmp<2) tmp=2;
					int tmpx=(tmp+1)/2;
					int tmpy=tmp/2;
					pWorkDC->FillSolidRect(Star[idx].z-x, Star[idx].oldy-y, tmpx, tmpy, RGB(255,255,255));
				}
#endif
				--idx;
				if (idx < 0) idx = NUMSTARS-1;
			}
			pDC->BitBlt(x,y,256,256,pWorkDC,0,0,SRCCOPY);
		}
	}

	pWorkDC->SelectObject(pOldBMP);
	delete pBMP;
	delete pWorkDC;
	ReleaseDC(pDC);

	SetThreadPriority(hThread, oldPri);
}

