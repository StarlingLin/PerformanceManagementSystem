﻿
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "素质类项目成绩管理系统.h"
#include "MainFrm.h"
#include "InfoFile.h"
#include "CSelectView.h"
#include "CDisplayView.h"
#include "CUserDlg.h"
#include "CStuManageDlg.h"
#include "CScoreManageDlg.h"
#include "CTermManageDlg.h"
#include "CThesisManageDlg.h"
#include "CProjectManageDlg.h"
#include "CAwardManageDlg.h"
#include "CAddStuDlg.h"
#include "CAddScoreDlg.h"
#include "CAddThesisDlg.h"
#include "CAddProjectDlg.h"
#include "CAddAwardDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	//自定义消息
	ON_MESSAGE(NM_A, OnMyChange)
	ON_MESSAGE(NM_B, OnMyChange)
	ON_MESSAGE(NM_C, OnMyChange)
	ON_MESSAGE(NM_D, OnMyChange)
	ON_MESSAGE(NM_D1, OnMyChange)
	ON_MESSAGE(NM_D2, OnMyChange)
	ON_MESSAGE(NM_D3, OnMyChange)
	ON_COMMAND(ID_32771, &CMainFrame::On32771)
	ON_COMMAND(ID_32772, &CMainFrame::On32772)
	ON_COMMAND(ID_32774, &CMainFrame::On32774)
	ON_COMMAND(ID_32773, &CMainFrame::On32773)
	ON_COMMAND(ID_32776, &CMainFrame::On32776)
	ON_COMMAND(ID_32777, &CMainFrame::On32777)
	ON_COMMAND(ID_32778, &CMainFrame::On32778)
	ON_COMMAND(ID_32779, &CMainFrame::On32779)
	ON_COMMAND(ID_32780, &CMainFrame::On32780)
	ON_COMMAND(ID_32781, &CMainFrame::On32781)
	ON_COMMAND(ID_32782, &CMainFrame::On32782)
	ON_COMMAND(ID_32783, &CMainFrame::On32783)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//设置图标
	SetClassLongPtr(m_hWnd, GCLP_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_ICON_SYS));
	//设置右标题
	SetTitle(_T("吉林大学"));
	//设置窗口大小
	MoveWindow(0, 0, 1300, 880);
	//设置居中显示
	CenterWindow();

	//测试CInfoFile类
	//CInfoFile file;
	//CString name, pwd_md5;
	//file.ReadLoginInfo(name, pwd_md5);
	//MessageBox(name + ":" + pwd_md5);
	//file.WritePwd("root", "123456");
	//file.ReadLoginInfo(name, pwd_md5);
	//MessageBox(name + ":" + pwd_md5);

	//CInfoFile file;
	//file.WriteScoreInfo();
	//file.WriteThesisInfo();
	//file.WriteProjectInfo();
	//file.WriteAwardInfo();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	//设置窗口大小不可改变
	cs.style &= ~WS_THICKFRAME;

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	// return CFrameWnd::OnCreateClient(lpcs, pContext);
	//创建分割窗口
	m_spliter.CreateStatic(this, 1, 2);
	//创建左视图
	m_spliter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(200, 800), pContext);
	//创建右视图
	m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(1000, 800), pContext);

	return TRUE;
}

LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	CCreateContext context;
	if (wParam == NM_A)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CUserDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CUserDlg), CSize(1000, 800), &context);
		CUserDlg* pView = (CUserDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	else if (wParam == NM_B)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CStuManageDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CStuManageDlg), CSize(1000, 800), &context);
		CStuManageDlg* pView = (CStuManageDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	else if (wParam == NM_C)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CScoreManageDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CScoreManageDlg), CSize(1000, 800), &context);
		CScoreManageDlg* pView = (CScoreManageDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	else if (wParam == NM_D)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CTermManageDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CTermManageDlg), CSize(1000, 800), &context);
		CTermManageDlg* pView = (CTermManageDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	else if (wParam == NM_D1)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CThesisManageDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CThesisManageDlg), CSize(1000, 800), &context);
		CThesisManageDlg* pView = (CThesisManageDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	else if (wParam == NM_D2)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CProjectManageDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CProjectManageDlg), CSize(1000, 800), &context);
		CProjectManageDlg* pView = (CProjectManageDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	else if (wParam == NM_D3)
	{
		context.m_pNewViewClass = RUNTIME_CLASS(CAwardManageDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CAwardManageDlg), CSize(1000, 800), &context);
		CAwardManageDlg* pView = (CAwardManageDlg*)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}

	return 0;
}

void CMainFrame::On32771()
{
	// TODO: 在此添加命令处理程序代码
	exit(0);
}



void CMainFrame::On32772()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
}


void CMainFrame::On32774()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
}


void CMainFrame::On32773()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);
}



void CMainFrame::On32776()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D1, (WPARAM)NM_D1, (LPARAM)0);
}


void CMainFrame::On32777()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D2, (WPARAM)NM_D2, (LPARAM)0);
}



void CMainFrame::On32778()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D3, (WPARAM)NM_D3, (LPARAM)0);
}


void CMainFrame::On32779()
{
	// TODO: 在此添加命令处理程序代码
	CAddStuDlg dlg;
	dlg.DoModal();
}


void CMainFrame::On32780()
{
	// TODO: 在此添加命令处理程序代码
	CAddScoreDlg dlg;
	dlg.DoModal();
}


void CMainFrame::On32781()
{
	// TODO: 在此添加命令处理程序代码
	CAddThesisDlg dlg;
	dlg.DoModal();
}



void CMainFrame::On32782()
{
	// TODO: 在此添加命令处理程序代码
	CAddProjectDlg dlg;
	dlg.DoModal();
}


void CMainFrame::On32783()
{
	// TODO: 在此添加命令处理程序代码
	CAddAwardDlg dlg;
	dlg.DoModal();
}
