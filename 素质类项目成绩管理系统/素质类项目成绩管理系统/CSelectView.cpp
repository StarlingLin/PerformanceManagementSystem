// CSelectView.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "CSelectView.h"
#include "MainFrm.h"

// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CTreeView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}

BEGIN_MESSAGE_MAP(CSelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSelectView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CSelectView 诊断

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSelectView 消息处理程序


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_imageList.Create(24, 24, ILC_COLOR32, 4, 4);
	m_imageList.Add(AfxGetApp()->LoadIconW(IDI_ICON2));
	m_imageList.Add(AfxGetApp()->LoadIconW(IDI_ICON3));
	m_imageList.Add(AfxGetApp()->LoadIconW(IDI_ICON4));
	m_imageList.Add(AfxGetApp()->LoadIconW(IDI_ICON5));

	m_treeCtrl = &GetTreeCtrl();
	m_treeCtrl->SetImageList(&m_imageList, TVSIL_NORMAL);

	//设置树形控件的风格
	m_treeCtrl->ModifyStyle(0, TVS_HASLINES | TVS_SHOWSELALWAYS);

	HTREEITEM s = m_treeCtrl->InsertItem(_T("个人信息"), 3, 3);
	m_treeCtrl->InsertItem(_T("学生管理"), 0, 0);
	m_treeCtrl->InsertItem(_T("成绩管理"), 2, 2);
	HTREEITEM r = m_treeCtrl->InsertItem(_T("素质类项"), 2, 2);
	m_treeCtrl->InsertItem(_T("论文管理"), 1, 1, r);
	m_treeCtrl->InsertItem(_T("项目管理"), 1, 1, r);
	m_treeCtrl->InsertItem(_T("获奖管理"), 1, 1, r);

	//默认选中第一个
	m_treeCtrl->SelectItem(s);

	//默认展开
	m_treeCtrl->Expand(r, TVE_EXPAND);
}


void CSelectView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	//获取当前选中的树形控件的项
	HTREEITEM hItem = m_treeCtrl->GetSelectedItem();
	//获取当前选中的树形控件的项的文本
	CString str = m_treeCtrl->GetItemText(hItem);
	//MessageBox(str);
	if (str == _T("个人信息"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
	}
	else if (str == _T("学生管理"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
	}
	else if (str == _T("成绩管理"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);
	}
	else if (str == _T("素质类项"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D, (WPARAM)NM_D, (LPARAM)0);
	}
	else if (str == _T("论文管理"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D1, (WPARAM)NM_D1, (LPARAM)0);
	}
	else if (str == _T("项目管理"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D2, (WPARAM)NM_D2, (LPARAM)0);
	}
	else if (str == _T("获奖管理"))
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D3, (WPARAM)NM_D3, (LPARAM)0);
	}
}
