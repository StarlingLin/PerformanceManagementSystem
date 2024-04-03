// CAwardManageDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "CAwardManageDlg.h"


// CAwardManageDlg

IMPLEMENT_DYNCREATE(CAwardManageDlg, CFormView)

CAwardManageDlg::CAwardManageDlg()
	: CFormView(IDD_CAwardManageDlg)
{

}

CAwardManageDlg::~CAwardManageDlg()
{
}

void CAwardManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAwardManageDlg, CFormView)
END_MESSAGE_MAP()


// CAwardManageDlg 诊断

#ifdef _DEBUG
void CAwardManageDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAwardManageDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAwardManageDlg 消息处理程序
