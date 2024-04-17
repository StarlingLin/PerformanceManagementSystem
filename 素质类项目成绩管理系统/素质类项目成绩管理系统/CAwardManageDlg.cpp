// CAwardManageDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "CAwardManageDlg.h"
#include "InfoFile.h"
#include "CAddAwardDlg.h"


// CAwardManageDlg

IMPLEMENT_DYNCREATE(CAwardManageDlg, CFormView)

CAwardManageDlg::CAwardManageDlg()
	: CFormView(IDD_CAwardManageDlg)
	, m_edit_id(_T(""))
	, m_edit_name(_T(""))
	, m_edit_gender(_T(""))
	, m_edit_title(_T(""))
	, m_edit_organization(_T(""))
	, m_edit_grade(_T(""))
	, m_edit_teacher(_T(""))
	, m_edit_members(_T(""))
{

}

CAwardManageDlg::~CAwardManageDlg()
{
}

void CAwardManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit_id);
	DDX_Text(pDX, IDC_EDIT2, m_edit_name);
	DDX_Text(pDX, IDC_EDIT4, m_edit_gender);
	DDX_Text(pDX, IDC_EDIT3, m_edit_title);
	DDX_Text(pDX, IDC_EDIT7, m_edit_organization);
	DDX_Text(pDX, IDC_EDIT5, m_edit_grade);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_date);
	DDX_Text(pDX, IDC_EDIT9, m_edit_teacher);
	DDX_Text(pDX, IDC_EDIT8, m_edit_members);
	DDX_Control(pDX, IDC_BUTTON4, m_btn_find);
	DDX_Control(pDX, IDC_BUTTON7, m_btn_modify);
	DDX_Control(pDX, IDC_BUTTON1, m_btn_add);
	DDX_Control(pDX, IDC_BUTTON6, m_btn_del);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CAwardManageDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON4, &CAwardManageDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_CHECK3, &CAwardManageDlg::OnBnClickedCheck3)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CAwardManageDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON7, &CAwardManageDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON6, &CAwardManageDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON1, &CAwardManageDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAwardManageDlg 诊断

#ifdef _DEBUG
void CAwardManageDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAwardManageDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAwardManageDlg 消息处理程序


void CAwardManageDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, _T("奖项名"), LVCFMT_LEFT, 200);
	m_list.InsertColumn(1, _T("颁奖组织"), LVCFMT_LEFT, 200);
	m_list.InsertColumn(2, _T("获奖日期"), LVCFMT_LEFT, 150);
	m_list.InsertColumn(3, _T("获奖级别"), LVCFMT_LEFT, 110);
	m_list.InsertColumn(4, _T("指导教师"), LVCFMT_LEFT, 110);
	m_list.InsertColumn(5, _T("获奖成员"), LVCFMT_LEFT, 500);
}


void CAwardManageDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CInfoFile file;
	file.ReadAllInfo();
	Student* pStu = file.FindStudentByID(_ttoi(m_edit_id));
	if (pStu == NULL)
	{
		MessageBox(_T("学号不存在"), _T("提示"));
		return;
	}
	m_edit_name = pStu->name;
	m_edit_gender = pStu->gender;
	UpdateData(FALSE);

	m_list.DeleteAllItems();
	for (int i = 0; i < pStu->awardNum; i++)
	{
		Award* pAward = &pStu->award[i];
		m_list.InsertItem(i, CString(pAward->title));
		m_list.SetItemText(i, 1, CString(pAward->organization));
		CString str;
		str.Format(_T("%d-%d-%d"), pAward->awardDate.year, pAward->awardDate.month, pAward->awardDate.day);
		m_list.SetItemText(i, 2, str);
		m_list.SetItemText(i, 3, CString(pAward->level));
		m_list.SetItemText(i, 4, CString(pAward->member[0]));
		CString members;
		bool first = true;
		for (int j = 1; strcmp(pAward->member[j], "") != 0; j++)
		{
			if (!first)
			{
				members += _T("、");
			}
			else
			{
				first = false;
			}
			members += pAward->member[j];
		}
		m_list.SetItemText(i, 5, members);
	}
}


void CAwardManageDlg::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck())
	{
		m_btn_find.EnableWindow(FALSE);
		m_btn_modify.EnableWindow(TRUE);
		m_btn_add.EnableWindow(FALSE);
		m_btn_del.EnableWindow(FALSE);
		m_list.EnableWindow(FALSE);
		m_date.EnableWindow(TRUE);
		//只读IDC_EDIT1
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
		pEdit->SetReadOnly(TRUE);
		//可读IDC_EDIT3
		CEdit* pEdit3 = (CEdit*)GetDlgItem(IDC_EDIT3);
		pEdit3->SetReadOnly(FALSE);
		//可读IDC_EDIT7
		CEdit* pEdit7 = (CEdit*)GetDlgItem(IDC_EDIT7);
		pEdit7->SetReadOnly(FALSE);
		//可读IDC_EDIT5
		CEdit* pEdit5 = (CEdit*)GetDlgItem(IDC_EDIT5);
		pEdit5->SetReadOnly(FALSE);
		//可读IDC_EDIT9
		CEdit* pEdit9 = (CEdit*)GetDlgItem(IDC_EDIT9);
		pEdit9->SetReadOnly(FALSE);
		//可读IDC_EDIT8
		CEdit* pEdit8 = (CEdit*)GetDlgItem(IDC_EDIT8);
		pEdit8->SetReadOnly(FALSE);
	}
	else
	{
		m_btn_find.EnableWindow(TRUE);
		m_btn_modify.EnableWindow(FALSE);
		m_btn_add.EnableWindow(TRUE);
		m_btn_del.EnableWindow(TRUE);
		m_list.EnableWindow(TRUE);
		m_date.EnableWindow(FALSE);
		//可读IDC_EDIT1
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
		pEdit->SetReadOnly(FALSE);
		//只读IDC_EDIT3
		CEdit* pEdit3 = (CEdit*)GetDlgItem(IDC_EDIT3);
		pEdit3->SetReadOnly(TRUE);
		//只读IDC_EDIT7
		CEdit* pEdit7 = (CEdit*)GetDlgItem(IDC_EDIT7);
		pEdit7->SetReadOnly(TRUE);
		//只读IDC_EDIT5
		CEdit* pEdit5 = (CEdit*)GetDlgItem(IDC_EDIT5);
		pEdit5->SetReadOnly(TRUE);
		//只读IDC_EDIT9
		CEdit* pEdit9 = (CEdit*)GetDlgItem(IDC_EDIT9);
		pEdit9->SetReadOnly(TRUE);
		//只读IDC_EDIT8
		CEdit* pEdit8 = (CEdit*)GetDlgItem(IDC_EDIT8);
		pEdit8->SetReadOnly(TRUE);
	}
}


void CAwardManageDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	UpdateData(TRUE);
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		return;
	}
	int nItem = m_list.GetNextSelectedItem(pos);
	m_edit_title = m_list.GetItemText(nItem, 0);
	m_edit_organization = m_list.GetItemText(nItem, 1);
	m_edit_grade = m_list.GetItemText(nItem, 3);
	m_edit_teacher = m_list.GetItemText(nItem, 4);
	m_edit_members = m_list.GetItemText(nItem, 5);
	CString strDate = m_list.GetItemText(nItem, 2);
	int year, month, day;
	_stscanf_s(strDate, _T("%d-%d-%d"), &year, &month, &day);
	CTime time(year, month, day, 0, 0, 0);
	m_date.SetTime(&time);
	UpdateData(FALSE);
}


void CAwardManageDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CInfoFile file;
	file.ReadAllInfo();
	Student* pStu = file.FindStudentByID(_ttoi(m_edit_id));
	if (pStu == NULL)
	{
		MessageBox(_T("学号不存在"), _T("提示"));
		return;
	}
	Award* award = NULL;
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请选择一个奖项"), _T("提示"));
		return;
	}
	int nItem = m_list.GetNextSelectedItem(pos);
	CString title0 = m_list.GetItemText(nItem, 0);
	for (int i = 0; i < pStu->awardNum; i++)
	{
		Award* pAward = &pStu->award[i];
		if (title0 == pAward->title)
		{
			award = pAward;
			break;
		}
	}
	if (award == NULL)
	{
		MessageBox(_T("奖项不存在"), _T("提示"));
		return;
	}
	strcpy_s(award->title, CT2A(m_edit_title));
	strcpy_s(award->organization, CT2A(m_edit_organization));
	CTime time;
	m_date.GetTime(time);
	award->awardDate.year = time.GetYear();
	award->awardDate.month = time.GetMonth();
	award->awardDate.day = time.GetDay();
	strcpy_s(award->level, CT2A(m_edit_grade));
	strcpy_s(award->member[0], CT2A(m_edit_teacher));
	for (int i = 1; i < MEMBER_MAX; i++)
	{
		strcpy_s(award->member[i], "");
	}
	CString members = m_edit_members;
	int curPos = 0;
	int j = 1;
	while (true)
	{
		int Pos = members.Find(_T('、'), curPos);
		if (Pos == -1)
		{
			strcpy_s(award->member[j], CT2A(members.Mid(curPos)));
			break;
		}
		strcpy_s(award->member[j], CT2A(members.Mid(curPos, Pos - curPos)));
		curPos = Pos + 1;
		j++;
	}

	file.WriteAllInfo();
	MessageBox(_T("修改成功"), _T("提示"));
	OnBnClickedButton4();
}


void CAwardManageDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CInfoFile file;
	file.ReadAllInfo();
	Student* pStu = file.FindStudentByID(_ttoi(m_edit_id));
	if (pStu == NULL)
	{
		MessageBox(_T("学号不存在"), _T("提示"));
		return;
	}
	Award* award = NULL;
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请选择一个奖项"), _T("提示"));
		return;
	}
	int nItem = m_list.GetNextSelectedItem(pos);
	CString title0 = m_list.GetItemText(nItem, 0);
	for (int i = 0; i < pStu->awardNum; i++)
	{
		Award* pAward = &pStu->award[i];
		if (title0 == pAward->title)
		{
			award = pAward;
			break;
		}
	}
	//判断是否存在
	if (award == NULL)
	{
		MessageBox(_T("奖项不存在"), _T("提示"));
		return;
	}
	//删除
	for (int i = 0; i < pStu->awardNum; i++)
	{
		if (pStu->award + i == award)
		{
			for (int j = i; j < pStu->awardNum - 1; j++)
			{
				pStu->award[j] = pStu->award[j + 1];
			}
			break;
		}
	}
	pStu->awardNum--;
	//保存
	file.WriteAllInfo();
	MessageBox(_T("删除成功"), _T("提示"));
	OnBnClickedButton4();
}


void CAwardManageDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CAddAwardDlg dlg;
	dlg.DoModal();
	OnBnClickedButton4();
}
