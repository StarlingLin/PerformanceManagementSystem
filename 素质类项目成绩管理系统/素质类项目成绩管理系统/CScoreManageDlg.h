#pragma once



// CScoreManageDlg 窗体视图

class CScoreManageDlg : public CFormView
{
	DECLARE_DYNCREATE(CScoreManageDlg)

protected:
	CScoreManageDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CScoreManageDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CScoreManageDlg };
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
private:
	CListCtrl m_list_score;
//	CEdit m_edit_id;
//	CEdit m_edit_name;
	CString m_edit_id;
//	CEdit m_edit_name;
	CString m_edit_gender;
	CButton m_btn_find;
	CString m_edit_subject;
	CString m_edit_score;
	CButton m_chk;
	CButton m_btn_modify;
	CButton m_btn_del;
	CButton m_btn_add;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton4();
private:
	CString m_edit_name;
public:
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
};


