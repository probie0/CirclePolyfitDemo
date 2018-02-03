
// CirclePolyfitDemoDlg.h : 头文件
//

#pragma once


// CCirclePolyfitDemoDlg 对话框
class CCirclePolyfitDemoDlg : public CDialogEx
{
// 构造
public:
	CCirclePolyfitDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CIRCLEPOLYFITDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCalc();
	double data11;
	double data12;
	double data21;
	double data22;
	double data31;
	double data32;
	double data41;
	double data42;
	double data51;
	double data52;
	double data61;
	double data62;
	afx_msg void OnStnClickedStaticAngle();
};
