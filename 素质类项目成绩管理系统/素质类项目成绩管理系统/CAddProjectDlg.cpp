// CAddProjectDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "afxdialogex.h"
#include "CAddProjectDlg.h"
#include "InfoFile.h"


// CAddProjectDlg 对话框

IMPLEMENT_DYNAMIC(CAddProjectDlg, CDialogEx)

CAddProjectDlg::CAddProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDPROJECT, pParent)
	, m_edit_title(_T(""))
	, m_edit_teacher(_T(""))
	, m_edit_number(_T(""))
	, m_edit_authors(_T(""))
	, m_edit_id(_T(""))
{

}

CAddProjectDlg::~CAddProjectDlg()
{
}

void CAddProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_edit_title);
	DDX_Text(pDX, IDC_EDIT7, m_edit_teacher);
	DDX_Text(pDX, IDC_EDIT5, m_edit_number);
	DDX_Text(pDX, IDC_EDIT8, m_edit_authors);
	DDX_Text(pDX, IDC_EDIT1, m_edit_id);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_date_begin);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_date_end);
}


BEGIN_MESSAGE_MAP(CAddProjectDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON7, &CAddProjectDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CAddProjectDlg 消息处理程序


void CAddProjectDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CInfoFile file;
	file.ReadAllInfo();
	//获取ID对应的学生
	Student* pStu = file.FindStudentByID(_ttoi(m_edit_id));
	if (pStu == NULL)
	{
		MessageBox(TEXT("学生不存在，请重新输入"));
		return;
	}
	//获取项目对象
	Project* Project = &pStu->project[pStu->projectNum];
	pStu->projectNum++;
	//获取编辑框内容
	Project->id = _ttoi(m_edit_id);
	strcpy(Project->title, CT2A(m_edit_title));
	strcpy(Project->member[0], CT2A(m_edit_teacher));
	Project->projectID = _ttoi(m_edit_number);
	//获取日期
	CTime time;
	m_date_begin.GetTime(time);
	Project->startDate.year = time.GetYear();
	Project->startDate.month = time.GetMonth();
	Project->startDate.day = time.GetDay();
	m_date_end.GetTime(time);
	Project->endDate.year = time.GetYear();
	Project->endDate.month = time.GetMonth();
	Project->endDate.day = time.GetDay();
	//获取项目成员
	CString authors = m_edit_authors;
	int curPos = 0;
	int i = 1;
	while (true)
	{
		int pos = authors.Find(_T(','), curPos);
		if (pos == -1)
		{
			CString author = authors.Mid(curPos);
			strcpy(Project->member[i], CT2A(author));
			break;
		}
		CString author = authors.Mid(curPos, pos - curPos);
		strcpy(Project->member[i], CT2A(author));
		curPos = pos + 1;
		i++;
	}
	//保存
	file.WriteAllInfo();
	MessageBox(TEXT("添加成功"));
	CDialogEx::OnOK();
}


void CAddProjectDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CAddProjectDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}
