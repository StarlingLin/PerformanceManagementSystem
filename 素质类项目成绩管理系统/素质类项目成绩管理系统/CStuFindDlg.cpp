// CStuFindDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "afxdialogex.h"
#include "CStuFindDlg.h"
#include "InfoFile.h"


// CStuFindDlg 对话框

IMPLEMENT_DYNAMIC(CStuFindDlg, CDialogEx)

CStuFindDlg::CStuFindDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STU_FIND, pParent)
{

}

CStuFindDlg::~CStuFindDlg()
{
}

void CStuFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbxFind);
	DDX_Control(pDX, IDC_EDIT3, m_edit_find);
	DDX_Control(pDX, IDC_EDIT1, m_edit_id);
	DDX_Control(pDX, IDC_EDIT2, m_edit_name);
	DDX_Control(pDX, IDC_EDIT4, m_edit_gender);
	DDX_Control(pDX, IDC_CHECK1, m_chk);
	DDX_Control(pDX, IDC_LIST1, m_list_find);
	DDX_Control(pDX, IDC_BUTTON1, m_btn_find);
	DDX_Control(pDX, IDC_BUTTON2, m_btn_del);
}


BEGIN_MESSAGE_MAP(CStuFindDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CStuFindDlg::OnCbnSelchangeCombo1)
//	ON_EN_CHANGE(IDC_EDIT3, &CStuFindDlg::OnEnChangeEdit3)
ON_BN_CLICKED(IDC_CHECK1, &CStuFindDlg::OnBnClickedCheck1)
ON_BN_CLICKED(IDC_BUTTON1, &CStuFindDlg::OnBnClickedButton1)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CStuFindDlg::OnLvnItemchangedList1)
ON_BN_CLICKED(IDC_BUTTON4, &CStuFindDlg::OnBnClickedButton4)
ON_BN_CLICKED(IDC_BUTTON2, &CStuFindDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CStuFindDlg 消息处理程序


void CStuFindDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}


//void CStuFindDlg::OnEnChangeEdit3()
//{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
//}


void CStuFindDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
	{
		//设置为可修改
		m_edit_id.SetReadOnly(FALSE);
		m_edit_name.SetReadOnly(FALSE);
		m_edit_gender.SetReadOnly(FALSE);
		m_edit_find.SetReadOnly(TRUE);
		m_cbxFind.EnableWindow(FALSE);
		m_list_find.EnableWindow(FALSE);
		m_btn_del.EnableWindow(FALSE);
		m_btn_find.EnableWindow(FALSE);
	}
	else
	{
		//设置为只读
		m_edit_id.SetReadOnly(TRUE);
		m_edit_name.SetReadOnly(TRUE);
		m_edit_gender.SetReadOnly(TRUE);
		m_edit_find.SetReadOnly(FALSE);
		m_cbxFind.EnableWindow(TRUE);
		m_list_find.EnableWindow(TRUE);
		m_btn_del.EnableWindow(TRUE);
		m_btn_find.EnableWindow(TRUE);
	}
}


