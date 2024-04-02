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

	ifs.getline(buf, sizeof(buf));	//��ȡһ��--�û���
	name = CString(buf);

	ifs.getline(buf, sizeof(buf));	//��ȡһ��--����md5
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

//��ȡѧ����Ϣ
//ѧ����Ϣ�ļ���ʽ��ѧ��|����|�Ա�|�ɼ���|������|��Ŀ��|����
void CInfoFile::ReadStudentInfo()
{
	ifstream ifs(_F_STUDENT);

	student_num = 0;
	InitList(student_head);

	char buf[1024] = { 0 };	//������

	//ȡ��ͷ
	ifs.getline(buf, sizeof(buf));

	//��ȡѧ����Ϣ
	while (!ifs.eof())
	{
		Student* tmp = (Student*)malloc(sizeof(Student));
		*tmp = { 0 };

		ifs.getline(buf, sizeof(buf));
		student_num++;

		//��ȡѧ��
		char* p = strtok(buf, "|");
		if (p != NULL)
		{
			tmp->id = atoi(p);
		}
		else
		{
			break;
		}
		//��ȡ����
		p = strtok(NULL, "|");
		strcpy(tmp->name, p);
		//��ȡ�Ա�
		p = strtok(NULL, "|");
		strcpy(tmp->gender, p);
		//��ȡ�ɼ���
		p = strtok(NULL, "|");
		tmp->scoreNum = atoi(p);
		//��ȡ������
		p = strtok(NULL, "|");
		tmp->thesisNum = atoi(p);
		//��ȡ��Ŀ��
		p = strtok(NULL, "|");
		tmp->projectNum = atoi(p);
		//��ȡ����
		p = strtok(NULL, "|");
		tmp->awardNum = atoi(p);

		//���ѧ��������
		PushBack(student_head, tmp);
	}

	ifs.close();
}

//��ȡѧ���ɼ�
//ѧ���ɼ��ļ���ʽ��ѧ��|�γ�����|�ɼ�
void CInfoFile::ReadScoreInfo()
{
	ifstream ifs(_F_SCORE);

	char buf[1024] = { 0 };	//������

	//ȡ��ͷ
	ifs.getline(buf, sizeof(buf));
	
	//��ȡѧ���ɼ�
	while (!ifs.eof())
	{
		int id;	//ѧ��-��ʶ��

		//��ȡѧ��
		char* p = strtok(buf, "|");
		if (p != NULL)
		{
			id = atoi(p);
		}
		else
		{
			break;
		}

		//����ѧ�Ų���ѧ��
		Student* pStu = FindStudentByID(id);
		pStu->scoreNum++;

		//��ȡ�γ�����
		p = strtok(NULL, "|");
		strcpy(pStu->score[pStu->scoreNum - 1].subject, p);
		//��ȡ�ɼ�
		p = strtok(NULL, "|");
		pStu->score[pStu->scoreNum - 1].score = atoi(p);
	}

	ifs.close();
}

//��ȡѧ������
//ѧ�������ļ���ʽ��ѧ��|���ı���|�ڿ�����|ҳ����Ϣ|����ʱ��|���ļ���|ͨѶ����|�����б�
void CInfoFile::ReadThesisInfo()
{
	ifstream ifs(_F_THESIS);

	char buf[1024] = { 0 };	//������

	//ȡ��ͷ
	ifs.getline(buf, sizeof(buf));

	//��ȡѧ������
	while (!ifs.eof())
	{
		int id;	//ѧ��-��ʶ��

		//��ȡѧ��
		char* p = strtok(buf, "|");
		if (p != NULL)
		{
			id = atoi(p);
		}
		else
		{
			break;
		}

		//����ѧ�Ų���ѧ��
		Student* pStu = FindStudentByID(id);
		pStu->thesisNum++;

		//��ȡ���ı���
		p = strtok(NULL, "|");
		strcpy(pStu->thesis[pStu->thesisNum - 1].title, p);
		//��ȡ�ڿ�����
		p = strtok(NULL, "|");
		strcpy(pStu->thesis[pStu->thesisNum - 1].periodical, p);
		//��ȡҳ����Ϣ
		p = strtok(NULL, "|");
		strcpy(pStu->thesis[pStu->thesisNum - 1].pagination, p);
		//��ȡ����ʱ�䣨��ʽ��yyyy-mm-dd��
		p = strtok(NULL, "|");
		char*q = strtok(p, "-");
		pStu->thesis[pStu->thesisNum - 1].publishDate.year = atoi(q);
		q = strtok(NULL, "-");
		pStu->thesis[pStu->thesisNum - 1].publishDate.month = atoi(q);
		q = strtok(NULL, "-");
		pStu->thesis[pStu->thesisNum - 1].publishDate.day = atoi(q);
		//��ȡ���ļ���
		p = strtok(NULL, "|");
		strcpy(&(pStu->thesis[pStu->thesisNum - 1].grade), p);
		//��ȡͨѶ����
		p = strtok(NULL, "|");
		strcpy(pStu->thesis[pStu->thesisNum - 1].author[0], p);
		//��ȡ�����б��Զٺŷָ���
		p = strtok(NULL, "|");
		q = strtok(p, "��");
		int i = 1;
		while (q != NULL)
		{
			strcpy(pStu->thesis[pStu->thesisNum - 1].author[i], q);
			q = strtok(NULL, "��");
			i++;
		}
	}

	ifs.close();
}

