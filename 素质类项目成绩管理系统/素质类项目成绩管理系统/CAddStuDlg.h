#pragma once
#include "afxdialogex.h"


// CAddStuDlg 对话框

class CAddStuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddStuDlg)

public:
	CAddStuDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddStuDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDSTU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
private:
	CEdit m_edit_a1;
	CEdit m_edit_a2;
	CEdit m_edit_a3;
public:
	afx_msg void OnBnClickedButton1();
};
