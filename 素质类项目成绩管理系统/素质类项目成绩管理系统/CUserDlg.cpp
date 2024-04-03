// CUserDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "CUserDlg.h"
#include "InfoFile.h"
#include "md5.h"


// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(IDD_CUserDlg)
	, m_userstage(_T(""))
	, m_username(_T(""))
	, m_newpwd(_T(""))
	, m_cfrmpwd(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_userstage);
	DDX_Text(pDX, IDC_EDIT2, m_username);
	DDX_Text(pDX, IDC_EDIT3, m_newpwd);
	DDX_Text(pDX, IDC_EDIT4, m_cfrmpwd);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CUserDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg 消息处理程序


void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_userstage = _T("系统管理员");
	
	CInfoFile file;
	CString name, pwd;
	file.ReadLoginInfo(name, pwd);
	m_username = name;

	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);	//更新数据到变量

	if (m_newpwd.IsEmpty() || m_cfrmpwd.IsEmpty())
	{
		MessageBox(_T("密码不能为空"), _T("修改失败"));
		return;
	}

	if (m_newpwd != m_cfrmpwd)
	{
		MessageBox(_T("两次密码不一致"), _T("修改失败"));
		return;
	}

	CInfoFile file;
	CString name, pwdmd5;
	file.ReadLoginInfo(name, pwdmd5);
	string pwd = CT2A(m_newpwd);
	if (pwdmd5 == MD5(pwd).toStr().c_str())
	{
		MessageBox(_T("新密码不能与旧密码相同"), _T("修改失败"));
		return;
	}
	CStringA tmp;
	CStringA tmp2;
	tmp = name;
	tmp2 = MD5(pwd).toStr().c_str();
	file.WritePwd(tmp.GetBuffer(), tmp2.GetBuffer());
	MessageBox(_T("修改成功"), _T("提示"));

	//清空数据
	m_newpwd.Empty();
	m_cfrmpwd.Empty();
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_newpwd.Empty();
	m_cfrmpwd.Empty();
	UpdateData(FALSE);
}
