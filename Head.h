#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include<Windows.h>
using namespace std;
#define P 4  //רҵ�θ���
#define NP 2   //��רҵ�θ���
struct LessonsInformation{
	string LessonID;
	string LessonName;
	string TeacherName;
	int MaxNoP; //��������
	int NowNop; //Ŀǰ��ѡ����
	string LessonType;
	vector<string> assistants;
};
extern vector<LessonsInformation>Lessons;
struct StudentsInformation{
	string StudentID;
	string Password;
	vector<LessonsInformation>PersonalLessons;
};
extern vector<StudentsInformation>Students; //ѧ�����б�
extern int StudentkeyID;   //��¼��ѧ��ϵͳ��ѧ��ID�±�
extern int pcourse,npcourse,allcourse;//����רҵ�κͷ�רҵ������
extern int lessonmark1,lessonmark2; //��¼��ѧ���������̵Ŀγ�ID�ڿγ��б��е��±�

void mainShow();  //���˵���չʾ
void adminShow();  //����Ա�˵���չʾ
void studentShow();  //ѧ���˵���չʾ
void mainpage();//��ҳ��
void adminpage();//����Աҳ��
void studentpage();  //ѧ���˵�ҳ��
BOOL SetConsoleColor(WORD wAttributes);  //������ɫ
bool StudentSignin(); //ѧ��ע��
bool StudentLogin(); //ѧ����¼
void StudentLogout(); //ѧ��ע�� 
void AdministratorLogout(); //����Աע��
bool AdministratorLogion();  //����Ա��¼

void lessonVector2File(); //��vector�γ����ݴ���currentcourse�ļ�
void studentVector2File();//��vectorѧ�����ݵ�ID���������student�ļ�
void studentsFile2Students();  //��student�ļ�¼��vectorѧ������
void personalstudentVector2File();//��vectorѧ���������ݵĿγ���Ϣ�Ŀγ�ID������ID������ѧ��ID�������ļ���
void personalstudentFile2Vector(); //��ѧ�������ļ�¼��vectorѧ������
void assistantsVector2File();  //����vector¼���ļ�
void assistantsFile2Vector();  //�����ļ�¼��vector

void InitializationCourse(); //��ʼ���γ�
bool ifInitializationCourse(); //�Ƿ����currentcourse
void adminSearchAllLessons();//����Ա�鿴ȫ���γ�
void studentSearchAllLessons();  //ѧ���鿴ȫ���γ�
void SearchCertainLesson();//�鿴����γ�
void StudentsforLesson(int); //ѡ����ε�ѧ������Щ
void mainLessonIDPlus(); //���ӿγ�
string LessonIDPlus(LessonsInformation table); //�γ�ID++
void mainReviseLesson();//�޸�ĳһ�γ�
void DeleteLesson();//ɾ��ĳһ�γ�
void StudentsforLesson(int i);//�鿴ѡ��ѧ������

void DropLesson(); //�˿�
void SplitString(const string &s, vector<string>&v, const string &c);//�ָ��ַ�
void SearchPersonalLesson(); //�鿴���˿α�
int CountforOtherAssistant(); //�����ѧ���ѱ��γ����̸���
bool CountmyLessonAssistant(int);//���Լ�ĳ�ſ���û������
void SignForAssistant(); //��������
void ChoosemyLessonAssistant();  //ѡ��ĳ�ſε�����
void ChooseLesson();//ѡ��
int CountmyLessons();//���Ѿ�ѡ�˼��ſ�
void BubblesortmyLessons();//���˿γ��б�γ���Ϣʼ�հ��γ�ID������ʾ
void SearchmyStudents();  //�鿴ѡ�Լ���Ϊ���̵�ѧ��
void DropmyAssistant();  //��ѡ����
void StudentChangePassword();  //ѧ���޸�����

bool ifmyassistantloss(); //�Ƿ��������˿��ˣ���������