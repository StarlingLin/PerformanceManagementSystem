// CLoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "afxdialogex.h"
#include "CLoginDlg.h"
#include "InfoFile.h"
#include "md5.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDI_LOGIN, pParent)
	, m_pwd(_T(""))
	, m_user(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT1, m_user);
	//  DDX_Control(pDX, IDC_EDIT2, m_pwd);
	//  DDX_Control(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
	DDX_Text(pDX, IDC_EDIT1, m_user);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLoginDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
//	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取用户名和密码
	UpdateData(TRUE);
	
	if (m_user.IsEmpty() || m_pwd.IsEmpty())
	{
		MessageBox(_T("用户名或密码不能为空"), _T("登录失败"));
		return;
	}
	//判断用户名和密码是否正确
	//打开文件
	CInfoFile file;
	CString name, pwd_md5;
	file.ReadLoginInfo(name, pwd_md5);
	if (name == m_user)
	{
		//计算输入密码的MD5值
		string input = CT2A(m_pwd);
		if (MD5(input).toStr().c_str() == pwd_md5)
		{
			MessageBox(_T("成功进入系统"), _T("登录成功"));
			CDialogEx::OnCancel();
		}
		else
		{
			MessageBox(_T("密码错误"), _T("登录失败"));
			return;
		}
	}
	else
	{
		MessageBox(_T("用户名错误"), _T("登录失败"));
		return;
	}
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_font.CreateFont(
		50,                        // nHeight--字体的平均字符高度
		0,                         // nWidth--字体的平均字符宽度
		0,                         // nEscapement--角度
		0,                         // nOrientation--基线方向
		FW_REGULAR,                // nWeight--字体的粗细
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial"));              // lpszFacename

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	if (pEdit != nullptr)
	{
		pEdit->SetFont(&m_font);
	}
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT2);
	if (pEdit != nullptr)
	{
		pEdit->SetFont(&m_font);
	}
	CButton* pButton = (CButton*)GetDlgItem(IDC_BUTTON1);
	if (pButton != nullptr)
	{
		pButton->SetFont(&m_font);
	}
	
	//默认登录信息
	CInfoFile file;
	CString name, pwd_md5;
	file.ReadLoginInfo(name, pwd_md5);

	m_user = name;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CLoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	//处理叉掉对话框
	exit(0);
}


void CLoginDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	// CDialogEx::OnCancel();
	//处理esc退出
	exit(0);
}


//HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
//
	// TODO:  在此更改 DC 的任何特性
//	if (nCtlColor == CTLCOLOR_EDIT || nCtlColor == CTLCOLOR_BTN)
//	{
//		pDC->SetBkMode(TRANSPARENT); // 设置背景模式为透明
//		return (HBRUSH)::GetStockObject(NULL_BRUSH);
//	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
//	return hbr;
//}


void CLoginDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetClientRect(&rect); // 获取对话框的客户区大小

	CBitmap bitmap;
	if (bitmap.LoadBitmap(IDB_LOGIN))
	{
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);

		CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

		BITMAP bitmapInfo;
		bitmap.GetBitmap(&bitmapInfo);

		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, bitmapInfo.bmWidth, bitmapInfo.bmHeight, SRCCOPY);

		memDC.SelectObject(pOldBitmap);
	}
	else
	{
		// 处理图片加载失败的情况
	}

	// 调用基类的OnPaint()以处理其他绘制任务
	CDialogEx::OnPaint();
}
