
// RedPacketVSDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RedPacketVS.h"
#include "RedPacketVSDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CRedPacketVSDlg 对话框




CRedPacketVSDlg::CRedPacketVSDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRedPacketVSDlg::IDD, pParent)
	, str(_T(""))
	, money(0)
	, number(0)
	, send_time(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRedPacketVSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_LBString(pDX, IDC_LIST1, str);
	DDX_Text(pDX, IDC_EDIT1, money);
	DDX_Text(pDX, IDC_EDIT2, number);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT3, send_time);
}

BEGIN_MESSAGE_MAP(CRedPacketVSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CRedPacketVSDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT2, &CRedPacketVSDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CRedPacketVSDlg::OnEnChangeEdit3)
END_MESSAGE_MAP()


// CRedPacketVSDlg 消息处理程序

BOOL CRedPacketVSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRedPacketVSDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRedPacketVSDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRedPacketVSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRedPacketVSDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	srand((unsigned)time(NULL));
	int* packet;
	//int number;
	//int money;
	int money_cp = money;
	int i, n;
	//printf("这里是拼手气抢红包游戏:)\n");
	
	//输入数据有效性检验

	if (money < 1 )
	{
		MessageBox(L"请重新设置总金额大于1");
		return;
	}
	if (number < 1 )
	{
		MessageBox(L"请重新设置人数大于1");
		return;
	}
	if (money < number)
	{
		MessageBox(L"红包太小不够分啊@_@");
		return;
	}
	if (send_time < 1)
	{
		MessageBox(L"再小气也得至少发一个吧。。。");
		return;
	}

	std::ofstream opt;
	opt.open("RedPacketResult.csv", std::ios::out | std::ios::trunc);
	//printf("请输入红包个数：");
	/*scanf("%d", &number);*/
	for (int j = 0; j < send_time; j++)
	{
		money = money_cp;
		packet = (int*)malloc(number * sizeof(int));

	/*printf("请输入总金额：");
	scanf("%d", &money);*/
		money -= number;
	
		for (i = 0; i < number - 1; i++)
		{
			int last = number - i;
			int max = 2 * money/last;
			packet[i] = rand() % (max+1 );
			money = money - packet[i];
			packet[i]++;
		}
		packet[i] = money+1;

		//printf("每按一次键就抢一个红包，开始了......\n");

		for (i = 0; i < number; i++)
		{

			do
			{
				n = rand() % number;
			} while (packet[n] == -1);
			str.Format(L"第%d个红包：%d\n", i + 1, packet[n]);
			m_list.InsertString(i, str);
			opt << "第" << i + 1 << "个红包" << ',';
			opt << packet[n]<<',';
			//write_to_excel(packet[n]);

			//printf("第%d个红包：%d\n", i + 1, packet[n]);
			packet[n] = -1;

		}
		opt << std::endl;
		free(packet);
	}
	
	opt.close();
}


void CRedPacketVSDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CRedPacketVSDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
