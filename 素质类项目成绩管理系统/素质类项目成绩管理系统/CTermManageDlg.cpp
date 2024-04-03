// CTermManageDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "CTermManageDlg.h"


// CTermManageDlg

IMPLEMENT_DYNCREATE(CTermManageDlg, CFormView)

CTermManageDlg::CTermManageDlg()
	: CFormView(IDD_CTermManageDlg)
{

}

CTermManageDlg::~CTermManageDlg()
{
}

void CTermManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTermManageDlg, CFormView)
END_MESSAGE_MAP()


// CTermManageDlg 诊断

#ifdef _DEBUG
void CTermManageDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTermManageDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTermManageDlg 消息处理程序
