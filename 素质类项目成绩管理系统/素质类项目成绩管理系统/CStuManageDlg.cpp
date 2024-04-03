// CStuManageDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "CStuManageDlg.h"


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
}

BEGIN_MESSAGE_MAP(CStuManageDlg, CFormView)
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
