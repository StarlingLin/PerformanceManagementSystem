#pragma once
#include "afxdialogex.h"


// CAddScoreDlg 对话框

class CAddScoreDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddScoreDlg)

public:
	CAddScoreDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddScoreDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDSCORE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
private:
	CString m_edit_id;
//	CEdit m_edit_subject;
//	CString m;
	CString m_edit_subject;
	CString m_edit_score;
public:
	afx_msg void OnBnClickedButton4();
};
