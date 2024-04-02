
// 素质类项目成绩管理系统.h: 素质类项目成绩管理系统 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号


// C素质类项目成绩管理系统App:
// 有关此类的实现，请参阅 素质类项目成绩管理系统.cpp
//

class C素质类项目成绩管理系统App : public CWinApp
{
public:
	C素质类项目成绩管理系统App() noexcept;


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern C素质类项目成绩管理系统App theApp;
