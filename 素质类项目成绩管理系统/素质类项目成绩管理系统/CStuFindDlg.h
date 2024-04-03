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
};
