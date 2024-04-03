// CScoreManageDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "CScoreManageDlg.h"


// CScoreManageDlg

IMPLEMENT_DYNCREATE(CScoreManageDlg, CFormView)

CScoreManageDlg::CScoreManageDlg()
	: CFormView(IDD_CScoreManageDlg)
{

}

CScoreManageDlg::~CScoreManageDlg()
{
}

void CScoreManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScoreManageDlg, CFormView)
END_MESSAGE_MAP()


// CScoreManageDlg 诊断

#ifdef _DEBUG
void CScoreManageDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CScoreManageDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CScoreManageDlg 消息处理程序
