#pragma once



// CAwardManageDlg 窗体视图

class CAwardManageDlg : public CFormView
{
	DECLARE_DYNCREATE(CAwardManageDlg)

protected:
	CAwardManageDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CAwardManageDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAwardManageDlg };
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
	CString m_edit_title;
	CString m_edit_organization;
	CString m_edit_grade;
	CDateTimeCtrl m_date;
	CString m_edit_teacher;
	CString m_edit_members;
	CButton m_btn_find;
	CButton m_btn_modify;
	CButton m_btn_add;
	CButton m_btn_del;
	CListCtrl m_list;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton1();
};


