#pragma once
#include "afxdialogex.h"


// CAddAwardDlg 对话框

class CAddAwardDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddAwardDlg)

public:
	CAddAwardDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddAwardDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDAWARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_edit_title;
	CString m_edit_organization;
	CString m_edit_level;
//	COleDateTime m_date;
	CString m_edit_teacher;
	CString m_edit_members;
	CString m_edit_id;
public:
	afx_msg void OnBnClickedButton7();
	virtual void OnOK();
private:
	CDateTimeCtrl m_date;
};
