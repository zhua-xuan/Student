#include"Head.h"
vector<LessonsInformation>Lessons;
vector<StudentsInformation>Students;
int StudentkeyID;  //登录进此系统的学生ID下标
int pcourse = 0, npcourse = 0, allcourse = 0;//计算专业课和非专业课数量
int lessonmark1 = -1, lessonmark2 = -1;
int main(){
	mainpage();
	return 0;
}
void mainpage(){  //用户输入登录方式
	mainShow();
	string LoginChoose;
	cin >> LoginChoose;
	if (LoginChoose=="3"){
		if (AdministratorLogion()) //登录成功了,登录不成功他会在那儿不停登录的
			adminpage();
	}
	else if (LoginChoose == "2"){
		if (StudentSignin())  //学生注册成功了
			studentpage();
		else mainpage();  //注册不成功，返回主菜单
	}
	else if (LoginChoose == "1"){
		if (StudentLogin())  //学生登录成功了
			studentpage();
		else mainpage();
	}
	else{
		cout << "**********选择功能失败，请按任意键返回登录界面，输入1或2或3！**********" << endl;
		system("pause");
		system("cls");
		mainpage();
	}
}
void adminpage(){
	adminShow();
	string FunctionChoose;
	cin >> FunctionChoose;
	if (FunctionChoose =="1")
		AdministratorLogout();
	else if (FunctionChoose =="2") {
		if (ifInitializationCourse()){
			cout << "课程已经初始化，请按任意键重新选择操作！";
			system("pause");
			adminpage();//回到管理员菜单选择
		}
		else InitializationCourse();
	}
	else if (FunctionChoose == "3")
		adminSearchAllLessons();
	else if (FunctionChoose == "4")
		mainLessonIDPlus();
	else if (FunctionChoose == "5")
		DeleteLesson();
	else if (FunctionChoose == "6")
		mainReviseLesson();
	else if (FunctionChoose == "7")
		SearchCertainLesson();
	else{
		cout << "**********选择功能失败，请按任意键返回管理员界面，从1、2、3、4、5、6、7中选择数字输入！**********" << endl;
		system("pause");
		adminpage();
	}
}

void studentpage(){
	studentShow();
	string FunctionChoose;
	cin >> FunctionChoose;
	if (FunctionChoose == "1")
		StudentLogout();
	else if (!ifInitializationCourse()){ //将课程信息读入Lessons
		cout << "管理员尚未初始化！请按任意键返回学生菜单" << endl;
		system("pause");
		studentpage();
	}
	else{
		assistantsFile2Vector();  //将助教名字录入Lessons的助教列表
		if (ifmyassistantloss())
			cout << "所选课程有助教退课！请注意查看" << endl;
		if (FunctionChoose == "2")
			studentSearchAllLessons();
		else if (FunctionChoose == "3")
			ChooseLesson();
		else if (FunctionChoose == "4")
			SearchPersonalLesson();
		else if (FunctionChoose == "5")
			DropLesson();
		else if (FunctionChoose == "6")
			SignForAssistant();
		else if (FunctionChoose == "7")
			ChoosemyLessonAssistant();
		else if (FunctionChoose == "8")
			DropmyAssistant();
		else if (FunctionChoose == "9")
			SearchmyStudents();
		else if (FunctionChoose == "10")
			StudentChangePassword();
		else{
			cout << "**********选择功能失败，请按任意键返回学生界面，从1、2、3、4、5、6、7中选择数字输入！**********" << endl;
			system("pause");
			studentpage();
		}
	}
}