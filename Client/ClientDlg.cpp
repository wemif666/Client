
// ClientDlg.cpp 
//
/*
Coded by Rogoz

*/

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "ClientCon.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif




class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// dane okna dial.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementacja
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientDlg dialogowe okno




CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent),
	m_pClient(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Textbox);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CClientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CClientDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CClientDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CClientDlg uchwyty wiadomosci

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Ikona.  
	SetIcon(m_hIcon, TRUE);			// duza
	SetIcon(m_hIcon, FALSE);		// mala

	

	return TRUE;  
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon. 
void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// rysowanie ikony
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// przesywanie zminimalizowanej aplikacji
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClientDlg::OnBnClickedOk()
{
	
	//CDialogEx::OnOK();
	//OnBnClickedButton1();
	OnBnClickedButton4();
}

void CClientDlg::OnBnClickedButton2()
{
	
	cTh = AfxBeginThread(
    StaticThreadFunc,
    this);
	
	//cTh->m_bAutoDelete = FALSE;
	m_Thread_handle = cTh->m_hThread;
}


void CClientDlg::OnBnClickedButton4()
{
	
	CString sTextData;
	GetDlgItemText(IDC_EDIT7, sTextData);
	
	CT2CA CStringToAscii(sTextData);

      // konstruktor std::string 
     std::string sResultedString (CStringToAscii);
	 if(m_pClient != NULL)
	 m_pClient->SendData(sResultedString);
	 CWnd* pWnd = GetDlgItem(IDC_EDIT7);
	 pWnd->SetWindowText(_T(""));
}


void CClientDlg::ShowServerInfo(string sValue)
{
	CString strLine(sValue.c_str());
	// dodanie CR/LF
	//MessageBox(sValue.c_str());
	AppendTextToEditCtrl(m_Textbox, strLine);
	//DoModal();
	//UpdateData(TRUE);
}

void CClientDlg::AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText)
{
   // pobieranie dlugosci tekstu
   int nLength = edit.GetWindowTextLength();
   //zaznaczenie na koncu txt
   edit.SetSel(nLength, nLength);
   //podmiana zaznaczenia
   edit.ReplaceSel(pszText);
}

UINT __cdecl CClientDlg::StaticThreadFunc(LPVOID pParam)
{
	CClientDlg *pYourClass = reinterpret_cast<CClientDlg*>(pParam);
    UINT retCode = pYourClass->ThreadFunc();

    return retCode;
}

UINT CClientDlg::ThreadFunc()
{ 
  
	

	CString txtname; 
	GetDlgItemText(IDC_EDIT2, txtname);

	CString portname;
	GetDlgItemText(IDC_EDIT3, portname);
	int iPort = _wtoi( portname.GetString() );
	
	CString username;
	GetDlgItemText(IDC_EDIT6, username);

	m_pClient = new ClientCon(this);

	CT2CA CStringToAscii(txtname);

    
     std::string sResultedString (CStringToAscii);
     
	CT2CA CStringToAscii2(username);

	std::string sResultedString2 (CStringToAscii2);

	m_pClient->StartConnect(sResultedString, iPort, sResultedString2);
	return 0;
}


void CClientDlg::OnBnClickedButton3()
{
	
	
	ShowServerInfo(m_pClient->m_pUser+ " is logged out\n");
	delete m_pClient;
}
