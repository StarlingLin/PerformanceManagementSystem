
// 素质类项目成绩管理系统View.h: C素质类项目成绩管理系统View 类的接口
//

#pragma once


class C素质类项目成绩管理系统View : public CView
{
protected: // 仅从序列化创建
	C素质类项目成绩管理系统View() noexcept;
	DECLARE_DYNCREATE(C素质类项目成绩管理系统View)

// 特性
public:
	C素质类项目成绩管理系统Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~C素质类项目成绩管理系统View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 素质类项目成绩管理系统View.cpp 中的调试版本
inline C素质类项目成绩管理系统Doc* C素质类项目成绩管理系统View::GetDocument() const
   { return reinterpret_cast<C素质类项目成绩管理系统Doc*>(m_pDocument); }
#endif

