
// CirclePolyfitDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCirclePolyfitDemoApp: 
// �йش����ʵ�֣������ CirclePolyfitDemo.cpp
//

class CCirclePolyfitDemoApp : public CWinApp
{
public:
	CCirclePolyfitDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCirclePolyfitDemoApp theApp;