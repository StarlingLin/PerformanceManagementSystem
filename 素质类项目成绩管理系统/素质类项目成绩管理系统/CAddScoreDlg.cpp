// CAddScoreDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "afxdialogex.h"
#include "CAddScoreDlg.h"
#include "InfoFile.h"


// CAddScoreDlg 对话框

IMPLEMENT_DYNAMIC(CAddScoreDlg, CDialogEx)

CAddScoreDlg::CAddScoreDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDSCORE, pParent)
	, m_edit_id(_T(""))
	//, m(_T(""))
	, m_edit_subject(_T(""))
	, m_edit_score(_T(""))
{

}

CAddScoreDlg::~CAddScoreDlg()
{
}

void CAddScoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit_id);
	//  DDX_Control(pDX, IDC_EDIT2, m_edit_subject);
	//  DDX_Text(pDX, IDC_EDIT4, m);
	DDX_Text(pDX, IDC_EDIT2, m_edit_subject);
	DDX_Text(pDX, IDC_EDIT4, m_edit_score);
}


BEGIN_MESSAGE_MAP(CAddScoreDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON4, &CAddScoreDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CAddScoreDlg 消息处理程序


void CAddScoreDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CAddScoreDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_edit_id.IsEmpty() || m_edit_subject.IsEmpty() || m_edit_score.IsEmpty())
	{
		MessageBox(_T("请填写完整信息"));
		return;
	}
	//判断学号是否存在
	CInfoFile file;
	file.ReadAllInfo();
	if (!file.IsIDExist(_ttoi(m_edit_id)))
	{
		MessageBox(_T("学号不存在"), _T("提示"));
		return;
	}
	//判断科目是否已经存在
	Student* stu = file.FindStudentByID(_ttoi(m_edit_id));
	Score* sc = stu->score;
	for (int i = 0; i < stu->scoreNum; i++)
	{
		if (sc[i].subject == m_edit_subject)
		{
			MessageBox(_T("该科目已经存在"), _T("提示"));
			return;
		}
	}
	//判断科目数量是否超过SUBJECT_MAX
	if (stu->scoreNum >= SUBJECT_MAX)
	{
		MessageBox(_T("科目数量已满"), _T("提示"));
		return;
	}
	//添加
	strcpy(stu->score[stu->scoreNum].subject, CT2A(m_edit_subject));
	stu->score[stu->scoreNum].score = _ttoi(m_edit_score);
	stu->scoreNum++;
	//保存
	file.WriteAllInfo();
	MessageBox(_T("添加成功"), _T("提示"));

	CDialogEx::OnOK();
}
