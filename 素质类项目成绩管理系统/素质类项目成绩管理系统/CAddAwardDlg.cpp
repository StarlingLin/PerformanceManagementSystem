// CAddAwardDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "afxdialogex.h"
#include "CAddAwardDlg.h"
#include "InfoFile.h"


// CAddAwardDlg 对话框

IMPLEMENT_DYNAMIC(CAddAwardDlg, CDialogEx)

CAddAwardDlg::CAddAwardDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDAWARD, pParent)
	, m_edit_title(_T(""))
	, m_edit_organization(_T(""))
	, m_edit_level(_T(""))
	//, m_date(COleDateTime::GetCurrentTime())
	, m_edit_teacher(_T(""))
	, m_edit_members(_T(""))
	, m_edit_id(_T(""))
{

}

CAddAwardDlg::~CAddAwardDlg()
{
}

void CAddAwardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_edit_title);
	DDX_Text(pDX, IDC_EDIT7, m_edit_organization);
	DDX_Text(pDX, IDC_EDIT5, m_edit_level);
	//  DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_date);
	DDX_Text(pDX, IDC_EDIT9, m_edit_teacher);
	DDX_Text(pDX, IDC_EDIT8, m_edit_members);
	DDX_Text(pDX, IDC_EDIT1, m_edit_id);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_date);
}


BEGIN_MESSAGE_MAP(CAddAwardDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON7, &CAddAwardDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CAddAwardDlg 消息处理程序


void CAddAwardDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CInfoFile file;
	file.ReadAllInfo();
	//获取ID对应的学生
	Student* pStu = file.FindStudentByID(_ttoi(m_edit_id));
	if (pStu == NULL)
	{
		MessageBox(TEXT("学号不存在"), TEXT("提示"));
		return;
	}
	//获取奖项对象
	Award* award = &pStu->award[pStu->awardNum];
	pStu->awardNum++;
	//获取编辑框内容
	award->id = _ttoi(m_edit_id);
	strcpy(award->title, CT2A(m_edit_title));
	strcpy(award->organization, CT2A(m_edit_organization));
	strcpy(award->level, CT2A(m_edit_level));
	strcpy(award->member[0], CT2A(m_edit_teacher));
	CTime time;
	m_date.GetTime(time);
	award->awardDate.year = time.GetYear();
	award->awardDate.month = time.GetMonth();
	award->awardDate.day = time.GetDay();
	//获取成员
	CString members = m_edit_members;
	int curPos = 0;
	int j = 1;
	while (true)
	{
		int Pos = members.Find(_T('、'), curPos);
		if (Pos == -1)
		{
			strcpy(award->member[j], CT2A(members.Mid(curPos)));
			break;
		}
		strcpy(award->member[j], CT2A(members.Mid(curPos, Pos - curPos)));
		curPos = Pos + 1;
		j++;
	}
	file.WriteAllInfo();
	MessageBox(TEXT("添加成功"), TEXT("提示"));
	CDialogEx::OnOK();
}


void CAddAwardDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}
