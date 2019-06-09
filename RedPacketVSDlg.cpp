
// RedPacketVSDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RedPacketVS.h"
#include "RedPacketVSDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CRedPacketVSDlg �Ի���




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


// CRedPacketVSDlg ��Ϣ�������

BOOL CRedPacketVSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRedPacketVSDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CRedPacketVSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRedPacketVSDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	srand((unsigned)time(NULL));
	int* packet;
	//int number;
	//int money;
	int money_cp = money;
	int i, n;
	//printf("������ƴ�����������Ϸ:)\n");
	
	//����������Ч�Լ���

	if (money < 1 )
	{
		MessageBox(L"�����������ܽ�����1");
		return;
	}
	if (number < 1 )
	{
		MessageBox(L"������������������1");
		return;
	}
	if (money < number)
	{
		MessageBox(L"���̫С�����ְ�@_@");
		return;
	}
	if (send_time < 1)
	{
		MessageBox(L"��С��Ҳ�����ٷ�һ���ɡ�����");
		return;
	}

	std::ofstream opt;
	opt.open("RedPacketResult.csv", std::ios::out | std::ios::trunc);
	//printf("��������������");
	/*scanf("%d", &number);*/
	for (int j = 0; j < send_time; j++)
	{
		money = money_cp;
		packet = (int*)malloc(number * sizeof(int));

	/*printf("�������ܽ�");
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

		//printf("ÿ��һ�μ�����һ���������ʼ��......\n");

		for (i = 0; i < number; i++)
		{

			do
			{
				n = rand() % number;
			} while (packet[n] == -1);
			str.Format(L"��%d�������%d\n", i + 1, packet[n]);
			m_list.InsertString(i, str);
			opt << "��" << i + 1 << "�����" << ',';
			opt << packet[n]<<',';
			//write_to_excel(packet[n]);

			//printf("��%d�������%d\n", i + 1, packet[n]);
			packet[n] = -1;

		}
		opt << std::endl;
		free(packet);
	}
	
	opt.close();
}


void CRedPacketVSDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CRedPacketVSDlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
