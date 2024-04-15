#pragma once



// CThesisManageDlg 窗体视图

class CThesisManageDlg : public CFormView
{
	DECLARE_DYNCREATE(CThesisManageDlg)

protected:
	CThesisManageDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CThesisManageDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CThesisManageDlg };
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
	CString m_edit_id;
	CString m_edit_name;
	CString m_edit_gender;
	CListCtrl m_list;
public:
	afx_msg void OnBnClickedButton4();
	virtual void OnInitialUpdate();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
private:
	CString m_edit_title;
	CString m_edit_periodical;
	CString m_edit_pagination;
	CString m_edit_author0;
	CString m_edit_author;
	CDateTimeCtrl m_date;
public:
	CComboBox m_cbx;
	afx_msg void OnBnClickedCheck3();
private:
	CButton m_btn_find;
	CButton m_btn_add;
	CButton m_btn_modify;
	CButton m_btn_del;
public:
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton1();
};