//��ȡѧ����Ŀ
//ѧ����Ŀ�ļ���ʽ��ѧ��|��Ŀ����|��Ŀ���|��ʼʱ��|����ʱ��|ָ����ʦ|��Ա�б�
void CInfoFile::ReadProjectInfo()
{
	ifstream ifs(_F_PROJECT);

	char buf[1024] = { 0 };	//������

	//ȡ��ͷ
	ifs.getline(buf, sizeof(buf));

	//��ȡѧ����Ŀ
	while (!ifs.eof())
	{
		int id;	//ѧ��-��ʶ��

		//��ȡѧ��
		char* p = strtok(buf, "|");
		if (p != NULL)
		{
			id = atoi(p);
		}
		else
		{
			break;
		}

		//����ѧ�Ų���ѧ��
		Student* pStu = FindStudentByID(id);
		pStu->projectNum++;

		//��ȡ��Ŀ����
		p = strtok(NULL, "|");
		strcpy(pStu->project[pStu->projectNum - 1].title, p);
		//��ȡ��Ŀ���
		p = strtok(NULL, "|");
		pStu->project[pStu->projectNum - 1].projectID = atoi(p);
		//��ȡ��ʼʱ�䣨��ʽ��yyyy-mm-dd��
		p = strtok(NULL, "|");
		char* q = strtok(p, "-");
		pStu->project[pStu->projectNum - 1].startDate.year = atoi(q);
		q = strtok(NULL, "-");
		pStu->project[pStu->projectNum - 1].startDate.month = atoi(q);
		q = strtok(NULL, "-");
		pStu->project[pStu->projectNum - 1].startDate.day = atoi(q);
		//��ȡ����ʱ�䣨��ʽ��yyyy-mm-dd��
		p = strtok(NULL, "|");
		q = strtok(p, "-");
		pStu->project[pStu->projectNum - 1].endDate.year = atoi(q);
		q = strtok(NULL, "-");
		pStu->project[pStu->projectNum - 1].endDate.month = atoi(q);
		q = strtok(NULL, "-");
		pStu->project[pStu->projectNum - 1].endDate.day = atoi(q);
		//��ȡָ����ʦ
		p = strtok(NULL, "|");
		strcpy(pStu->project[pStu->projectNum - 1].member[0], p);
		//��ȡ��Ա�б��Զٺŷָ���
		p = strtok(NULL, "|");
		q = strtok(p, "��");
		int i = 1;
		while (q != NULL)
		{
			strcpy(pStu->project[pStu->projectNum - 1].member[i], q);
			q = strtok(NULL, "��");
			i++;
		}
	}

	ifs.close();
}

