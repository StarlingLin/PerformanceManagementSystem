// CProjectManageDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "CProjectManageDlg.h"
#include "InfoFile.h"
#include "CAddProjectDlg.h"


// CProjectManageDlg

IMPLEMENT_DYNCREATE(CProjectManageDlg, CFormView)

CProjectManageDlg::CProjectManageDlg()
	: CFormView(IDD_CProjectManageDlg)
	, m_edit_id(_T(""))
	, m_edit_name(_T(""))
	, m_edit_gender(_T(""))
	, m_edit_title(_T(""))
	, m_edit_teacher(_T(""))
	, m_edit_number(_T(""))
	, m_edit_authors(_T(""))
{

}

CProjectManageDlg::~CProjectManageDlg()
{
}

void CProjectManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit_id);
	DDX_Text(pDX, IDC_EDIT2, m_edit_name);
	DDX_Text(pDX, IDC_EDIT4, m_edit_gender);
	DDX_Text(pDX, IDC_EDIT3, m_edit_title);
	DDX_Text(pDX, IDC_EDIT7, m_edit_teacher);
	DDX_Text(pDX, IDC_EDIT5, m_edit_number);
	DDX_Text(pDX, IDC_EDIT8, m_edit_authors);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_date_begin);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_date_end);
	DDX_Control(pDX, IDC_BUTTON4, m_btn_find);
	DDX_Control(pDX, IDC_BUTTON7, m_btn_modify);
	DDX_Control(pDX, IDC_BUTTON1, m_btn_add);
	DDX_Control(pDX, IDC_BUTTON6, m_btn_del);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CProjectManageDlg, CFormView)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CProjectManageDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON4, &CProjectManageDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_CHECK3, &CProjectManageDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_BUTTON7, &CProjectManageDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON6, &CProjectManageDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON1, &CProjectManageDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CProjectManageDlg 诊断

#ifdef _DEBUG
void CProjectManageDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CProjectManageDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CProjectManageDlg 消息处理程序


void CProjectManageDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, _T("项目编号"), LVCFMT_LEFT, 110);
	m_list.InsertColumn(1, _T("项目名称"), LVCFMT_LEFT, 200);
	m_list.InsertColumn(2, _T("开始日期"), LVCFMT_LEFT, 150);
	m_list.InsertColumn(3, _T("结束日期"), LVCFMT_LEFT, 150);
	m_list.InsertColumn(4, _T("指导教师"), LVCFMT_LEFT, 110);
	m_list.InsertColumn(5, _T("项目成员"), LVCFMT_LEFT, 500);
}


void CProjectManageDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	UpdateData(TRUE);
	POSITION pos = m_list.GetFirstSelectedItemPosition();	//貌似已修复？//bug: 第二次时不能获取到选中的行
	if (pos == NULL)
	{
		return;
	}
	//int nItem = m_list.GetSelectedColumn();
	int nItem = m_list.GetNextSelectedItem(pos);
	m_edit_number = m_list.GetItemText(nItem, 0);
	m_edit_title = m_list.GetItemText(nItem, 1);
	m_edit_teacher = m_list.GetItemText(nItem, 4);
	m_edit_authors = m_list.GetItemText(nItem, 5);
	/////////////////date
	CString date = m_list.GetItemText(nItem, 2);
	int year, month, day;
	_stscanf_s(date, _T("%d-%d-%d"), &year, &month, &day);
	CTime time(year, month, day, 0, 0, 0);
	m_date_begin.SetTime(&time);
	date = m_list.GetItemText(nItem, 3);
	_stscanf_s(date, _T("%d-%d-%d"), &year, &month, &day);
	time = CTime(year, month, day, 0, 0, 0);
	m_date_end.SetTime(&time);
	UpdateData(FALSE);
}


void CProjectManageDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CInfoFile file;
	file.ReadAllInfo();
	Student* stu = file.FindStudentByID(_ttoi(m_edit_id));
	if (stu == NULL)
	{
		MessageBox(_T("学号不存在"), _T("提示"));
		return;
	}
	m_edit_name = stu->name;
	m_edit_gender = stu->gender;
	UpdateData(FALSE);

	m_list.DeleteAllItems();
	for (int i = 0; i < stu->projectNum; i++)
	{
		Project* project = stu->project + i;
		m_list.InsertItem(i, to_wstring(project->projectID).c_str());
		m_list.SetItemText(i, 1, CString(project->title));
		CString date;
		date.Format(_T("%d-%d-%d"), project->startDate.year, project->startDate.month, project->startDate.day);
		m_list.SetItemText(i, 2, date);
		date.Format(_T("%d-%d-%d"), project->endDate.year, project->endDate.month, project->endDate.day);
		m_list.SetItemText(i, 3, date);
		m_list.SetItemText(i, 4, CString(project->member[0]));
		CString members;
		bool first = true;
		for (int j = 1; strcmp(project->member[j], "") != 0; j++)
		{
			if (!first)
			{
				members += _T("、");
			}
			else
			{
				first = false;
			}
			members += project->member[j];
		}
		m_list.SetItemText(i, 5, members);
	}
}


