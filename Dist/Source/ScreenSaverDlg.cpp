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
// ScreenSaverDlg.cpp : implementation file
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

#include "ScreenSaverWnd.h"
#include "ScreenSaverDlg.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define SET(VAR, DEF) VAR=DEF;
void SetDefaults() {
	SET(VarAMin, -999999);
	SET(VarAMax, 999999);
	SET(VarBMin, -999999);
	SET(VarBMax, 999999);
	SET(VarCMin, 0);
	SET(VarCMax, 999);
	SET(VarDMin, -999999);
	SET(VarDMax, 999999);
	SET(VarEMin, -999999);
	SET(VarEMax, 999999);
	SET(VarFMin, 0);
	SET(VarFMax, 999);
	SET(TimeStepMin, 0);
	SET(TimeStepMax, 10000);
	SET(XSpeedMin, 0);
	SET(XSpeedMax, 99);
	SET(YSpeedMin, 0);
	SET(YSpeedMax, 99);
	SET(RotateMin, 0);
	SET(RotateMax, 499);
	SET(WarpSpeedMin, 1);
	SET(WarpSpeedMax, 200);
	SET(VarCenter, 2);
	SET(VarRotate, 2);
	SET(VarDirection, 2);
	SET(ChangeTime, 30);
}
#undef SET

/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CScreenSaverDlg, CDialog)

// MFC's normal processing would have CDialog and CWnd handle any messages
// not handled by the CScreenSaverDlg.  Some are not appropriate for a
// screen saver's configuration dialog, so we skip CDialog and CWnd in the
// line below, and have all unhandled messages go to the CCmdTarget.
// The WindowProc() below will forward the reasonable messages to CDialog.
//
BEGIN_MESSAGE_MAP(CScreenSaverDlg, CCmdTarget)
	//{{AFX_MSG_MAP(CScreenSaverDlg)
	ON_WM_NCDESTROY()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_COMMAND(IDOK, OnOK)
	ON_COMMAND(IDCANCEL, OnCancel)
	ON_MESSAGE(WM_INITDIALOG, HandleInitDialog)
END_MESSAGE_MAP()

// There should be only one CScreenSaverDlg instantiated at a time.
// The helper function AfxGetScreenSaverDlg() returns this pointer.
//
/* static */ CScreenSaverDlg* CScreenSaverDlg::sm_pTheConfigureDialog = NULL;

CScreenSaverDlg::CScreenSaverDlg()
{
	ASSERT(!sm_pTheConfigureDialog);
	sm_pTheConfigureDialog = this;
}

CScreenSaverDlg::~CScreenSaverDlg()
{
	sm_pTheConfigureDialog = NULL;
}

/////////////////////////////////////////////////////////////////////////////

void CScreenSaverDlg::OnNcDestroy()
{
	CDialog::OnNcDestroy();
}

BOOL CScreenSaverDlg::OnInitDialog()
{
	LoadSettings();

	return CDialog::OnInitDialog();
}

int CScreenSaverDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
#ifdef _DEBUG
	// Screen savers should be TOPMOST to block out any other windows,
	// such as other topmost windows created previously.  However, if you
	// are trying to debug a screen saver, it can get in the way.
	// We remove the topmost status from this window only if we're _DEBUG.
	// 
	SetWindowPos(&CWnd::wndNoTopMost,
		0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
#endif

	return 0;
}

/////////////////////////////////////////////////////////////////////////////

//
// The default message routing is not built to deal with screen saver
// dialogs.  This avoids the default dialog proc from handling anything we
// don't handle.
//

LRESULT CScreenSaverDlg::WindowProc(UINT uMsg,
                                    WPARAM wParam,
                                    LPARAM lParam)
{
	return CDialog::WindowProc(uMsg, wParam, lParam);
}

LRESULT CScreenSaverDlg::DefWindowProc(UINT uMsg,
                                       WPARAM wParam,
                                       LPARAM lParam)
{
	return 0L;
}

/////////////////////////////////////////////////////////////////////////////

