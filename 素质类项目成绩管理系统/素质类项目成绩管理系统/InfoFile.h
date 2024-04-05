#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "List.h"

using namespace std;

//定义文件路径
#define _F_LOGIN	"./login.ini"	//登录文件路径
#define _F_STUDENT	"./student.txt"	//学生信息文件路径
#define _F_SCORE	"./score.txt"	//学生成绩文件路径
#define _F_THESIS	"./thesis.txt"	//论文信息文件路径
#define _F_PROJECT	"./project.txt"	//项目信息文件路径
#define _F_AWARD	"./award.txt"	//获奖信息文件路径

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//读取登录信息
	void ReadLoginInfo(CString& name, CString& pwd_md5);
	//写入登录信息
	void WritePwd(char* name, char* pwd_md5);

	//读取学生信息
	void ReadStudentInfo();
	//读取学生成绩
	void ReadScoreInfo();
	//读取论文信息
	void ReadThesisInfo();
	//读取项目信息
	void ReadProjectInfo();
	//读取获奖信息
	void ReadAwardInfo();
	
	//写入学生信息
	void WriteStudentInfo();
	//写入学生成绩
	void WriteScoreInfo();
	//写入论文信息
	void WriteThesisInfo();
	//写入项目信息
	void WriteProjectInfo();
	//写入获奖信息
	void WriteAwardInfo();

	//全部信息读取
	void ReadAllInfo();
	//全部信息写入文件
	void WriteAllInfo();

	//删除学生信息
	void DeleteStudent(int pos);
	//根据学号删除学生信息
	void DeleteStudentByID(int id);

	//学生数量
	int GetStudentNum();
	//第i个学生
	Student* GetStudent(int i);

	//通过学号查找学生信息
	Student* FindStudentByID(int id);
	//通过姓名查找学生信息
	Student** FindStudentByName(CString name, int* count);

	//判断学号是否存在
	bool IsIDExist(int id);

	//添加学生信息
	void AddStudent(Student* stu);

	//按学号排序
	void SortByID();

	Node* student_head;	//学生信息链表头
	int student_num;	//学生信息数量
};