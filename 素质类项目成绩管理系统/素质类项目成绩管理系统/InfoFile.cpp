#include "pch.h"
#include "InfoFile.h"

CInfoFile::CInfoFile()
{
}

CInfoFile::~CInfoFile()
{
}

void CInfoFile::ReadLoginInfo(CString& name, CString& pwd_md5)
{
	ifstream ifs;
	ifs.open(_F_LOGIN);

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf));	//读取一行--用户名
	name = CString(buf);

	ifs.getline(buf, sizeof(buf));	//读取一行--密码md5
	pwd_md5 = CString(buf);

	ifs.close();
}

void CInfoFile::WritePwd(char* name, char* pwd_md5)
{
	ofstream ofs;
	ofs.open(_F_LOGIN);

	ofs << name << endl;
	ofs << pwd_md5 << endl;

	ofs.close();
}

//读取学生信息
//学生信息文件格式：学号|姓名|性别|成绩数|论文数|项目数|获奖数
void CInfoFile::ReadStudentInfo()
{
	ifstream ifs(_F_STUDENT);

	student_num = 0;
	InitList(student_head);

	char buf[1024] = { 0 };	//缓冲区

	//取表头
	ifs.getline(buf, sizeof(buf));

	//读取学生信息
	while (!ifs.eof())
	{
		Student* tmp = (Student*)malloc(sizeof(Student));
		*tmp = { 0 };

		ifs.getline(buf, sizeof(buf));
		student_num++;

		//读取学号
		char* p = strtok(buf, "|");
		if (p != NULL)
		{
			tmp->id = atoi(p);
		}
		else
		{
			break;
		}
		//读取姓名
		p = strtok(NULL, "|");
		strcpy(tmp->name, p);
		//读取性别
		p = strtok(NULL, "|");
		strcpy(tmp->gender, p);
		//读取成绩数
		p = strtok(NULL, "|");
		tmp->scoreNum = atoi(p);
		//读取论文数
		p = strtok(NULL, "|");
		tmp->thesisNum = atoi(p);
		//读取项目数
		p = strtok(NULL, "|");
		tmp->projectNum = atoi(p);
		//读取获奖数
		p = strtok(NULL, "|");
		tmp->awardNum = atoi(p);

		//添加学生至链表
		PushBack(student_head, tmp);
	}

	ifs.close();
}

//读取学生成绩
//学生成绩文件格式：学号|课程名称|成绩
void CInfoFile::ReadScoreInfo()
{
	ifstream ifs(_F_SCORE);

	char buf[1024] = { 0 };	//缓冲区

	//取表头
	ifs.getline(buf, sizeof(buf));
	
	//读取学生成绩
	while (!ifs.eof())
	{
		int id;	//学号-标识符

		//读取学号
		char* p = strtok(buf, "|");
		if (p != NULL)
		{
			id = atoi(p);
		}
		else
		{
			break;
		}

		//根据学号查找学生
		Student* pStu = FindStudentByID(id);
		pStu->scoreNum++;

		//读取课程名称
		p = strtok(NULL, "|");
		strcpy(pStu->score[pStu->scoreNum - 1].subject, p);
		//读取成绩
		p = strtok(NULL, "|");
		pStu->score[pStu->scoreNum - 1].score = atoi(p);
	}

	ifs.close();
}

//读取学生论文
//学生论文文件格式：学号|论文标题|期刊名称|页码信息|发表时间|论文级别|通讯作者|作者列表
void CInfoFile::ReadThesisInfo()
{
	ifstream ifs(_F_THESIS);

	char buf[1024] = { 0 };	//缓冲区

	//取表头
	ifs.getline(buf, sizeof(buf));

	//读取学生论文
	while (!ifs.eof())
	{
		int id;	//学号-标识符

		//读取学号
		char* p = strtok(buf, "|");
		if (p != NULL)
		{
			id = atoi(p);
		}
		else
		{
			break;
		}

		//根据学号查找学生
		Student* pStu = FindStudentByID(id);
		pStu->thesisNum++;

		//读取论文标题
		p = strtok(NULL, "|");
		strcpy(pStu->thesis[pStu->thesisNum - 1].title, p);
		//读取期刊名称
		p = strtok(NULL, "|");
		strcpy(pStu->thesis[pStu->thesisNum - 1].periodical, p);
		//读取页码信息
		p = strtok(NULL, "|");
		strcpy(pStu->thesis[pStu->thesisNum - 1].pagination, p);
		//读取发表时间（格式：yyyy-mm-dd）
		p = strtok(NULL, "|");
		char*q = strtok(p, "-");
		pStu->thesis[pStu->thesisNum - 1].publishDate.year = atoi(q);
		q = strtok(NULL, "-");
		pStu->thesis[pStu->thesisNum - 1].publishDate.month = atoi(q);
		q = strtok(NULL, "-");
		pStu->thesis[pStu->thesisNum - 1].publishDate.day = atoi(q);
		//读取论文级别
		p = strtok(NULL, "|");
		strcpy(&(pStu->thesis[pStu->thesisNum - 1].grade), p);
		//读取通讯作者
		p = strtok(NULL, "|");
		strcpy(pStu->thesis[pStu->thesisNum - 1].author[0], p);
		//读取作者列表（以顿号分隔）
		p = strtok(NULL, "|");
		q = strtok(p, "、");
		int i = 1;
		while (q != NULL)
		{
			strcpy(pStu->thesis[pStu->thesisNum - 1].author[i], q);
			q = strtok(NULL, "、");
			i++;
		}
	}

	ifs.close();
}

//读取学生项目
//学生项目文件格式：学号|项目名称|项目编号|开始时间|结束时间|指导老师|成员列表
void CInfoFile::ReadProjectInfo()
{
	ifstream ifs(_F_PROJECT);

	char buf[1024] = { 0 };	//缓冲区

	//取表头
	ifs.getline(buf, sizeof(buf));

	//读取学生项目
	while (!ifs.eof())
	{
		int id;	//学号-标识符

		//读取学号
		char* p = strtok(buf, "|");
		if (p != NULL)
		{
			id = atoi(p);
		}
		else
		{
			break;
		}

		//根据学号查找学生
		Student* pStu = FindStudentByID(id);
		pStu->projectNum++;

		//读取项目名称
		p = strtok(NULL, "|");
		strcpy(pStu->project[pStu->projectNum - 1].title, p);
		//读取项目编号
		p = strtok(NULL, "|");
		pStu->project[pStu->projectNum - 1].projectID = atoi(p);
		//读取开始时间（格式：yyyy-mm-dd）
		p = strtok(NULL, "|");
		char* q = strtok(p, "-");
		pStu->project[pStu->projectNum - 1].startDate.year = atoi(q);
		q = strtok(NULL, "-");
		pStu->project[pStu->projectNum - 1].startDate.month = atoi(q);
		q = strtok(NULL, "-");
		pStu->project[pStu->projectNum - 1].startDate.day = atoi(q);
		//读取结束时间（格式：yyyy-mm-dd）
		p = strtok(NULL, "|");
		q = strtok(p, "-");
		pStu->project[pStu->projectNum - 1].endDate.year = atoi(q);
		q = strtok(NULL, "-");
		pStu->project[pStu->projectNum - 1].endDate.month = atoi(q);
		q = strtok(NULL, "-");
		pStu->project[pStu->projectNum - 1].endDate.day = atoi(q);
		//读取指导老师
		p = strtok(NULL, "|");
		strcpy(pStu->project[pStu->projectNum - 1].member[0], p);
		//读取成员列表（以顿号分隔）
		p = strtok(NULL, "|");
		q = strtok(p, "、");
		int i = 1;
		while (q != NULL)
		{
			strcpy(pStu->project[pStu->projectNum - 1].member[i], q);
			q = strtok(NULL, "、");
			i++;
		}
	}

	ifs.close();
}

//读取学生获奖
//学生获奖文件格式：学号|奖项名称|颁奖单位|获奖级别|获奖时间|指导老师|成员列表
void CInfoFile::ReadAwardInfo()
{
	ifstream ifs(_F_AWARD);

	char buf[1024] = { 0 };	//缓冲区

	//取表头
	ifs.getline(buf, sizeof(buf));

	//读取学生获奖
	while (!ifs.eof())
	{
		int id;	//学号-标识符

		//读取学号
		char* p = strtok(buf, "|");
		if (p != NULL)
		{
			id = atoi(p);
		}
		else
		{
			break;
		}

		//根据学号查找学生
		Student* pStu = FindStudentByID(id);
		pStu->awardNum++;

		//读取奖项名称
		p = strtok(NULL, "|");
		strcpy(pStu->award[pStu->awardNum - 1].title, p);
		//读取颁奖单位
		p = strtok(NULL, "|");
		strcpy(pStu->award[pStu->awardNum - 1].organization, p);
		//读取获奖级别
		p = strtok(NULL, "|");
		strcpy(pStu->award[pStu->awardNum - 1].level, p);
		//读取获奖时间（格式：yyyy-mm-dd）
		p = strtok(NULL, "|");
		char* q = strtok(p, "-");
		pStu->award[pStu->awardNum - 1].awardDate.year = atoi(q);
		q = strtok(NULL, "-");
		pStu->award[pStu->awardNum - 1].awardDate.month = atoi(q);
		q = strtok(NULL, "-");
		pStu->award[pStu->awardNum - 1].awardDate.day = atoi(q);
		//读取指导老师
		p = strtok(NULL, "|");
		strcpy(pStu->award[pStu->awardNum - 1].member[0], p);
		//读取成员列表（以顿号分隔）
		p = strtok(NULL, "|");
		q = strtok(p, "、");
		int i = 1;
		while (q != NULL)
		{
			strcpy(pStu->award[pStu->awardNum - 1].member[i], q);
			q = strtok(NULL, "、");
			i++;
		}
	}

	ifs.close();
}

