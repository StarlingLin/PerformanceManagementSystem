// CScoreManageDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "CScoreManageDlg.h"
#include "InfoFile.h"
#include "CAddScoreDlg.h"


// CScoreManageDlg

IMPLEMENT_DYNCREATE(CScoreManageDlg, CFormView)

CScoreManageDlg::CScoreManageDlg()
	: CFormView(IDD_CScoreManageDlg)
	, m_edit_id(_T(""))
	, m_edit_gender(_T(""))
	, m_edit_subject(_T(""))
	, m_edit_score(_T(""))
	, m_edit_name(_T(""))
{

}

CScoreManageDlg::~CScoreManageDlg()
{
}

void CScoreManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_score);
	//  DDX_Control(pDX, IDC_EDIT1, m_edit_id);
	//  DDX_Control(pDX, IDC_EDIT2, m_edit_name);
	DDX_Text(pDX, IDC_EDIT1, m_edit_id);
	//  DDX_Control(pDX, IDC_EDIT2, m_edit_name);
	DDX_Text(pDX, IDC_EDIT4, m_edit_gender);
	DDX_Control(pDX, IDC_BUTTON4, m_btn_find);
	DDX_Text(pDX, IDC_EDIT6, m_edit_subject);
	DDX_Text(pDX, IDC_EDIT7, m_edit_score);
	DDX_Control(pDX, IDC_CHECK2, m_chk);
	DDX_Control(pDX, IDC_BUTTON5, m_btn_modify);
	DDX_Control(pDX, IDC_BUTTON6, m_btn_del);
	DDX_Control(pDX, IDC_BUTTON7, m_btn_add);
	DDX_Text(pDX, IDC_EDIT2, m_edit_name);
}

BEGIN_MESSAGE_MAP(CScoreManageDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON4, &CScoreManageDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_CHECK2, &CScoreManageDlg::OnBnClickedCheck2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CScoreManageDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON5, &CScoreManageDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CScoreManageDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CScoreManageDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CScoreManageDlg 诊断

#ifdef _DEBUG
void CScoreManageDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CScoreManageDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CScoreManageDlg 消息处理程序


void CScoreManageDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_list_score.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list_score.InsertColumn(0, _T("学号"), LVCFMT_LEFT, 120);
	m_list_score.InsertColumn(1, _T("学科"), LVCFMT_LEFT, 200);
	m_list_score.InsertColumn(2, _T("成绩"), LVCFMT_LEFT, 100);
}


void CScoreManageDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取学号
	UpdateData(TRUE);
	//判断是否为空
	if (m_edit_id.IsEmpty())
	{
		MessageBox(_T("请输入学号"), _T("提示"));
		return;
	}
	//读取文件
	CInfoFile file;
	file.ReadAllInfo();
	//判断学号是否存在
	if (!file.IsIDExist(_ttoi(m_edit_id)))
	{
		MessageBox(_T("学号不存在"), _T("提示"));
		return;
	}
	//获取学生信息
	Student* stu = file.FindStudentByID(_ttoi(m_edit_id));
	//显示学生信息
	m_edit_name = CString(stu->name);
	m_edit_gender = CString(stu->gender);
	//显示学生成绩
	m_list_score.DeleteAllItems();
	for (int i = 0; i < stu->scoreNum; i++)
	{
		m_list_score.InsertItem(i, _T(""));
		m_list_score.SetItemText(i, 0, m_edit_id);
		m_list_score.SetItemText(i, 1, CString(stu->score[i].subject));
		m_list_score.SetItemText(i, 2, CString(to_string(stu->score[i].score).c_str()));
	}
	UpdateData(FALSE);
}


void CScoreManageDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_chk.GetCheck())
	{
		m_btn_add.EnableWindow(FALSE);
		m_btn_del.EnableWindow(FALSE);
		m_btn_modify.EnableWindow(TRUE);
		m_btn_find.EnableWindow(FALSE);
		m_list_score.EnableWindow(FALSE);
		//只读IDC_EDIT1
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
		pEdit->SetReadOnly(TRUE);
		//可读IDC_EDIT6
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT6);
		pEdit->SetReadOnly(FALSE);
		//可读IDC_EDIT7
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT7);
		pEdit->SetReadOnly(FALSE);
	}
	else
	{
		m_btn_add.EnableWindow(TRUE);
		m_btn_del.EnableWindow(TRUE);
		m_btn_modify.EnableWindow(FALSE);
		m_btn_find.EnableWindow(TRUE);
		m_list_score.EnableWindow(TRUE);
		//可读IDC_EDIT1
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
		pEdit->SetReadOnly(FALSE);
		//只读IDC_EDIT6
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT6);
		pEdit->SetReadOnly(TRUE);
		//只读IDC_EDIT7
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT7);
		pEdit->SetReadOnly(TRUE);
	}
}


void CScoreManageDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	//获取选中的行
	POSITION pos = m_list_score.GetFirstSelectedItemPosition();
	int nItem = m_list_score.GetNextSelectedItem(pos);
	CString id = m_list_score.GetItemText(nItem, 0);
	CString subject = m_list_score.GetItemText(nItem, 1);
	CString score = m_list_score.GetItemText(nItem, 2);
	m_edit_score = score;
	m_edit_subject = subject;
	UpdateData(FALSE);
}


void CScoreManageDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//判断是否选中
	POSITION pos = m_list_score.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请选中要修改的学科成绩！"), _T("提示"));
		return;
	}
	int nItem = m_list_score.GetNextSelectedItem(pos);
	//判断是否为空
	if (m_edit_score.IsEmpty() || m_edit_subject.IsEmpty())
	{
		MessageBox(_T("请填写完整信息！"), _T("提示"));
		return;
	}
	//获取学号与学科
	CString id = m_list_score.GetItemText(nItem, 0);
	CString subject = m_list_score.GetItemText(nItem, 1);
	//文件
	CInfoFile file;
	file.ReadAllInfo();
	//获取学生信息
	Student* stu = file.FindStudentByID(_ttoi(id));
	//修改成绩与学科
	for (int i = 0; i < stu->scoreNum; i++)
	{
		if (stu->score[i].subject == subject)
		{
			stu->score[i].score = _ttoi(m_edit_score);
			strcpy(stu->score[i].subject, CT2A(m_edit_subject));
			break;
		}
	}
	//保存
	file.WriteAllInfo();
	//提示
	MessageBox(_T("修改成功！"), _T("提示"));
	//清空
	m_edit_score.Empty();
	m_edit_subject.Empty();
	UpdateData(FALSE);

	OnBnClickedButton4();
}


void CScoreManageDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取学号与学科（选中的行）
	POSITION pos = m_list_score.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请选中要删除的学科成绩！"), _T("提示"));
		return;
	}
	int nItem = m_list_score.GetNextSelectedItem(pos);
	CString id = m_list_score.GetItemText(nItem, 0);
	CString subject = m_list_score.GetItemText(nItem, 1);
	//文件
	CInfoFile file;
	file.ReadAllInfo();
	//获取学生信息
	Student* stu = file.FindStudentByID(_ttoi(id));
	//删除学科成绩
	for (int i = 0; i < stu->scoreNum; i++)
	{
		if (stu->score[i].subject == subject)
		{
			for (int j = i; j < stu->scoreNum - 1; j++)
			{
				stu->score[j] = stu->score[j + 1];
			}
			stu->scoreNum--;
			break;
		}
	}
	//保存
	file.WriteAllInfo();
	//提示
	MessageBox(_T("删除成功！"), _T("提示"));
	//更新
	OnBnClickedButton4();
}


void CScoreManageDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	CAddScoreDlg dlg;
	dlg.DoModal();
	OnBnClickedButton4();
}
