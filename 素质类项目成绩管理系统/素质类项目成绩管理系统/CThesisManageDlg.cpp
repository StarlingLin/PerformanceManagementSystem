// CThesisManageDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "CThesisManageDlg.h"
#include "InfoFile.h"
#include "CAddThesisDlg.h"


// CThesisManageDlg

IMPLEMENT_DYNCREATE(CThesisManageDlg, CFormView)

CThesisManageDlg::CThesisManageDlg()
	: CFormView(IDD_CThesisManageDlg)
	, m_edit_id(_T(""))
	, m_edit_name(_T(""))
	, m_edit_gender(_T(""))
	, m_edit_title(_T(""))
	, m_edit_periodical(_T(""))
	, m_edit_pagination(_T(""))
	, m_edit_author0(_T(""))
	, m_edit_author(_T(""))
{

}

CThesisManageDlg::~CThesisManageDlg()
{
}

void CThesisManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit_id);
	DDX_Text(pDX, IDC_EDIT2, m_edit_name);
	DDX_Text(pDX, IDC_EDIT4, m_edit_gender);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT3, m_edit_title);
	DDX_Text(pDX, IDC_EDIT5, m_edit_periodical);
	DDX_Text(pDX, IDC_EDIT6, m_edit_pagination);
	DDX_Text(pDX, IDC_EDIT7, m_edit_author0);
	DDX_Text(pDX, IDC_EDIT8, m_edit_author);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_date);
	DDX_Control(pDX, IDC_COMBO1, m_cbx);
	DDX_Control(pDX, IDC_BUTTON4, m_btn_find);
	DDX_Control(pDX, IDC_BUTTON1, m_btn_add);
	DDX_Control(pDX, IDC_BUTTON7, m_btn_modify);
	DDX_Control(pDX, IDC_BUTTON6, m_btn_del);
}

BEGIN_MESSAGE_MAP(CThesisManageDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON4, &CThesisManageDlg::OnBnClickedButton4)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CThesisManageDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_CHECK3, &CThesisManageDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_BUTTON7, &CThesisManageDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON6, &CThesisManageDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON1, &CThesisManageDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CThesisManageDlg 诊断

#ifdef _DEBUG
void CThesisManageDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CThesisManageDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CThesisManageDlg 消息处理程序


void CThesisManageDlg::OnBnClickedButton4()
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
	for (int i = 0; i < stu->thesisNum; i++)
	{
		Thesis* thesis = stu->thesis + i;
		m_list.InsertItem(i, CString(thesis->title));
		m_list.SetItemText(i, 1, CString(thesis->periodical));
		m_list.SetItemText(i, 2, CString(thesis->pagination));
		CString date;
		date.Format(_T("%d-%d-%d"), thesis->publishDate.year, thesis->publishDate.month, thesis->publishDate.day);
		m_list.SetItemText(i, 3, date);
		m_list.SetItemText(i, 4, CString(thesis->grade));
		m_list.SetItemText(i, 5, CString(thesis->author[0]));
		CString authors;
		bool first = true;
		for (int j = 1; strcmp(thesis->author[j], "") != 0; j++)
		{
			if (!first)
			{
				authors += _T("、");
			}
			else
			{
				first = false;
			}
			authors += thesis->author[j];
		}
		m_list.SetItemText(i, 6, authors);
	}
}


void CThesisManageDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, _T("标题"), LVCFMT_LEFT, 200);
	m_list.InsertColumn(1, _T("期刊"), LVCFMT_LEFT, 120);
	m_list.InsertColumn(2, _T("页码"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(3, _T("发表时间"), LVCFMT_LEFT, 150);
	m_list.InsertColumn(4, _T("级别"), LVCFMT_LEFT, 70);
	m_list.InsertColumn(5, _T("通讯作者"), LVCFMT_LEFT, 110);
	m_list.InsertColumn(6, _T("作者"), LVCFMT_LEFT, 500);
}


void CThesisManageDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
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
	m_edit_title = m_list.GetItemText(nItem, 0);
	m_edit_periodical = m_list.GetItemText(nItem, 1);
	m_edit_pagination = m_list.GetItemText(nItem, 2);
	/////////////////date
	CString date = m_list.GetItemText(nItem, 3);
	CString resToken;
	int curPos = 0;
	SYSTEMTIME sysTime;
	memset(&sysTime, 0, sizeof(sysTime));
	sysTime.wYear = _ttoi(date.Tokenize(_T("-"), curPos));
	sysTime.wMonth = _ttoi(date.Tokenize(_T("-"), curPos));
	sysTime.wDay = _ttoi(date.Tokenize(_T(""), curPos));
	m_date.SetTime(sysTime);
	/////////////////
	CString grade = m_list.GetItemText(nItem, 4);
	if (grade == _T("T"))
	{
		m_cbx.SetCurSel(0);
	}
	else if (grade == _T("A"))
	{
		m_cbx.SetCurSel(1);
	}
	else if (grade == _T("B"))
	{
		m_cbx.SetCurSel(2);
	}
	else if (grade == _T("C"))
	{
		m_cbx.SetCurSel(3);
	}
	else if (grade == _T("D"))
	{
		m_cbx.SetCurSel(4);
	}
	else if (grade == _T("E"))
	{
		m_cbx.SetCurSel(5);
	}
	m_edit_author0 = m_list.GetItemText(nItem, 5);
	m_edit_author = m_list.GetItemText(nItem, 6);
	UpdateData(FALSE);
}


