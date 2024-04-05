#pragma once
#include "afxdialogex.h"


// CStuShowDlg 对话框

class CStuShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStuShowDlg)

public:
	CStuShowDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStuShowDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STU_SHOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_list_stuShow;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
private:
	CEdit m_edit_stuid;
	CEdit m_edit_stuname;
	CEdit m_edit_stugender;
public:
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
private:
	CButton m_btn_add;
	CButton m_btn_del;
};
