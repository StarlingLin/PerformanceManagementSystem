#pragma once
#include "afxdialogex.h"


// CAddThesisDlg 对话框

class CAddThesisDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddThesisDlg)

public:
	CAddThesisDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddThesisDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDTHESIS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString m_edit_title;
	CString m_edit_periodical;
	CString m_edit_pagination;
	CString m_edit_author0;
	CComboBox m_cbx;
	CString m_edit_author;
	CDateTimeCtrl m_date;
	CString m_edit_id;
public:
	afx_msg void OnBnClickedButton7();
	virtual void OnOK();
	virtual void OnCancel();
};
