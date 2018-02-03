
// CirclePolyfitDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CirclePolyfitDemo.h"
#include "CirclePolyfitDemoDlg.h"
#include "afxdialogex.h"
#include <Eigen\Dense>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define maxCnt 6            //ϵͳ��������������������
#define xzero 30              //��������������� 
#define yzero 260                  //�豸����y�������������Ƶ����귽���෴��Ҫ�Ӹ�����
#define xmax 420              //x���������ֵ
#define ymax 30              //y���������ֵ��������豸����������˵����С��
using Eigen::MatrixXd;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCirclePolyfitDemoDlg �Ի���



CCirclePolyfitDemoDlg::CCirclePolyfitDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CIRCLEPOLYFITDEMO_DIALOG, pParent)
	, data11(0)
	, data12(0)
	, data21(0)
	, data22(0)
	, data31(0)
	, data32(0)
	, data41(0)
	, data42(0)
	, data51(0)
	, data52(0)
	, data61(0)
	, data62(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCirclePolyfitDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT11, data11);
	DDX_Text(pDX, IDC_EDIT12, data12);
	DDX_Text(pDX, IDC_EDIT21, data21);
	DDX_Text(pDX, IDC_EDIT22, data22);
	DDX_Text(pDX, IDC_EDIT31, data31);
	DDX_Text(pDX, IDC_EDIT32, data32);
	DDX_Text(pDX, IDC_EDIT41, data41);
	DDX_Text(pDX, IDC_EDIT42, data42);
	DDX_Text(pDX, IDC_EDIT51, data51);
	DDX_Text(pDX, IDC_EDIT52, data52);
	DDX_Text(pDX, IDC_EDIT61, data61);
	DDX_Text(pDX, IDC_EDIT62, data62);
}

BEGIN_MESSAGE_MAP(CCirclePolyfitDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CALC, &CCirclePolyfitDemoDlg::OnBnClickedBtnCalc)
	ON_STN_CLICKED(IDC_STATIC_ANGLE, &CCirclePolyfitDemoDlg::OnStnClickedStaticAngle)
END_MESSAGE_MAP()


// CCirclePolyfitDemoDlg ��Ϣ�������

BOOL CCirclePolyfitDemoDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCirclePolyfitDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCirclePolyfitDemoDlg::OnPaint()
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
		//����ͼ������

		CWnd *pWnd;
		pWnd = GetDlgItem(IDC_FIGURE);  //�õ��ؼ����
		CDC* pdc = pWnd->GetDC();
		pdc->MoveTo(xzero, ymax);
		pdc->LineTo(xzero, yzero);
		pdc->LineTo(xmax, yzero);
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCirclePolyfitDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCirclePolyfitDemoDlg::OnBnClickedBtnCalc()
{
	UpdateData(TRUE);
	MatrixXd o(maxCnt+1, 3);
	o << 0, 0, 0,                               //Ϊ���±�ʹ�÷��㣬���ȫΪ0�����к����У�ʹ֮������ѧ������±�����ϰ��
		0, data11, data12,
		0, data21, data22,
		0, data31, data32,
		0, data41, data42,
		0, data51, data52,
		0, data61, data62;


	double o0[maxCnt+1] = {};
	double r[maxCnt+1] = {};
	
	int cnt{6};                        //��ʾ�������ݵ���������ʼ��Ϊ�����������6

	for (int i = 1; i <= maxCnt; i++)
	{
		o0[i] = (o(i, 1) + o(i, 2)) / 2;
		r[i] = (o(i, 1) - o(i, 2)) / 2;
		if (r[i] == 0)
		{
			cnt = i - 1;  
			break;                         //��������һ���뾶Ϊ0���飬cnt = i-1�����������һ������Ƴ�ѭ��ʱ��������Ϊ��ʼ����ֵmaxCnt
		}
	}                                        //������forѭ�������յ㶼Ϊ i<=cnt
	  


	double res1{}, res2{};
	double res1k{}, res1c{}, res2k{}, res2c{};      //ƫ����
	double k{}, c{};      //��ֵΪ0
	MatrixXd mat_J(2, 2), mat_S(2, 1), mat_R(2, 1);               //J*S=R   =>  S=J.inverse*R  �˴�����������Ҫ���о������㣬���Բ������ȫΪ0�����к�����

	res1c = cnt;
	do
	{
		res1 = 0; res2 = 0; res1k = 0; /*res1c �����3*/; res2k = 0; res2c = 0;
		for (int i = 1; i <= cnt; i++)
		{
			res1 = o0[i] * k + c - r[i] * sqrt(1 + k*k) + res1;
			res2 = (o0[i] * k + c - r[i] * sqrt(1 + k*k))*(2 * o0[i] - k * 2 * (r[i]) / sqrt(1 + k*k)) + res2;
			res1k = o0[i] - r[i] * k / sqrt(1 + k*k) + res1k;
			//	res1c�Ѹ�ֵ
			res2k = (o0[i] - k*r[i] / sqrt(1 + k*k)) * (2 * o0[i] - k * 2 * r[i] / sqrt(1 + k*k))
				+ (o0[i] * k + c - r[i] * sqrt(1 + k*k)) * (2 * r[i] * sqrt(1 + k*k) - k*k * 2 * r[i] / sqrt(1 + k*k)) / (-k*k - 1) + res2k;
			res2c = 2 * o0[i] - k * 2 * r[i] / sqrt(1 + k*k) + res2c;

		}

		mat_J <<
			res1k, res1c,
			res2k, res2c;
		mat_R <<
			-res1,
			-res2;

		mat_S = mat_J.inverse()*mat_R;
		k = k + mat_S(0, 0);
		c = c + mat_S(1, 0);
		
		
	} while (sqrt(mat_S(0, 0)*mat_S(0, 0) + mat_S(1, 0)*mat_S(1, 0)) > 0.001);

	double angle1 = atan(k);
	double angle2 = angle1 / 3.141592654 * 180;
	CString str_k, str_c, str_angle1, str_angle2, str_angle;
	str_k.Format(_T("%lf"), k);
	str_c.Format(_T("%lf"), c);
	str_angle1.Format(_T("%lfrad \\ "), angle1);
	str_angle2.Format(_T("%lf��"), angle2);
	str_angle = str_angle1 + str_angle2;
	SetDlgItemText(IDC_STATIC_K, str_k.GetBuffer());
	SetDlgItemText(IDC_STATIC_C, str_c.GetBuffer());
	SetDlgItemText(IDC_STATIC_ANGLE, str_angle);


		//����Ӧ��Բ
	
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_FIGURE);  //�õ��ؼ����
	CDC* pdc = pWnd->GetDC();        //�õ��ؼ��豸����
	CRect wholeArea(xzero+1, ymax, xmax, yzero-1);
	pdc->FillSolidRect(wholeArea, RGB(240, 240, 240));                                       //����ϴε�ͼ��
	
	double o0Max{};                     //�ҳ�λ������˵�Ӧ��Բ��Բ������ 
	int o0MaxIdx{};                               //��Ӧ������
	for (int i = 1; i <= cnt; i++)
	{
		if (o0Max < o0[i])
		{
			o0Max = o0[i];
			o0MaxIdx = i;
		}
	}
	
	double scale{};          //ͼ�����
	scale = (xmax-50) / o(o0MaxIdx, 1);

	//����Ӧ��Բ
	for (int i = 0; i <= cnt; i++)
	{
		CRect rect(int(xzero+scale*o(i,1)), int(yzero-scale*r[i]), int(xzero+scale*o(i,2)), int(yzero+scale*r[i]));
		POINT start; start.x = int(xzero+scale*o(i,1)); start.y = yzero;
		POINT end; end.x = int(xzero + scale*o(i, 2)); end.y = yzero;
		pdc->MoveTo(start);
		pdc->ArcTo(rect, start, end);
	}
	//�����������
	pdc->MoveTo(xzero, int(yzero - scale*c));
	pdc->LineTo(int(xzero+scale*o(o0MaxIdx,1)), int(yzero-scale*(o(o0MaxIdx,1)*k + c)));

}


void CCirclePolyfitDemoDlg::OnStnClickedStaticAngle()
{
	// TODO: Add your control notification handler code here
}
