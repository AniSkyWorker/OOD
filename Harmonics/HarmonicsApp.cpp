#include "stdafx.h"
#include "HarmonicsApp.h"
#include "MainDlg.h"
#include "HarmonicCollection.h"
#include "AddHarmonicDlg.h"
#include "MainDlgPresenter.h"

BEGIN_MESSAGE_MAP(CHarmonicsApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CHarmonicsApp theApp;

BOOL CHarmonicsApp::InitInstance()
{
	CWinApp::InitInstance();
	AfxEnableControlContainer();


	CShellManager *pShellManager = new CShellManager;
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	MainDlg mainDlg;
	HarmonicCollection harmonics;
	AddHarmonicDlg addHarmonicDlg;
	CMainDlgPresenter presenter(harmonics, mainDlg, addHarmonicDlg);
	m_pMainWnd = &mainDlg;

	INT_PTR nResponse = mainDlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

