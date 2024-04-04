// CAddStuDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "afxdialogex.h"
#include "CAddStuDlg.h"
#include "InfoFile.h"
#include "MainFrm.h"

// CAddStuDlg 对话框

IMPLEMENT_DYNAMIC(CAddStuDlg, CDialogEx)

CAddStuDlg::CAddStuDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDSTU, pParent)
{

}

CAddStuDlg::~CAddStuDlg()
{
}

void CAddStuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit_a1);
	DDX_Control(pDX, IDC_EDIT2, m_edit_a2);
	DDX_Control(pDX, IDC_EDIT4, m_edit_a3);
}


BEGIN_MESSAGE_MAP(CAddStuDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddStuDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAddStuDlg 消息处理程序


void CAddStuDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CAddStuDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取编辑框内容
	CString strid, strname, strgender;
	m_edit_a1.GetWindowText(strid);
	m_edit_a2.GetWindowText(strname);
	m_edit_a3.GetWindowText(strgender);

	//判断是否为空
	if (strid.IsEmpty() || strname.IsEmpty() || strgender.IsEmpty())
	{
		MessageBox(_T("请填写完整信息"), _T("提示"));
		return;
	}

	//判断学号是否重复	
	CInfoFile fstu;
	fstu.ReadStudentInfo();
	int id = _ttoi(strid);
	if (fstu.IsIDExist(id))
	{
		MessageBox(_T("学号已存在"), _T("提示"));
		return;
	}

	//添加学生信息
	Student* stu = new Student;
	stu->id = id;
	LPCTSTR wideStr = strname.GetString();
	int len = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, NULL, 0, NULL, NULL);
	char* p = new char[len];
	WideCharToMultiByte(CP_ACP, 0, wideStr, -1, p, len, NULL, NULL);
	strcpy(stu->name, p);
	delete[] p;

	wideStr = strgender.GetString();
	len = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, NULL, 0, NULL, NULL);
	p = new char[len];
	WideCharToMultiByte(CP_ACP, 0, wideStr, -1, p, len, NULL, NULL);
	strcpy(stu->gender, p);
	delete[] p;

	stu->awardNum = 0;
	stu->projectNum = 0;
	stu->scoreNum = 0;
	stu->thesisNum = 0;
	memset(stu->award, 0, sizeof(stu->award));
	memset(stu->project, 0, sizeof(stu->project));
	memset(stu->score, 0, sizeof(stu->score));

	fstu.AddStudent(stu);
	fstu.WriteStudentInfo();

	MessageBox(_T("添加成功"), _T("提示"));

	CDialogEx::OnOK();
}
