// CAddThesisDlg.cpp: 实现文件
//

#include "pch.h"
#include "素质类项目成绩管理系统.h"
#include "afxdialogex.h"
#include "CAddThesisDlg.h"
#include "InfoFile.h"


// CAddThesisDlg 对话框

IMPLEMENT_DYNAMIC(CAddThesisDlg, CDialogEx)

CAddThesisDlg::CAddThesisDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADDTHESIS, pParent)
	, m_edit_title(_T(""))
	, m_edit_periodical(_T(""))
	, m_edit_pagination(_T(""))
	, m_edit_author0(_T(""))
	, m_edit_author(_T(""))
	, m_edit_id(_T(""))
{

}

CAddThesisDlg::~CAddThesisDlg()
{
}

void CAddThesisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_edit_title);
	DDX_Text(pDX, IDC_EDIT5, m_edit_periodical);
	DDX_Text(pDX, IDC_EDIT6, m_edit_pagination);
	DDX_Text(pDX, IDC_EDIT7, m_edit_author0);
	DDX_Control(pDX, IDC_COMBO1, m_cbx);
	DDX_Text(pDX, IDC_EDIT8, m_edit_author);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_date);
	DDX_Text(pDX, IDC_EDIT1, m_edit_id);
}


BEGIN_MESSAGE_MAP(CAddThesisDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON7, &CAddThesisDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CAddThesisDlg 消息处理程序


void CAddThesisDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CInfoFile file;
	file.ReadAllInfo();
	//获取ID对应的学生
	CString strID;
	GetDlgItemText(IDC_EDIT1, strID);
	Student* pStu = file.FindStudentByID(_ttoi(strID));
	if (pStu == NULL)
	{
		MessageBox(L"学号不存在", L"提示");
		return;
	}
	//获取论文对象
	Thesis* pThesis = &pStu->thesis[pStu->thesisNum];
	pStu->thesisNum++;
	//获取编辑框内容
	strcpy(pThesis->title, CT2A(m_edit_title));
	strcpy(pThesis->periodical, CT2A(m_edit_periodical));
	strcpy(pThesis->pagination, CT2A(m_edit_pagination));
	strcpy(pThesis->author[0], CT2A(m_edit_author0));

	//获取日期
	CTime time;
	m_date.GetTime(time);
	pThesis->publishDate.year = time.GetYear();
	pThesis->publishDate.month = time.GetMonth();
	pThesis->publishDate.day = time.GetDay();
	//获取论文级别（T、A、B、C、D、E）
	int index = m_cbx.GetCurSel();
	CString strLevel;
	m_cbx.GetLBText(index, strLevel);
	pThesis->grade = *CT2A(strLevel);
	//添加作者
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
		strcpy(pThesis->author[j++], CT2A(author));
	}
	//保存
	file.WriteAllInfo();
	MessageBox(L"添加成功", L"提示");
	CDialogEx::OnOK();
}


void CAddThesisDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}
