// CThesisManageDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "CThesisManageDlg.h"


// CThesisManageDlg

IMPLEMENT_DYNCREATE(CThesisManageDlg, CFormView)

CThesisManageDlg::CThesisManageDlg()
	: CFormView(IDD_CThesisManageDlg)
{

}

CThesisManageDlg::~CThesisManageDlg()
{
}

void CThesisManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CThesisManageDlg, CFormView)
END_MESSAGE_MAP()


// CThesisManageDlg 诊断

#ifdef _DEBUG
void CThesisManageDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CThesisManageDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CThesisManageDlg 消息处理程序
