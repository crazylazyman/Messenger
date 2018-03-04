
// MessengerClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MessengerClient.h"
#include "MessengerClientDlg.h"
#include "afxdialogex.h"
#include "DialogLogin.h"

#include <Protocol\Types.h>
#include <Protocol\UserInfo.h>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using UserInfo_t = std::pair<ID_t, std::string>;


static void *THISP;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMessengerClientDlg dialog



CMessengerClientDlg::CMessengerClientDlg(MessengerAPI& api,CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MESSENGERCLIENT_DIALOG, pParent),
	 API{ api }
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMessengerClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMessengerClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ButtonSend, &CMessengerClientDlg::OnBnClickedButtonsend)
	ON_WM_TIMER(&CMessengerClientDlg::OnTimer)
END_MESSAGE_MAP()


// CMessengerClientDlg message handlers


void CMessengerClientDlg::OnTimer(UINT_PTR event)
{
	
}


BOOL CMessengerClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CString IdCapture;
	IdCapture.Format(L"Your ID: %d : %s", API.GetCurrentUserID(), API.GetCurrentUserLogin().c_str() );
	SetDlgItemText(YourID, IdCapture);


	std::vector<UserInfo_t> Info;

	for (int i = 0; i < 20; ++i)
	{
		API.GetUserLogin(i);
	}
	for (int i = 0; i < 20; ++i)
	{
		while (!API.Ready());
		auto  packet = API.GetPacket();
		if (packet->GetType() == Types::UserInfo)
		{
			auto UserInf = static_cast<UserInfo*>(packet);
			if (UserInf->GetLogin() != "")
				Info.push_back({ UserInf->GetId() , UserInf->GetLogin() });
		}
	}

	UINT_PTR res = SetTimer(228, 300,NULL);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMessengerClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMessengerClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMessengerClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMessengerClientDlg::OnBnClickedButtonsend()
{
	uint32_t id = GetDlgItemInt(EditID, 0, 0);
	CString mes;
	
	GetDlgItemText(EditMessage, mes);
	if (mes == "")
		return;


}

