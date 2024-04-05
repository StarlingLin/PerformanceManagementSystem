#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "List.h"

using namespace std;

//�����ļ�·��
#define _F_LOGIN	"./login.ini"	//��¼�ļ�·��
#define _F_STUDENT	"./student.txt"	//ѧ����Ϣ�ļ�·��
#define _F_SCORE	"./score.txt"	//ѧ���ɼ��ļ�·��
#define _F_THESIS	"./thesis.txt"	//������Ϣ�ļ�·��
#define _F_PROJECT	"./project.txt"	//��Ŀ��Ϣ�ļ�·��
#define _F_AWARD	"./award.txt"	//����Ϣ�ļ�·��

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//��ȡ��¼��Ϣ
	void ReadLoginInfo(CString& name, CString& pwd_md5);
	//д���¼��Ϣ
	void WritePwd(char* name, char* pwd_md5);

	//��ȡѧ����Ϣ
	void ReadStudentInfo();
	//��ȡѧ���ɼ�
	void ReadScoreInfo();
	//��ȡ������Ϣ
	void ReadThesisInfo();
	//��ȡ��Ŀ��Ϣ
	void ReadProjectInfo();
	//��ȡ����Ϣ
	void ReadAwardInfo();
	
	//д��ѧ����Ϣ
	void WriteStudentInfo();
	//д��ѧ���ɼ�
	void WriteScoreInfo();
	//д��������Ϣ
	void WriteThesisInfo();
	//д����Ŀ��Ϣ
	void WriteProjectInfo();
	//д�����Ϣ
	void WriteAwardInfo();

	//ȫ����Ϣ��ȡ
	void ReadAllInfo();
	//ȫ����Ϣд���ļ�
	void WriteAllInfo();

	//ɾ��ѧ����Ϣ
	void DeleteStudent(int pos);
	//����ѧ��ɾ��ѧ����Ϣ
	void DeleteStudentByID(int id);

	//ѧ������
	int GetStudentNum();
	//��i��ѧ��
	Student* GetStudent(int i);

	//ͨ��ѧ�Ų���ѧ����Ϣ
	Student* FindStudentByID(int id);
	//ͨ����������ѧ����Ϣ
	Student** FindStudentByName(CString name, int* count);

	//�ж�ѧ���Ƿ����
	bool IsIDExist(int id);

	//���ѧ����Ϣ
	void AddStudent(Student* stu);

	//��ѧ������
	void SortByID();

	Node* student_head;	//ѧ����Ϣ����ͷ
	int student_num;	//ѧ����Ϣ����
};