//写入学生信息
void CInfoFile::WriteStudentInfo()
{
	ofstream ofs(_F_STUDENT);

	//写入表头
	ofs << "学号|姓名|性别|成绩数|论文数|项目数|获奖数" << endl;

	Node* pcur = student_head->next;
	while (pcur != NULL)
	{
		Student* pStu = (Student*)pcur->data;

		//写入学生信息
		ofs << pStu->id << "|";
		ofs << pStu->name << "|";
		ofs << pStu->gender << "|";
		ofs << pStu->scoreNum << "|";
		ofs << pStu->thesisNum << "|";
		ofs << pStu->projectNum << "|";
		ofs << pStu->awardNum << endl;

		pcur = pcur->next;
	}

	ofs.close();
}

//写入学生成绩
void CInfoFile::WriteScoreInfo()
{
	ofstream ofs(_F_SCORE);

	//写入表头
	ofs << "学号|课程名称|成绩" << endl;

	Node* pcur = student_head->next;
	while (pcur != NULL)
	{
		Student* pStu = (Student*)pcur->data;

		for (int i = 0; i < pStu->scoreNum; i++)
		{
			//写入学生成绩
			ofs << pStu->id << "|";
			ofs << pStu->score[i].subject << "|";
			ofs << pStu->score[i].score << endl;
		}

		pcur = pcur->next;
	}

	ofs.close();
}

//写入学生论文
void CInfoFile::WriteThesisInfo()
{
	ofstream ofs(_F_THESIS);

	//写入表头
	ofs << "学号|论文标题|期刊名称|页码信息|发表时间|论文级别|通讯作者|作者列表" << endl;

	Node* pcur = student_head->next;
	while (pcur != NULL)
	{
		Student* pStu = (Student*)pcur->data;

		for (int i = 0; i < pStu->thesisNum; i++)
		{
			//写入学生论文
			ofs << pStu->id << "|";
			ofs << pStu->thesis[i].title << "|";
			ofs << pStu->thesis[i].periodical << "|";
			ofs << pStu->thesis[i].pagination << "|";
			ofs << pStu->thesis[i].publishDate.year << "-" << pStu->thesis[i].publishDate.month << "-" << pStu->thesis[i].publishDate.day << "|";
			ofs << pStu->thesis[i].grade << "|";
			ofs << pStu->thesis[i].author[0] << "|";
			for (int j = 1; j < MEMBER_MAX; j++)
			{
				if (strlen(pStu->thesis[i].author[j]) > 0)
				{
					ofs << pStu->thesis[i].author[j] << "、";
				}
			}
			ofs << endl;
		}

		pcur = pcur->next;
	}

	ofs.close();
}

//写入学生项目
void CInfoFile::WriteProjectInfo()
{
	ofstream ofs(_F_PROJECT);

	//写入表头
	ofs << "学号|项目名称|项目编号|开始时间|结束时间|指导老师|成员列表" << endl;

	Node* pcur = student_head->next;
	while (pcur != NULL)
	{
		Student* pStu = (Student*)pcur->data;

		for (int i = 0; i < pStu->projectNum; i++)
		{
			//写入学生项目
			ofs << pStu->id << "|";
			ofs << pStu->project[i].title << "|";
			ofs << pStu->project[i].projectID << "|";
			ofs << pStu->project[i].startDate.year << "-" << pStu->project[i].startDate.month << "-" << pStu->project[i].startDate.day << "|";
			ofs << pStu->project[i].endDate.year << "-" << pStu->project[i].endDate.month << "-" << pStu->project[i].endDate.day << "|";
			ofs << pStu->project[i].member[0] << "|";
			for (int j = 1; j < MEMBER_MAX; j++)
			{
				if (strlen(pStu->project[i].member[j]) > 0)
				{
					ofs << pStu->project[i].member[j] << "、";
				}
			}
			ofs << endl;
		}

		pcur = pcur->next;
	}

	ofs.close();
}

//写入学生获奖
void CInfoFile::WriteAwardInfo()
{
	ofstream ofs(_F_AWARD);

	//写入表头
	ofs << "学号|奖项名称|颁奖单位|获奖级别|获奖时间|指导老师|成员列表" << endl;

	Node* pcur = student_head->next;
	while (pcur != NULL)
	{
		Student* pStu = (Student*)pcur->data;

		for (int i = 0; i < pStu->awardNum; i++)
		{
			//写入学生获奖
			ofs << pStu->id << "|";
			ofs << pStu->award[i].title << "|";
			ofs << pStu->award[i].organization << "|";
			ofs << pStu->award[i].level << "|";
			ofs << pStu->award[i].awardDate.year << "-" << pStu->award[i].awardDate.month << "-" << pStu->award[i].awardDate.day << "|";
			ofs << pStu->award[i].member[0] << "|";
			for (int j = 1; j < MEMBER_MAX; j++)
			{
				if (strlen(pStu->award[i].member[j]) > 0)
				{
					ofs << pStu->award[i].member[j] << "、";
				}
			}
			ofs << endl;
		}

		pcur = pcur->next;
	}

	ofs.close();
}

//通过学号查找学生信息
Student* CInfoFile::FindStudentByID(int id)
{
	Node* pcur = student_head->next;
	while (pcur != NULL)
	{
		Student* pStu = (Student*)pcur->data;
		if (pStu->id == id)
		{
			return pStu;
		}
		pcur = pcur->next;
	}
	return NULL;
}