// ::ScreenSaverConfigureDialog():
// This API must be exported to be recognized as a configurable screen
// saver.  This serves as the dialog message proc called by Windows to
// display the configuration dialog for the screen saver.  Not all messages
// that go to the dialog actually get sent to our proc.
//
BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT uMsg,
                                       WPARAM wParam, LPARAM lParam)
{

	// There should be one global instance of a CScreenSaverDlg derivative.
	ASSERT(AfxGetScreenSaverDialog());
	if (!AfxGetScreenSaverDialog())
		return 0L;

	if (!AfxGetScreenSaverDialog()->m_hWnd)
		AfxGetScreenSaverDialog()->Attach(hDlg);

	// MFC does a lot of helpful but nonstandard things with WM_INITDIALOG.
	//
	// Since a screen saver's configuration dialog proc is dictated to us,
	// we need to manually perform the ->OnInitDialog() call ourselves.
	//
	// This is equivalent to MFC4.2's ::AfxDlgProc() [which is not exported
	// nor used by the sanctioned exported public ::AfxCallWndProc()
	// function].
	//
	LRESULT lResult;
	if (uMsg == WM_INITDIALOG)
	{
		CWnd *pWnd;
		CDialog* pDlg =
			DYNAMIC_DOWNCAST(CDialog,
				CWnd::FromHandlePermanent(hDlg));
		if (pDlg == NULL) {
			return 1;	// what more can we do?
		}
		
		lResult = pDlg->OnInitDialog();

#define SETSLIDER(CTL, MIN, MAX) pWnd=pDlg->GetDlgItem(CTL); if (pWnd) ((CSliderCtrl*)pWnd)->SetRange(MIN, MAX, TRUE);
		SETSLIDER(IDC_SLIDER1, -999999, 999999);
		SETSLIDER(IDC_SLIDER2, -999999, 999999);
		SETSLIDER(IDC_SLIDER3, -999999, 999999);
		SETSLIDER(IDC_SLIDER4, -999999, 999999);
		SETSLIDER(IDC_SLIDER5, 0, 999);
		SETSLIDER(IDC_SLIDER6, 0, 999);
		SETSLIDER(IDC_SLIDER7, -999999, 999999);
		SETSLIDER(IDC_SLIDER8, -999999, 999999);
		SETSLIDER(IDC_SLIDER9, -999999, 999999);
		SETSLIDER(IDC_SLIDER10, -999999, 999999);
		SETSLIDER(IDC_SLIDER11, 0, 999);
		SETSLIDER(IDC_SLIDER12, 0, 999);
		SETSLIDER(IDC_SLIDER13, 0, 10000);
		SETSLIDER(IDC_SLIDER14, 0, 10000);
		SETSLIDER(IDC_SLIDER15, 0, 99);
		SETSLIDER(IDC_SLIDER16, 0, 99);
		SETSLIDER(IDC_SLIDER17, 0, 99);
		SETSLIDER(IDC_SLIDER18, 0, 99);
		SETSLIDER(IDC_SLIDER19, 0, 499);
		SETSLIDER(IDC_SLIDER20, 0, 499);
		SETSLIDER(IDC_SLIDER21, 1, 200);
		SETSLIDER(IDC_SLIDER22, 1, 200);
		SETSLIDER(IDC_SLIDER23, 5, 300);
		SETSLIDER(IDC_SIZESTAR, 1, 5);
#undef SETSLIDER

		pDlg->PostMessage(WM_USER+1, 0, 0);
	}
	else
	{
		lResult =
			AfxCallWndProc(
				AfxGetScreenSaverDialog(),
				AfxGetScreenSaverDialog()->m_hWnd,
		        uMsg, wParam, lParam);
	}

	if (uMsg == WM_NCDESTROY)
	{
		ASSERT(!AfxGetScreenSaverDialog() ||
		       !AfxGetScreenSaverDialog()->m_hWnd);
	}

	if (uMsg == WM_USER+1) {
		CWnd *pWnd;
		CDialog* pDlg =
			DYNAMIC_DOWNCAST(CDialog,
				CWnd::FromHandlePermanent(hDlg));
		if (pDlg == NULL) {
			return 1;	// what more can we do?
		}

#define SETSLIDER(VAR, CTL) pWnd=pDlg->GetDlgItem(CTL); if (pWnd) ((CSliderCtrl*)pWnd)->SetPos(VAR);
#define SETCHECK(VAR, CTL, VAL) pWnd=pDlg->GetDlgItem(CTL); if (pWnd) if (VAR==VAL) ((CButton*)pWnd)->SetCheck(BST_CHECKED); else ((CButton*)pWnd)->SetCheck(BST_UNCHECKED);
		// Set the variables into the dialog controls
		SETSLIDER(VarAMin, IDC_SLIDER1);
		SETSLIDER(VarAMax, IDC_SLIDER2);
		SETSLIDER(VarBMin, IDC_SLIDER3);
		SETSLIDER(VarBMax, IDC_SLIDER4);
		SETSLIDER(VarCMin, IDC_SLIDER5);
		SETSLIDER(VarCMax, IDC_SLIDER6);
		SETSLIDER(VarDMin, IDC_SLIDER7);
		SETSLIDER(VarDMax, IDC_SLIDER8);
		SETSLIDER(VarEMin, IDC_SLIDER9);
		SETSLIDER(VarEMax, IDC_SLIDER10);
		SETSLIDER(VarFMin, IDC_SLIDER11);
		SETSLIDER(VarFMax, IDC_SLIDER12);
		SETSLIDER(TimeStepMin, IDC_SLIDER13);
		SETSLIDER(TimeStepMax, IDC_SLIDER14);
		SETSLIDER(XSpeedMin, IDC_SLIDER15);
		SETSLIDER(XSpeedMax, IDC_SLIDER16);
		SETSLIDER(YSpeedMin, IDC_SLIDER17);
		SETSLIDER(YSpeedMax, IDC_SLIDER18);
		SETSLIDER(RotateMin, IDC_SLIDER19);
		SETSLIDER(RotateMax, IDC_SLIDER20);
		SETSLIDER(WarpSpeedMin, IDC_SLIDER21);
		SETSLIDER(WarpSpeedMax, IDC_SLIDER22);
		SETSLIDER(ChangeTime, IDC_SLIDER23);
		SETSLIDER(size, IDC_SIZESTAR);

		SETCHECK(VarCenter, IDC_RADIO1, 0);
		SETCHECK(VarCenter, IDC_RADIO2, 1);
		SETCHECK(VarCenter, IDC_RADIO3, 2);

		SETCHECK(VarRotate, IDC_RADIO4, 0);
		SETCHECK(VarRotate, IDC_RADIO5, 1);
		SETCHECK(VarRotate, IDC_RADIO10, 2);
		SETCHECK(VarRotate, IDC_RADIO6, 3);

		SETCHECK(VarDirection, IDC_RADIO7, 0);
		SETCHECK(VarDirection, IDC_RADIO8, 1);
		SETCHECK(VarDirection, IDC_RADIO9, 2);
#undef SETSLIDER
#undef SETCHECK

		lResult=1;
	}

	if ((uMsg == WM_COMMAND) && (wParam == IDC_BUTTON1)) {
		SetDefaults();
		PostMessage(hDlg, WM_USER+1, 0, 0);
		lResult=1;
	}

#define READSLIDER(VAR, CTL) pWnd=pDlg->GetDlgItem(CTL); if (pWnd) VAR=((CSliderCtrl*)pWnd)->GetPos();
#define TESTCHECK(VAR, CTL, VAL) pWnd=pDlg->GetDlgItem(CTL); if (pWnd) if (BST_CHECKED == ((CButton*)pWnd)->GetCheck()) VAR=VAL;
	if ((uMsg == WM_COMMAND) && (wParam == IDOK)) {
		CWnd *pWnd;
		CDialog* pDlg =
			DYNAMIC_DOWNCAST(CDialog,
				CWnd::FromHandlePermanent(hDlg));
		if (pDlg == NULL) {
			return 1;	// what more can we do?
		}

		// copy the settings from the dialog down to the variables, so we can save them

		READSLIDER(VarAMin, IDC_SLIDER1);
		READSLIDER(VarAMax, IDC_SLIDER2);
		READSLIDER(VarBMin, IDC_SLIDER3);
		READSLIDER(VarBMax, IDC_SLIDER4);
		READSLIDER(VarCMin, IDC_SLIDER5);
		READSLIDER(VarCMax, IDC_SLIDER6);
		READSLIDER(VarDMin, IDC_SLIDER7);
		READSLIDER(VarDMax, IDC_SLIDER8);
		READSLIDER(VarEMin, IDC_SLIDER9);
		READSLIDER(VarEMax, IDC_SLIDER10);
		READSLIDER(VarFMin, IDC_SLIDER11);
		READSLIDER(VarFMax, IDC_SLIDER12);
		READSLIDER(TimeStepMin, IDC_SLIDER13);
		READSLIDER(TimeStepMax, IDC_SLIDER14);
		READSLIDER(XSpeedMin, IDC_SLIDER15);
		READSLIDER(XSpeedMax, IDC_SLIDER16);
		READSLIDER(YSpeedMin, IDC_SLIDER17);
		READSLIDER(YSpeedMax, IDC_SLIDER18);
		READSLIDER(RotateMin, IDC_SLIDER19);
		READSLIDER(RotateMax, IDC_SLIDER20);
		READSLIDER(WarpSpeedMin, IDC_SLIDER21);
		READSLIDER(WarpSpeedMax, IDC_SLIDER22);
		READSLIDER(ChangeTime, IDC_SLIDER23);
		READSLIDER(size, IDC_SIZESTAR);

		TESTCHECK(VarCenter, IDC_RADIO1, 0);
		TESTCHECK(VarCenter, IDC_RADIO2, 1);
		TESTCHECK(VarCenter, IDC_RADIO3, 2);

		TESTCHECK(VarRotate, IDC_RADIO4, 0);
		TESTCHECK(VarRotate, IDC_RADIO5, 1);
		TESTCHECK(VarRotate, IDC_RADIO10, 2);
		TESTCHECK(VarRotate, IDC_RADIO6, 3);

		TESTCHECK(VarDirection, IDC_RADIO7, 0);
		TESTCHECK(VarDirection, IDC_RADIO8, 1);
		TESTCHECK(VarDirection, IDC_RADIO9, 2);

		SaveSettings();
	}
#undef READSLIDER
#undef TESTCHECK

	return lResult;
}

// ::RegisterDialogClasses():
// This API must be exported to be recognized as a configurable screen
// saver.  It is called upon startup to register any WNDCLASS structures
// that would later be necessary to display a configuration dialog.
//
BOOL WINAPI RegisterDialogClasses(HANDLE hInstance)
{
	// We rely on the default registered window class used by MFC
	// dialogs.  Therefore, we have nothing to do here.
	//
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
