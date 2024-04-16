#pragma once



// CProjectManageDlg 窗体视图

class CProjectManageDlg : public CFormView
{
	DECLARE_DYNCREATE(CProjectManageDlg)

protected:
	CProjectManageDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CProjectManageDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CProjectManageDlg };
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
	virtual void OnInitialUpdate();
private:
	CString m_edit_id;
	CString m_edit_name;
	CString m_edit_gender;
	CString m_edit_title;
	CString m_edit_teacher;
	CString m_edit_number;
	CString m_edit_authors;
	CDateTimeCtrl m_date_begin;
	CDateTimeCtrl m_date_end;
	CButton m_btn_find;
	CButton m_btn_modify;
	CButton m_btn_add;
	CButton m_btn_del;
	CListCtrl m_list;
public:
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton1();
};


