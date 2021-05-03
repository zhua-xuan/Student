#include"Head.h"
#define AdminID "Admin"
#define AdminP "admin"
void movecursor(int x, int y){
	HANDLE hout;
	COORD pos = { x, y };
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, pos);
}
bool AdministratorLogion(){ //管理员登录
	cout << "输入管理员ID：" << endl;
	cout << "输入管理员密码：" << endl;
	string Admin, Password;
	movecursor(13, 7);
	cin >> Admin;
	movecursor(15, 8);
	cin >> Password;
	if (Admin == AdminID&&Password == AdminP){
		cout << "*************登录成功！*************";
		system("pause");
		return true;
	}
	else{
		cout << "*************用户名或密码错误，登录失败！请按下任意键重新选择操作*************" << endl;
		system("pause");
		system("cls");
		cout << "———————————————————————————" << endl << endl;
		cout << "      ";
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED);
		cout << "1.学生登录";
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "    ";
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED);
		cout << "2.学生注册";
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "    ";
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED);
		cout << "3.管理员登录";
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "    " << endl << endl;
		cout << "———————————————————————————" << endl << endl << endl;
		AdministratorLogion();
	}
}

bool StudentSignin(){//学生注册
	//先读一下students文件录入Students中
	studentsFile2Students();
	cout << "输入学生ID：" << endl << "输入学生个人密码：";
	StudentsInformation temp;
	movecursor(11, 7);
	cin >> temp.StudentID;
	movecursor(17, 8);
	cin >> temp.Password;
	int i; //看是否已经存在此学生
	for (i = 0; i < Students.size(); i++){
		if (Students[i].StudentID == temp.StudentID){
			cout << "此学生ID已存在，注册失败！";
			cout << "请按任意键返回主菜单" << endl;
			system("pause");
			system("cls");
			return false;
		}
	}
	if (i == Students.size()){ //未注册过
		StudentkeyID = i;   //StudentKeyID在全局里用来记录这个学号下标
		Students.push_back(temp);
		studentVector2File();            //更新学生列表
		personalstudentVector2File();  //创建学生ID文件
		cout << "***********注册成功！登录成功！***********" << endl;
		cout << "请按任意键进入学生菜单" << endl;
		system("pause");
		return true;
	}
}
void studentVector2File(){//学生系统中，将vector学生数据的ID和密码存入students文件
	ofstream fp("students.txt", ios::out);
	if (!fp){
		cerr << "文件打开失败！" << endl;
		exit(-1);
	}
	for (int i = 0; i < Students.size(); i++){
		string secretpassword = Students[i].Password; //加密密码
		for (size_t j = 0; j < Students[i].Password.size(); j++){
			secretpassword[j] = ~secretpassword[j] + 95;
		}
		fp << Students[i].StudentID << " ";
		fp << secretpassword;
		fp << endl;
	}
	fp.close();
}
void personalstudentVector2File(){
	string fileStudentkeyID = Students[StudentkeyID].StudentID;
	fileStudentkeyID += ".txt";
	ofstream fp(fileStudentkeyID,ios::out);
	if (!fp){
		cerr << "文件打开失败！" << endl;
		exit(-1);
	}
	for (size_t j = 0; j < Students[StudentkeyID].PersonalLessons.size(); j++){
		fp << Students[StudentkeyID].PersonalLessons[j].LessonID << " ";
		fp << Students[StudentkeyID].PersonalLessons[j].assistants[0];
		fp << endl;
	}
	fp.close();
}
void studentsFile2Students(){
	ifstream fp("students.txt", ios::in);
	if (!fp){
		cout << "文件打开失败" << endl;
		exit(-1);
	}
	if (!fp.eof()){   //如果students文件不为空
		if (Students.size() == 0){  //如果未从文件读进过
			while (!fp.eof()){
				StudentsInformation temp;
				string coverpassword;
				fp >> temp.StudentID;
				fp >> coverpassword;
				for (size_t j = 0; j <coverpassword.size(); j++){ //解密
					coverpassword[j] = coverpassword[j] - 95;
					coverpassword[j] = ~coverpassword[j];
				}
				temp.Password = coverpassword;
				Students.push_back(temp);
			}
			Students.pop_back();
		}
	}
	fp.close();
}
bool StudentLogin(){//学生登录
	studentsFile2Students();  //读入学生列表
	cout << "输入学生ID：" << endl << "输入学生个人密码：";
	StudentsInformation temp;
	movecursor(11, 7);
	cin >> temp.StudentID;
	movecursor(17, 8);
	cin >> temp.Password;
	size_t i;
	for (i = 0; i < Students.size(); i++){
		if (Students[i].StudentID == temp.StudentID&&Students[i].Password == temp.Password){
			StudentkeyID = i;
			personalstudentFile2Vector();  //将个人课表信息录入Students[StudentkeyID].PersonalLessons
			cout << "**********登录成功！请按任意键进入学生菜单**********" << endl;
			system("pause");
			return true;
		}
	}
	if (i == Students.size()){
		cout << "登录失败！用户名或密码错误!请按任意键返回登录页面" << endl;
		system("pause");
		system("cls");
		return false;
	}
}
void personalstudentFile2Vector(){
	string fileStudentkeyID = Students[StudentkeyID].StudentID;
	fileStudentkeyID += ".txt";
	ifstream fp(fileStudentkeyID, ios::in);
	if (!fp){
		cerr << "文件打开失败" << endl;
		exit(-1);
	}
	if (Students[StudentkeyID].PersonalLessons.size() == 0){//没有读进过
		while (!fp.eof()){
			LessonsInformation temp; string tempassistant;
			fp >> temp.LessonID;
			fp >> tempassistant;
			temp.assistants.push_back(tempassistant);
			Students[StudentkeyID].PersonalLessons.push_back(temp);
		}
		Students[StudentkeyID].PersonalLessons.pop_back();
	}
	fp.close();
}