//��ȡѧ����
//ѧ�����ļ���ʽ��ѧ��|��������|�佱��λ|�񽱼���|��ʱ��|ָ����ʦ|��Ա�б�
void CInfoFile::ReadAwardInfo()
{
	ifstream ifs(_F_AWARD);

	char buf[1024] = { 0 };	//������

	//ȡ��ͷ
	ifs.getline(buf, sizeof(buf));

	//��ȡѧ����
	while (!ifs.eof())
	{
		int id;	//ѧ��-��ʶ��

		//��ȡѧ��
		char* p = strtok(buf, "|");
		if (p != NULL)
		{
			id = atoi(p);
		}
		else
		{
			break;
		}

		//����ѧ�Ų���ѧ��
		Student* pStu = FindStudentByID(id);
		pStu->awardNum++;

		//��ȡ��������
		p = strtok(NULL, "|");
		strcpy(pStu->award[pStu->awardNum - 1].title, p);
		//��ȡ�佱��λ
		p = strtok(NULL, "|");
		strcpy(pStu->award[pStu->awardNum - 1].organization, p);
		//��ȡ�񽱼���
		p = strtok(NULL, "|");
		strcpy(pStu->award[pStu->awardNum - 1].level, p);
		//��ȡ��ʱ�䣨��ʽ��yyyy-mm-dd��
		p = strtok(NULL, "|");
		char* q = strtok(p, "-");
		pStu->award[pStu->awardNum - 1].awardDate.year = atoi(q);
		q = strtok(NULL, "-");
		pStu->award[pStu->awardNum - 1].awardDate.month = atoi(q);
		q = strtok(NULL, "-");
		pStu->award[pStu->awardNum - 1].awardDate.day = atoi(q);
		//��ȡָ����ʦ
		p = strtok(NULL, "|");
		strcpy(pStu->award[pStu->awardNum - 1].member[0], p);
		//��ȡ��Ա�б��Զٺŷָ���
		p = strtok(NULL, "|");
		q = strtok(p, "��");
		int i = 1;
		while (q != NULL)
		{
			strcpy(pStu->award[pStu->awardNum - 1].member[i], q);
			q = strtok(NULL, "��");
			i++;
		}
	}

	ifs.close();
}

//д��ѧ����Ϣ
void CInfoFile::WriteStudentInfo()
{
	ofstream ofs(_F_STUDENT);

	//д���ͷ
	ofs << "ѧ��|����|�Ա�|�ɼ���|������|��Ŀ��|����" << endl;

	Node* pcur = student_head->next;
	while (pcur != NULL)
	{
		Student* pStu = (Student*)pcur->data;

		//д��ѧ����Ϣ
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

//д��ѧ���ɼ�
void CInfoFile::WriteScoreInfo()
{
	ofstream ofs(_F_SCORE);

	//д���ͷ
	ofs << "ѧ��|�γ�����|�ɼ�" << endl;

	Node* pcur = student_head->next;
	while (pcur != NULL)
	{
		Student* pStu = (Student*)pcur->data;

		for (int i = 0; i < pStu->scoreNum; i++)
		{
			//д��ѧ���ɼ�
			ofs << pStu->id << "|";
			ofs << pStu->score[i].subject << "|";
			ofs << pStu->score[i].score << endl;
		}

		pcur = pcur->next;
	}

	ofs.close();
}

//д��ѧ������
void CInfoFile::WriteThesisInfo()
{
	ofstream ofs(_F_THESIS);

	//д���ͷ
	ofs << "ѧ��|���ı���|�ڿ�����|ҳ����Ϣ|����ʱ��|���ļ���|ͨѶ����|�����б�" << endl;

	Node* pcur = student_head->next;
	while (pcur != NULL)
	{
		Student* pStu = (Student*)pcur->data;

		for (int i = 0; i < pStu->thesisNum; i++)
		{
			//д��ѧ������
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
					ofs << pStu->thesis[i].author[j] << "��";
				}
			}
			ofs << endl;
		}

		pcur = pcur->next;
	}

	ofs.close();
}

//д��ѧ����Ŀ
void CInfoFile::WriteProjectInfo()
{
	ofstream ofs(_F_PROJECT);

	//д���ͷ
	ofs << "ѧ��|��Ŀ����|��Ŀ���|��ʼʱ��|����ʱ��|ָ����ʦ|��Ա�б�" << endl;

	Node* pcur = student_head->next;
	while (pcur != NULL)
	{
		Student* pStu = (Student*)pcur->data;

		for (int i = 0; i < pStu->projectNum; i++)
		{
			//д��ѧ����Ŀ
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
					ofs << pStu->project[i].member[j] << "��";
				}
			}
			ofs << endl;
		}

		pcur = pcur->next;
	}

	ofs.close();
}

//д��ѧ����
void CInfoFile::WriteAwardInfo()
{
	ofstream ofs(_F_AWARD);

	//д���ͷ
	ofs << "ѧ��|��������|�佱��λ|�񽱼���|��ʱ��|ָ����ʦ|��Ա�б�" << endl;

	Node* pcur = student_head->next;
	while (pcur != NULL)
	{
		Student* pStu = (Student*)pcur->data;

		for (int i = 0; i < pStu->awardNum; i++)
		{
			//д��ѧ����
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
					ofs << pStu->award[i].member[j] << "��";
				}
			}
			ofs << endl;
		}

		pcur = pcur->next;
	}

	ofs.close();
}

//ͨ��ѧ�Ų���ѧ����Ϣ
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