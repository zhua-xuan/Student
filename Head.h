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
#define P 4  //专业课个数
#define NP 2   //非专业课个数
struct LessonsInformation{
	string LessonID;
	string LessonName;
	string TeacherName;
	int MaxNoP; //上限人数
	int NowNop; //目前已选人数
	string LessonType;
	vector<string> assistants;
};
extern vector<LessonsInformation>Lessons;
struct StudentsInformation{
	string StudentID;
	string Password;
	vector<LessonsInformation>PersonalLessons;
};
extern vector<StudentsInformation>Students; //学生总列表
extern int StudentkeyID;   //登录进学生系统的学生ID下标
extern int pcourse,npcourse,allcourse;//计算专业课和非专业课数量
extern int lessonmark1,lessonmark2; //记录此学生报名助教的课程ID在课程列表中的下标

void mainShow();  //主菜单的展示
void adminShow();  //管理员菜单的展示
void studentShow();  //学生菜单的展示
void mainpage();//主页面
void adminpage();//管理员页面
void studentpage();  //学生菜单页面
BOOL SetConsoleColor(WORD wAttributes);  //字体颜色
bool StudentSignin(); //学生注册
bool StudentLogin(); //学生登录
void StudentLogout(); //学生注销 
void AdministratorLogout(); //管理员注销
bool AdministratorLogion();  //管理员登录

void lessonVector2File(); //将vector课程数据存入currentcourse文件
void studentVector2File();//将vector学生数据的ID和密码存入student文件
void studentsFile2Students();  //将student文件录入vector学生数据
void personalstudentVector2File();//将vector学生个人数据的课程信息的课程ID和助教ID存入以学生ID命名的文件中
void personalstudentFile2Vector(); //将学生个人文件录入vector学生数据
void assistantsVector2File();  //助教vector录入文件
void assistantsFile2Vector();  //助教文件录入vector

void InitializationCourse(); //初始化课程
bool ifInitializationCourse(); //是否存在currentcourse
void adminSearchAllLessons();//管理员查看全部课程
void studentSearchAllLessons();  //学生查看全部课程
void SearchCertainLesson();//查看具体课程
void StudentsforLesson(int); //选这个课的学生有哪些
void mainLessonIDPlus(); //增加课程
string LessonIDPlus(LessonsInformation table); //课程ID++
void mainReviseLesson();//修改某一课程
void DeleteLesson();//删除某一课程
void StudentsforLesson(int i);//查看选课学生名单

void DropLesson(); //退课
void SplitString(const string &s, vector<string>&v, const string &c);//分割字符
void SearchPersonalLesson(); //查看个人课表
int CountforOtherAssistant(); //计算此学生已报课程助教个数
bool CountmyLessonAssistant(int);//看自己某门课有没有助教
void SignForAssistant(); //报名助教
void ChoosemyLessonAssistant();  //选择某门课的助教
void ChooseLesson();//选课
int CountmyLessons();//看已经选了几门课
void BubblesortmyLessons();//个人课程列表课程信息始终按课程ID升序显示
void SearchmyStudents();  //查看选自己作为助教的学生
void DropmyAssistant();  //退选助教
void StudentChangePassword();  //学生修改密码

bool ifmyassistantloss(); //是否有助教退课了，设置提醒