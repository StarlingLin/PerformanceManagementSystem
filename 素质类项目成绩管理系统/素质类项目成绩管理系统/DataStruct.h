#pragma once
//��������ݽṹ

//������������󳤶�
#define NAME_MAX			20	//������󳤶�
#define GENDER_MAX			10	//�Ա���󳤶�
#define SCORE_MAX			100	//�����������
#define THESIS_MAX			5	//�����������
#define PROJECT_MAX			5	//��Ŀ�������
#define AWARD_MAX			5	//���������
#define MEMBER_MAX			10	//��Ա�����������Ŀ�����ġ��񽱣�
#define SUBJECT_MAX			50	//ѧ����󳤶�
#define TITLE_MAX			50	//������󳤶�
#define PERIODICAL_MAX		50	//�ڿ���󳤶�
#define PAGINATION_MAX		10	//ҳ����󳤶�
#define ORGANIZATION_MAX	50	//��֯��󳤶�
#define LEVEL_MAX			10	//������󳤶�

//������ṹ��
//���ڽṹ��
typedef struct Date
{
	int year;	//��
	int month;	//��
	int day;	//��
} Date;

//���Ľṹ��
typedef struct Thesis
{
	int id;								//ѧ��-Ψһ��ʶ
	char title[TITLE_MAX];				//������Ŀ
	char author[MEMBER_MAX][NAME_MAX];	//���ߣ�athor[0]ΪͨѶ���ߣ�author[1]Ϊ��һ���ߣ�author[2]Ϊ�ڶ����ߣ��Դ����ƣ�
	char periodical[PERIODICAL_MAX];	//�ڿ�
	char pagination[PAGINATION_MAX];	//ҳ��/����/���ı��
	Date publishDate;					//��������
	char grade;							//���ļ���T��A��B��C��D��E��
} Thesis;

//�����ṹ��
typedef struct Score
{
	int id;						//ѧ��-Ψһ��ʶ
	char subject[SUBJECT_MAX];	//ѧ��
	float score;				//����
} Score;

//��Ŀ�ṹ��
typedef struct Project
{
	int id;								//ѧ��-Ψһ��ʶ
	char title[TITLE_MAX];				//��Ŀ����
	char member[MEMBER_MAX][NAME_MAX];	//��Ա��member[0]Ϊָ����ʦ��member[1]Ϊ��Ա1��member[2]Ϊ��Ա2���Դ����ƣ�
	int projectID;						//��Ŀ���
	Date startDate;						//��ʼ����
	Date endDate;						//��������
} Project;

//�񽱽ṹ��
typedef struct Award
{
	int id;								//ѧ��-Ψһ��ʶ
	char title[TITLE_MAX];				//������
	char organization[ORGANIZATION_MAX];//�佱��֯
	char member[MEMBER_MAX][NAME_MAX];	//��Ա��member[0]Ϊָ����ʦ��member[1]Ϊ����1��member[2]Ϊ����2���Դ����ƣ�
	char level[LEVEL_MAX];				//�񽱼���
	Date awardDate;						//������
} Award;

//ѧ���ṹ��
typedef struct Student
{
	int id;							//ѧ��-Ψһ��ʶ
	char name[NAME_MAX];			//����
	char gender[GENDER_MAX];		//�Ա�
	int scoreNum;					//��������
	int thesisNum;					//��������
	int projectNum;					//��Ŀ����
	int awardNum;					//������
	Score score[SCORE_MAX];			//����
	Thesis thesis[THESIS_MAX];		//����
	Project project[PROJECT_MAX];	//��Ŀ
	Award award[AWARD_MAX];			//��
} Student;