void CProjectManageDlg::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck())
	{
		m_btn_find.EnableWindow(FALSE);
		m_btn_modify.EnableWindow(TRUE);
		m_btn_add.EnableWindow(FALSE);
		m_btn_del.EnableWindow(FALSE);
		m_list.EnableWindow(FALSE);
		m_date_begin.EnableWindow(TRUE);
		m_date_end.EnableWindow(TRUE);
		//只读IDC_EDIT1
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
		pEdit->SetReadOnly(TRUE);
		//只读IDC_EDIT2
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT2);
		pEdit->SetReadOnly(TRUE);
		//只读IDC_EDIT4
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT4);
		pEdit->SetReadOnly(TRUE);
		//可读IDC_EDIT3
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT3);
		pEdit->SetReadOnly(FALSE);
		//可读IDC_EDIT7
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT7);
		pEdit->SetReadOnly(FALSE);
		//可读IDC_EDIT5
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT5);
		pEdit->SetReadOnly(FALSE);
		//可读IDC_EDIT8
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT8);
		pEdit->SetReadOnly(FALSE);
	}
	else
	{
		m_btn_find.EnableWindow(TRUE);
		m_btn_modify.EnableWindow(FALSE);
		m_btn_add.EnableWindow(TRUE);
		m_btn_del.EnableWindow(TRUE);
		m_list.EnableWindow(TRUE);
		m_date_begin.EnableWindow(FALSE);
		m_date_end.EnableWindow(FALSE);
		//可读IDC_EDIT1
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
		pEdit->SetReadOnly(FALSE);
		//只读IDC_EDIT2
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT2);
		pEdit->SetReadOnly(TRUE);
		//只读IDC_EDIT4
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT4);
		pEdit->SetReadOnly(TRUE);
		//只读IDC_EDIT3
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT3);
		pEdit->SetReadOnly(TRUE);
		//只读IDC_EDIT7
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT7);
		pEdit->SetReadOnly(TRUE);
		//只读IDC_EDIT5
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT5);
		pEdit->SetReadOnly(TRUE);
		//只读IDC_EDIT8
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT8);
		pEdit->SetReadOnly(TRUE);
	}
}


void CProjectManageDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CInfoFile file;
	file.ReadAllInfo();
	Student* stu = file.FindStudentByID(_ttoi(m_edit_id));
	if (stu == NULL)
	{
		MessageBox(_T("学号不存在"), _T("提示"));
		return;
	}
	Project* project = NULL;
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请选择一个项目"), _T("提示"));
		return;
	}
	int nItem = m_list.GetNextSelectedItem(pos);
	CString id0 = m_list.GetItemText(nItem, 0);
	for (int i = 0; i < stu->projectNum; i++)
	{
		if (stu->project[i].projectID == _ttoi(id0))
		{
			project = stu->project + i;
			break;
		}
	}
	if (project == NULL)
	{
		MessageBox(_T("项目不存在"), _T("提示"));
		return;
	}
	//修改
	//项目编号
	project->projectID = _ttoi(m_edit_number);
	//项目名称
	strcpy_s(project->title, CT2A(m_edit_title.GetBuffer()));
	//开始日期
	CTime time;
	m_date_begin.GetTime(time);
	project->startDate.year = time.GetYear();
	project->startDate.month = time.GetMonth();
	project->startDate.day = time.GetDay();
	//结束日期
	m_date_end.GetTime(time);
	project->endDate.year = time.GetYear();
	project->endDate.month = time.GetMonth();
	project->endDate.day = time.GetDay();
	//指导教师
	strcpy_s(project->member[0], CT2A(m_edit_teacher.GetBuffer()));
	//项目成员
	/*先清空*/
	for (int i = 1; i < MEMBER_MAX; i++)
	{
		strcpy_s(project->member[i], "");
	}
	CString authors = m_edit_authors;
	int i = 1;
	int curPos = 0;
	while (true)
	{
		int pos = authors.Find(_T("、"), curPos);
		if (pos == -1)
		{
			strcpy_s(project->member[i], CT2A(authors.Mid(curPos)));
			break;
		}
		strcpy_s(project->member[i], CT2A(authors.Mid(curPos, pos - curPos)));
		curPos = pos + 1;
		i++;
	}
	//保存
	file.WriteAllInfo();
	MessageBox(_T("修改成功"), _T("提示"));
	OnBnClickedButton4();
}


void CProjectManageDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CInfoFile file;
	file.ReadAllInfo();
	Student* stu = file.FindStudentByID(_ttoi(m_edit_id));
	if (stu == NULL)
	{
		MessageBox(_T("学号不存在"), _T("提示"));
		return;
	}
	Project* project = NULL;
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请选择一个项目"), _T("提示"));
		return;
	}
	int nItem = m_list.GetNextSelectedItem(pos);
	CString id0 = m_list.GetItemText(nItem, 0);
	for (int i = 0; i < stu->projectNum; i++)
	{
		if (stu->project[i].projectID == _ttoi(id0))
		{
			project = stu->project + i;
			break;
		}
	}
	if (project == NULL)
	{
		MessageBox(_T("项目不存在"), _T("提示"));
		return;
	}
	//删除
	for (int i = 0; i < stu->projectNum; i++)
	{
		if (stu->project + i == project)
		{
			for (int j = i; j < stu->projectNum - 1; j++)
			{
				stu->project[j] = stu->project[j + 1];
			}
			stu->projectNum--;
			break;
		}
	}
	//保存
	file.WriteAllInfo();
	MessageBox(_T("删除成功"), _T("提示"));
	OnBnClickedButton4();
}


void CProjectManageDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CAddProjectDlg dlg;
	dlg.DoModal();
	OnBnClickedButton4();
}
