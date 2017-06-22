
// Harmonics.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

class CHarmonicsApp : public CWinApp
{
public:
    BOOL InitInstance() final;
protected:
	DECLARE_MESSAGE_MAP()
};

extern CHarmonicsApp theApp;