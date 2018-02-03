
// CirclePolyfitDemoDlg.cpp : 实现文件
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

#define maxCnt 6            //系统允许输入最多的数据组数
#define xzero 30              //定义横纵坐标的起点 
#define yzero 260                  //设备环境y轴坐标与所绘制的坐标方向相反，要加个负号
#define xmax 420              //x轴最大坐标值
#define ymax 30              //y轴最大坐标值（相对于设备环境坐标来说是最小）
using Eigen::MatrixXd;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCirclePolyfitDemoDlg 对话框



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


// CCirclePolyfitDemoDlg 消息处理程序

BOOL CCirclePolyfitDemoDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCirclePolyfitDemoDlg::OnPaint()
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
		//绘制图像坐标

		CWnd *pWnd;
		pWnd = GetDlgItem(IDC_FIGURE);  //得到控件句柄
		CDC* pdc = pWnd->GetDC();
		pdc->MoveTo(xzero, ymax);
		pdc->LineTo(xzero, yzero);
		pdc->LineTo(xmax, yzero);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCirclePolyfitDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCirclePolyfitDemoDlg::OnBnClickedBtnCalc()
{
	UpdateData(TRUE);
	MatrixXd o(maxCnt+1, 3);
	o << 0, 0, 0,                               //为了下标使用方便，添加全为0的首行和首列，使之符合数学矩阵的下标引用习惯
		0, data11, data12,
		0, data21, data22,
		0, data31, data32,
		0, data41, data42,
		0, data51, data52,
		0, data61, data62;


	double o0[maxCnt+1] = {};
	double r[maxCnt+1] = {};
	
	int cnt{6};                        //表示输入数据的组数，初始化为最大允许组数6

	for (int i = 1; i <= maxCnt; i++)
	{
		o0[i] = (o(i, 1) + o(i, 2)) / 2;
		r[i] = (o(i, 1) - o(i, 2)) / 2;
		if (r[i] == 0)
		{
			cnt = i - 1;  
			break;                         //迭代到第一个半径为0的组，cnt = i-1。迭代到最后一个组才推出循环时，组数即为初始化的值maxCnt
		}
	}                                        //后续的for循环迭代终点都为 i<=cnt
	  


	double res1{}, res2{};
	double res1k{}, res1c{}, res2k{}, res2c{};      //偏导数
	double k{}, c{};      //初值为0
	MatrixXd mat_J(2, 2), mat_S(2, 1), mat_R(2, 1);               //J*S=R   =>  S=J.inverse*R  此处这三个矩阵要进行矩阵运算，所以不能添加全为0的首行和首列

	res1c = cnt;
	do
	{
		res1 = 0; res2 = 0; res1k = 0; /*res1c 恒等于3*/; res2k = 0; res2c = 0;
		for (int i = 1; i <= cnt; i++)
		{
			res1 = o0[i] * k + c - r[i] * sqrt(1 + k*k) + res1;
			res2 = (o0[i] * k + c - r[i] * sqrt(1 + k*k))*(2 * o0[i] - k * 2 * (r[i]) / sqrt(1 + k*k)) + res2;
			res1k = o0[i] - r[i] * k / sqrt(1 + k*k) + res1k;
			//	res1c已赋值
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
	str_angle2.Format(_T("%lf°"), angle2);
	str_angle = str_angle1 + str_angle2;
	SetDlgItemText(IDC_STATIC_K, str_k.GetBuffer());
	SetDlgItemText(IDC_STATIC_C, str_c.GetBuffer());
	SetDlgItemText(IDC_STATIC_ANGLE, str_angle);


		//绘制应力圆
	
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_FIGURE);  //得到控件句柄
	CDC* pdc = pWnd->GetDC();        //得到控件设备环境
	CRect wholeArea(xzero+1, ymax, xmax, yzero-1);
	pdc->FillSolidRect(wholeArea, RGB(240, 240, 240));                                       //清除上次的图像
	
	double o0Max{};                     //找出位于最左端的应力圆的圆心坐标 
	int o0MaxIdx{};                               //对应的组数
	for (int i = 1; i <= cnt; i++)
	{
		if (o0Max < o0[i])
		{
			o0Max = o0[i];
			o0MaxIdx = i;
		}
	}
	
	double scale{};          //图像比例
	scale = (xmax-50) / o(o0MaxIdx, 1);

	//绘制应力圆
	for (int i = 0; i <= cnt; i++)
	{
		CRect rect(int(xzero+scale*o(i,1)), int(yzero-scale*r[i]), int(xzero+scale*o(i,2)), int(yzero+scale*r[i]));
		POINT start; start.x = int(xzero+scale*o(i,1)); start.y = yzero;
		POINT end; end.x = int(xzero + scale*o(i, 2)); end.y = yzero;
		pdc->MoveTo(start);
		pdc->ArcTo(rect, start, end);
	}
	//绘制拟合曲线
	pdc->MoveTo(xzero, int(yzero - scale*c));
	pdc->LineTo(int(xzero+scale*o(o0MaxIdx,1)), int(yzero-scale*(o(o0MaxIdx,1)*k + c)));

}


void CCirclePolyfitDemoDlg::OnStnClickedStaticAngle()
{
	// TODO: Add your control notification handler code here
}