void CThesisManageDlg::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck())
	{
		m_btn_find.EnableWindow(FALSE);
		m_btn_add.EnableWindow(FALSE);
		m_btn_modify.EnableWindow(TRUE);
		m_btn_del.EnableWindow(FALSE);
		m_list.EnableWindow(FALSE);
		m_cbx.EnableWindow(TRUE);
		m_date.EnableWindow(TRUE);
		//只读IDC_EDIT1
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
		pEdit->SetReadOnly(TRUE);
		//可读IDC_EDIT3
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT3);
		pEdit->SetReadOnly(FALSE);
		//可读IDC_EDIT5
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT5);
		pEdit->SetReadOnly(FALSE);
		//可读IDC_EDIT6
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT6);
		pEdit->SetReadOnly(FALSE);
		//可读IDC_EDIT7
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT7);
		pEdit->SetReadOnly(FALSE);
		//可读IDC_EDIT8
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT8);
		pEdit->SetReadOnly(FALSE);
	}
	else
	{
		m_btn_find.EnableWindow(TRUE);
		m_btn_add.EnableWindow(TRUE);
		m_btn_modify.EnableWindow(FALSE);
		m_btn_del.EnableWindow(TRUE);
		m_list.EnableWindow(TRUE);
		m_cbx.EnableWindow(FALSE);
		m_date.EnableWindow(FALSE);
		//可读IDC_EDIT1
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
		pEdit->SetReadOnly(FALSE);
		//只读IDC_EDIT3
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT3);
		pEdit->SetReadOnly(TRUE);
		//只读IDC_EDIT5
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT5);
		pEdit->SetReadOnly(TRUE);
		//只读IDC_EDIT6
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT6);
		pEdit->SetReadOnly(TRUE);
		//只读IDC_EDIT7
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT7);
		pEdit->SetReadOnly(TRUE);
		//只读IDC_EDIT8
		pEdit = (CEdit*)GetDlgItem(IDC_EDIT8);
		pEdit->SetReadOnly(TRUE);
	}
}


void CThesisManageDlg::OnBnClickedButton7()
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
	Thesis* thesis = NULL;
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请选择要修改的论文"), _T("提示"));
		return;
	}
	int nItem = m_list.GetNextSelectedItem(pos);
	CString title0 = m_list.GetItemText(nItem, 0);
	for (int i = 0; i < stu->thesisNum; i++)
	{
		Thesis* t = stu->thesis + i;
		if (CString(t->title) == title0)
		{
			thesis = t;
			break;
		}
	}
	if (thesis == NULL)
	{
		MessageBox(_T("论文不存在"), _T("提示"));
		return;
	}
	//级别
	int sel = m_cbx.GetCurSel();
	CString grade;
	m_cbx.GetLBText(sel, grade);
	thesis->grade = *CT2A(grade);
	//日期
	SYSTEMTIME sysTime;
	m_date.GetTime(&sysTime);
	thesis->publishDate.year = sysTime.wYear;
	thesis->publishDate.month = sysTime.wMonth;
	thesis->publishDate.day = sysTime.wDay;
	//标题
	strcpy(thesis->title, CT2A(m_edit_title));
	//期刊
	strcpy(thesis->periodical, CT2A(m_edit_periodical));
	//页码
	strcpy(thesis->pagination, CT2A(m_edit_pagination));
	//通讯作者
	strcpy(thesis->author[0], CT2A(m_edit_author0));
	//作者
	CString authors = m_edit_author;
	int curPos = 0;
	int j = 1;
	while (true)
	{
		CString author = authors.Tokenize(_T("、"), curPos);
		if (author == _T(""))
		{
			break;
		}
		strcpy(thesis->author[j++], CT2A(author));
	}
	//保存
	file.WriteAllInfo();
	MessageBox(_T("修改成功"), _T("提示"));
	OnBnClickedButton4();
}


void CThesisManageDlg::OnBnClickedButton6()
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
	Thesis* thesis = NULL;
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请选择要删除的论文"), _T("提示"));
		return;
	}
	int nItem = m_list.GetNextSelectedItem(pos);
	CString title0 = m_list.GetItemText(nItem, 0);
	for (int i = 0; i < stu->thesisNum; i++)
	{
		Thesis* t = stu->thesis + i;
		if (CString(t->title) == title0)
		{
			thesis = t;
			break;
		}
	}
	if (thesis == NULL)
	{
		MessageBox(_T("论文不存在"), _T("提示"));
		return;
	}
	//删除
	for (int i = 0; i < stu->thesisNum; i++)
	{
		if (stu->thesis + i == thesis)
		{
			for (int j = i; j < stu->thesisNum - 1; j++)
			{
				stu->thesis[j] = stu->thesis[j + 1];
			}
			break;
		}
	}
	stu->thesisNum--;
	//保存
	file.WriteAllInfo();
	MessageBox(_T("删除成功"), _T("提示"));
	OnBnClickedButton4();
}


void CThesisManageDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CAddThesisDlg dlg;
	dlg.DoModal();
	OnBnClickedButton4();
}
