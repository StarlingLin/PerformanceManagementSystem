#pragma once

#include "TabSheet.h"
#include "CStuFindDlg.h"
#include "CStuShowDlg.h"

// CStuManageDlg 窗体视图

class CStuManageDlg : public CFormView
{
	DECLARE_DYNCREATE(CStuManageDlg)

protected:
	CStuManageDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CStuManageDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CStuManageDlg };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnInitialUpdate();
private:
	CTabSheet m_tab_stu;
	CStuFindDlg m_dlg_find;
	CStuShowDlg m_dlg_show;
};