void assistantsVector2File(){
	ofstream fp("assistants.txt", ios::out);
	if (!fp){
		cerr << "文件打开失败" << endl;
		exit(-1);
	}
	for (size_t i = 0; i < Lessons.size();){
		if (Lessons[i].assistants.size() == 0) i++;
		else{
			fp << Lessons[i].LessonID << " ";
			for (size_t j = 0; j < Lessons[i].assistants.size(); j++){
				if (j == Lessons[i].assistants.size() - 1)
					fp << Lessons[i].assistants[j];
				else fp << Lessons[i].assistants[j] << ",";
			}
			fp << endl;
			i++;
		}
	}
	fp.close();
}

void assistantsFile2Vector(){
	ifstream fp("assistants.txt", ios::in);
	if (!fp){
		cerr << "文件打开失败" << endl;
		exit(-1);
	}
	while (!fp.eof()){
		string LessonID;
		fp >> LessonID;
		for (size_t i = 0; i < Lessons.size(); i++)
			if (Lessons[i].LessonID == LessonID&&Lessons[i].assistants.size()==0) {
				string assistants;
				fp >> assistants;
				SplitString(assistants, Lessons[i].assistants, ",");
				break;
			}
	}
	fp.close();
}

void SplitString(const string &s,vector<string>&v, const string &c){
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2){
		v.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length()) v.push_back(s.substr(pos1));
}

void StudentLogout(){//学生注销
	cout << "请按任意键返回登录界面" << endl;  //要清除学生个人课表和所有课的表
	Students[StudentkeyID].PersonalLessons.clear();
	Lessons.clear();
	Students.clear();
	system("pause");
	system("cls");
	mainpage();
}
void AdministratorLogout(){//管理员注销
	cout << "请按任意键返回登录界面" << endl;
	Lessons.clear();
	Students.clear();
	system("pause");
	system("cls");
	mainpage();
}

void StudentChangePassword(){
	C:cout << "请输入原密码：";
	string oldpassword;
	cin >> oldpassword;
	if (oldpassword == Students[StudentkeyID].Password){
		cout << "请输入新密码：";
		string newpassword;
		cin >> newpassword;
		if (newpassword == oldpassword){
			cout << "与原密码相同，修改失败！请按任意键返回学生菜单！" << endl;
			system("pause");
			studentpage();
		}
		else{
			Students[StudentkeyID].Password = newpassword;
			studentVector2File();
			cout << "*********修改密码成功！************" << endl;
			cout << "请按任意键返回登录菜单重新登录！" << endl;
			system("pause");
			system("cls");
			mainpage();
		}
	}
	else {
		cout << "原密码输入错误！" << endl;
		goto C;
	}
}