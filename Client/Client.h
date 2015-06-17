/*
Coded by Rogoz
*/
// Client.h :plik nagl
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"	


// CClientApp:


class CClientApp : public CWinApp
{
public:
	CClientApp();


public:
	virtual BOOL InitInstance();



	DECLARE_MESSAGE_MAP()
};

extern CClientApp theApp;