#pragma once
#include "afxdialogex.h"


// CStuFindDlg 对话框

class CStuFindDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStuFindDlg)

public:
	CStuFindDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStuFindDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STU_FIND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
private:
	CComboBox m_cbxFind;
public:
//	afx_msg void OnEnChangeEdit3();
private:
	CEdit m_edit_find;
	CEdit m_edit_id;
	CEdit m_edit_name;
	CEdit m_edit_gender;
	CButton m_chk;
public:
	afx_msg void OnBnClickedCheck1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	virtual void OnOK();
private:
	CListCtrl m_list_find;
public:
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton4();
private:
	CButton m_btn_find;
	CButton m_btn_del;
public:
	afx_msg void OnBnClickedButton2();
private:
	CButton m_btn_cfmedit;
};
