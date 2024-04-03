// CProjectManageDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "CProjectManageDlg.h"


// CProjectManageDlg

IMPLEMENT_DYNCREATE(CProjectManageDlg, CFormView)

CProjectManageDlg::CProjectManageDlg()
	: CFormView(IDD_CProjectManageDlg)
{

}

CProjectManageDlg::~CProjectManageDlg()
{
}

void CProjectManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CProjectManageDlg, CFormView)
END_MESSAGE_MAP()


// CProjectManageDlg 诊断

#ifdef _DEBUG
void CProjectManageDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CProjectManageDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CProjectManageDlg 消息处理程序
