// CStuShowDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "afxdialogex.h"
#include "CStuShowDlg.h"
#include "CAddStuDlg.h"
#include "InfoFile.h"


// CStuShowDlg 对话框

IMPLEMENT_DYNAMIC(CStuShowDlg, CDialogEx)

CStuShowDlg::CStuShowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STU_SHOW, pParent)
{

}

CStuShowDlg::~CStuShowDlg()
{
}

void CStuShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list_stuShow);
	DDX_Control(pDX, IDC_EDIT1, m_edit_stuid);
	DDX_Control(pDX, IDC_EDIT2, m_edit_stuname);
	DDX_Control(pDX, IDC_EDIT4, m_edit_stugender);
	DDX_Control(pDX, IDC_BUTTON1, m_btn_add);
	DDX_Control(pDX, IDC_BUTTON3, m_btn_del);
}


BEGIN_MESSAGE_MAP(CStuShowDlg, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CStuShowDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_CHECK1, &CStuShowDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON4, &CStuShowDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CStuShowDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CStuShowDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CStuShowDlg 消息处理程序


BOOL CStuShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//设置表头
	m_list_stuShow.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list_stuShow.InsertColumn(0, _T("学号"), 0, 140);
	m_list_stuShow.InsertColumn(1, _T("姓名"), 0, 200);
	m_list_stuShow.InsertColumn(2, _T("性别"), 0, 90);

	//读取文件
	CInfoFile file;
	file.ReadStudentInfo();

	//显示到列表控件
	for (int i = 0; i < file.GetStudentNum(); i++)
	{
		Student* stu = file.GetStudent(i);
		wstring tmp = to_wstring(stu->id);
		
		char* p = stu->name;
		int len = MultiByteToWideChar(CP_ACP, 0, p, -1, NULL, 0);
		wchar_t* wideStr = new wchar_t[len];
		LPCTSTR lpctstr = wideStr;
		MultiByteToWideChar(CP_ACP, 0, p, -1, wideStr, len);

		char* p1 = stu->gender;
		int len1 = MultiByteToWideChar(CP_ACP, 0, p1, -1, NULL, 0);
		wchar_t* wideStr1 = new wchar_t[len1];
		LPCTSTR lpctstr1 = wideStr1;
		MultiByteToWideChar(CP_ACP, 0, p1, -1, wideStr1, len1);

		m_list_stuShow.InsertItem(i, tmp.c_str());
		m_list_stuShow.SetItemText(i, 1, wideStr);
		m_list_stuShow.SetItemText(i, 2, wideStr1);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CStuShowDlg::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	//获取选中的行
	POSITION pos = m_list_stuShow.GetFirstSelectedItemPosition();
	int nItem = m_list_stuShow.GetNextSelectedItem(pos);
	CString id = m_list_stuShow.GetItemText(nItem, 0);
	CString name = m_list_stuShow.GetItemText(nItem, 1);
	CString gender = m_list_stuShow.GetItemText(nItem, 2);

	m_edit_stuid.SetWindowText(id);
	m_edit_stuname.SetWindowText(name);
	m_edit_stugender.SetWindowText(gender);

	UpdateData(FALSE);
}


void CStuShowDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
	{
		m_edit_stuid.SetReadOnly(FALSE);
		m_edit_stuname.SetReadOnly(FALSE);
		m_edit_stugender.SetReadOnly(FALSE);
		m_btn_add.EnableWindow(FALSE);
		m_btn_del.EnableWindow(FALSE);
	}
	else
	{
		m_edit_stuid.SetReadOnly(TRUE);
		m_edit_stuname.SetReadOnly(TRUE);
		m_edit_stugender.SetReadOnly(TRUE);
		m_btn_add.EnableWindow(TRUE);
		m_btn_del.EnableWindow(TRUE);
	}
}


void CStuShowDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//检查是否选中
	POSITION pos = m_list_stuShow.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请选中要修改的学生信息！"));
		return;
	}
	int nItem = m_list_stuShow.GetNextSelectedItem(pos);

	//获取编辑框内容
	CString id, name, gender;
	m_edit_stuid.GetWindowText(id);
	m_edit_stuname.GetWindowText(name);
	m_edit_stugender.GetWindowText(gender);

	//修改学生信息
	CInfoFile file;
	file.ReadAllInfo();

	Student* tmp = file.GetStudent(nItem);
	tmp->id = _wtoi(id);
	strcpy_s(tmp->name, NAME_MAX, CT2A(name));
	strcpy_s(tmp->gender, GENDER_MAX, CT2A(gender));

	//写入文件
	file.WriteAllInfo();

	//更新列表控件
	m_list_stuShow.DeleteAllItems();
	for (int i = 0; i < file.GetStudentNum(); i++)
	{
		Student* stu = file.GetStudent(i);
		wstring tmp = to_wstring(stu->id);

		char* p = stu->name;
		int len = MultiByteToWideChar(CP_ACP, 0, p, -1, NULL, 0);
		wchar_t* wideStr = new wchar_t[len];
		LPCTSTR lpctstr = wideStr;
		MultiByteToWideChar(CP_ACP, 0, p, -1, wideStr, len);

		char* p1 = stu->gender;
		int len1 = MultiByteToWideChar(CP_ACP, 0, p1, -1, NULL, 0);
		wchar_t* wideStr1 = new wchar_t[len1];
		LPCTSTR lpctstr1 = wideStr1;
		MultiByteToWideChar(CP_ACP, 0, p1, -1, wideStr1, len1);

		m_list_stuShow.InsertItem(i, tmp.c_str());
		m_list_stuShow.SetItemText(i, 1, wideStr);
		m_list_stuShow.SetItemText(i, 2, wideStr1);
	}

	MessageBox(_T("修改成功！"), _T("管理学生"));
}


void CStuShowDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CAddStuDlg dlg;
	dlg.DoModal();

	//更新列表控件
	CInfoFile file;
	file.ReadStudentInfo();
	m_list_stuShow.DeleteAllItems();
	for (int i = 0; i < file.GetStudentNum(); i++)
	{
		Student* stu = file.GetStudent(i);
		wstring tmp = to_wstring(stu->id);

		char* p = stu->name;
		int len = MultiByteToWideChar(CP_ACP, 0, p, -1, NULL, 0);
		wchar_t* wideStr = new wchar_t[len];
		LPCTSTR lpctstr = wideStr;
		MultiByteToWideChar(CP_ACP, 0, p, -1, wideStr, len);

		char* p1 = stu->gender;
		int len1 = MultiByteToWideChar(CP_ACP, 0, p1, -1, NULL, 0);
		wchar_t* wideStr1 = new wchar_t[len1];
		LPCTSTR lpctstr1 = wideStr1;
		MultiByteToWideChar(CP_ACP, 0, p1, -1, wideStr1, len1);

		m_list_stuShow.InsertItem(i, tmp.c_str());
		m_list_stuShow.SetItemText(i, 1, wideStr);
		m_list_stuShow.SetItemText(i, 2, wideStr1);
	}
}


void CStuShowDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//检查是否选中
	POSITION pos = m_list_stuShow.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请选中要删除的学生信息！"));
		return;
	}
	int nItem = m_list_stuShow.GetNextSelectedItem(pos);	//获取选中的行，其值为0开始

	//删除学生信息
	CInfoFile file;
	file.ReadAllInfo();

	file.DeleteStudent(nItem);

	//写入文件
	file.WriteAllInfo();

	//更新列表控件
	m_list_stuShow.DeleteAllItems();
	for (int i = 0; i < file.GetStudentNum(); i++)
	{
		Student* stu = file.GetStudent(i);
		wstring tmp = to_wstring(stu->id);

		char* p = stu->name;
		int len = MultiByteToWideChar(CP_ACP, 0, p, -1, NULL, 0);
		wchar_t* wideStr = new wchar_t[len];
		LPCTSTR lpctstr = wideStr;
		MultiByteToWideChar(CP_ACP, 0, p, -1, wideStr, len);

		char* p1 = stu->gender;
		int len1 = MultiByteToWideChar(CP_ACP, 0, p1, -1, NULL, 0);
		wchar_t* wideStr1 = new wchar_t[len1];
		LPCTSTR lpctstr1 = wideStr1;
		MultiByteToWideChar(CP_ACP, 0, p1, -1, wideStr1, len1);

		m_list_stuShow.InsertItem(i, tmp.c_str());
		m_list_stuShow.SetItemText(i, 1, wideStr);
		m_list_stuShow.SetItemText(i, 2, wideStr1);
	}

	MessageBox(_T("删除成功！"), _T("管理学生"));
}
