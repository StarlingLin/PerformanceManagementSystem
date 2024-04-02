
// 素质类项目成绩管理系统Doc.h: C素质类项目成绩管理系统Doc 类的接口
//


#pragma once


class C素质类项目成绩管理系统Doc : public CDocument
{
protected: // 仅从序列化创建
	C素质类项目成绩管理系统Doc() noexcept;
	DECLARE_DYNCREATE(C素质类项目成绩管理系统Doc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~C素质类项目成绩管理系统Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