BOOL CStuFindDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_cbxFind.AddString(_T("按学号"));
	m_cbxFind.AddString(_T("按姓名"));
	m_cbxFind.SetCurSel(0);

	m_list_find.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list_find.InsertColumn(0, _T("学号"), 0, 140);
	m_list_find.InsertColumn(1, _T("姓名"), 0, 200);
	m_list_find.InsertColumn(2, _T("性别"), 0, 90);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CStuFindDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取查找方式
	int index = m_cbxFind.GetCurSel();
	if (index == -1)
	{
		MessageBox(_T("请选择查找方式！"));
		return;
	}
	else if (index == 0)
	{
		//按学号查找
		CString id;
		m_edit_find.GetWindowText(id);
		if (id.IsEmpty())
		{
			MessageBox(_T("请输入学号！"));
			return;
		}
		//查找学生信息
		CInfoFile file;
		file.ReadStudentInfo();
		Student* stu = file.FindStudentByID(_wtoi(id));
		if (stu == NULL)
		{
			MessageBox(_T("查无此人！"));
			return;
		}
		//显示学生信息
		m_edit_id.SetWindowText(id);
		CString name(stu->name);
		m_edit_name.SetWindowText(name);
		CString gender(stu->gender);
		m_edit_gender.SetWindowText(gender);

		UpdateData(FALSE);
	}
	else if (index == 1)
	{
		//按姓名查找
		CString name;
		m_edit_find.GetWindowText(name);
		if (name.IsEmpty())
		{
			MessageBox(_T("请输入姓名！"));
			return;
		}
		//查找学生信息
		CInfoFile file;
		file.ReadStudentInfo();
		int count = 0;
		Student** stu = file.FindStudentByName(name, &count);
		if (count == 0)
		{
			MessageBox(_T("查无此人！"));
			return;
		}
		//显示学生信息
		m_list_find.DeleteAllItems();
		for (int i = 0; i < count; i++)
		{
			CString id;
			id.Format(_T("%d"), stu[i]->id);
			m_list_find.InsertItem(i, id);

			char* p = stu[i]->name;
			int len = MultiByteToWideChar(CP_ACP, 0, p, -1, NULL, 0);
			wchar_t* wstr = new wchar_t[len];
			MultiByteToWideChar(CP_ACP, 0, p, -1, wstr, len);
			m_list_find.SetItemText(i, 1, wstr);

			char* p1 = stu[i]->gender;
			int len1 = MultiByteToWideChar(CP_ACP, 0, p1, -1, NULL, 0);
			wchar_t* wstr1 = new wchar_t[len1];
			MultiByteToWideChar(CP_ACP, 0, p1, -1, wstr1, len1);
			m_list_find.SetItemText(i, 2, wstr1);

			delete[] wstr;
		}

	}
}


void CStuFindDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	
	//CDialogEx::OnOK();
	
}


void CStuFindDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	//获取选中的行
	POSITION pos = m_list_find.GetFirstSelectedItemPosition();
	int nItem = m_list_find.GetNextSelectedItem(pos);
	CString id = m_list_find.GetItemText(nItem, 0);
	CString name = m_list_find.GetItemText(nItem, 1);
	CString gender = m_list_find.GetItemText(nItem, 2);

	m_edit_id.SetWindowText(id);
	m_edit_name.SetWindowText(name);
	m_edit_gender.SetWindowText(gender);

	UpdateData(FALSE);
}


void CStuFindDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取学生信息
	CString id, name, gender;
	m_edit_id.GetWindowText(id);
	m_edit_name.GetWindowText(name);
	m_edit_gender.GetWindowText(gender);
	if (id.IsEmpty() || name.IsEmpty() || gender.IsEmpty())
	{
		MessageBox(_T("请填写完整信息！"), _T("提示"));
		return;
	}
	//获取列表中选中项学号
	POSITION pos = m_list_find.GetFirstSelectedItemPosition();
	int nItem = m_list_find.GetNextSelectedItem(pos);
	CString id1 = m_list_find.GetItemText(nItem, 0);

	//修改学生信息
	CInfoFile file;
	file.ReadAllInfo();
	
	Student* tmp = file.FindStudentByID(_wtoi(id1));
	tmp->id = _wtoi(id);
	strcpy_s(tmp->name, NAME_MAX, CT2A(name));
	strcpy_s(tmp->gender, GENDER_MAX, CT2A(gender));
	
	file.WriteAllInfo();

	MessageBox(_T("修改成功！", _T("提示")));

	//刷新列表
	OnBnClickedButton1();
	//调整列表的选中项依旧为修改后的学生
	m_list_find.SetItemState(nItem, LVIS_SELECTED, LVIS_SELECTED);
}


void CStuFindDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//检查是否选中
	POSITION pos = m_list_find.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请选中要删除的学生信息！"));
		return;
	}
	int nItem = m_list_find.GetNextSelectedItem(pos);

	//获取学号
	CString id = m_list_find.GetItemText(nItem, 0);

	//删除学生信息
	CInfoFile file;
	file.ReadAllInfo();
	file.DeleteStudentByID(_wtoi(id));

	file.WriteAllInfo();

	MessageBox(_T("删除成功！"), _T("提示"));

	//刷新列表
	OnBnClickedButton1();
}
