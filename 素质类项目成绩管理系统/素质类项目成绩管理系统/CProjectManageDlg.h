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
};


