#pragma once
#include "afxdialogex.h"


// CAddProjectDlg 对话框

class CAddProjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddProjectDlg)

public:
	CAddProjectDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddProjectDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDPROJECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_edit_title;
	CString m_edit_teacher;
	CString m_edit_number;
	CString m_edit_authors;
	CString m_edit_id;
	CDateTimeCtrl m_date_begin;
	CDateTimeCtrl m_date_end;
public:
	afx_msg void OnBnClickedButton7();
	virtual void OnOK();
	virtual void OnCancel();
};
