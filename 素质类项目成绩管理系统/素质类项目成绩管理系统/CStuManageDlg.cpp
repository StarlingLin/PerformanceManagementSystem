// CStuManageDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "CStuManageDlg.h"
#include "CStuFindDlg.h"
#include "CStuShowDlg.h"


// CStuManageDlg

IMPLEMENT_DYNCREATE(CStuManageDlg, CFormView)

CStuManageDlg::CStuManageDlg()
	: CFormView(IDD_CStuManageDlg)
{

}

CStuManageDlg::~CStuManageDlg()
{
}

void CStuManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab_stu);
}

BEGIN_MESSAGE_MAP(CStuManageDlg, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CStuManageDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CStuManageDlg 诊断

#ifdef _DEBUG
void CStuManageDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStuManageDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStuManageDlg 消息处理程序


void CStuManageDlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CStuManageDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_tab_stu.AddPage(_T("显示学生列表"), &m_dlg_show, IDD_STU_SHOW);
	m_tab_stu.AddPage(_T("查找学生信息"), &m_dlg_find, IDD_STU_FIND);
	m_tab_stu.Show();
}
