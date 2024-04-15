
// MainFrm.h: CMainFrame 类的接口
//

#pragma once

//自定义事件
#define NM_A	(WM_APP + 1)
#define NM_B	(WM_APP + 2)
#define NM_C	(WM_APP + 3)
#define NM_D	(WM_APP + 4)
#define NM_D1	(WM_APP + 5)
#define NM_D2	(WM_APP + 6)
#define NM_D3	(WM_APP + 7)

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

private:
	CSplitterWnd m_spliter;
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void On32771();
	afx_msg void On32772();
	afx_msg void On32774();
	afx_msg void On32773();
	afx_msg void On32776();
	afx_msg void On32777();
	afx_msg void On32778();
};


