#include"Head.h"
BOOL SetConsoleColor(WORD wAttributes)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
		return FALSE;
	return SetConsoleTextAttribute(hConsole, wAttributes);
}
void mainShow(){  //主界面的展示
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "———————————————————————————" << endl << endl;
	cout << "      ";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE| BACKGROUND_RED);
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
	cout << "    "<< endl << endl;
	cout << "———————————————————————————" << endl << endl;
	cout << "请输入操作：";
}
void adminShow(){ //管理员菜单显示
	system("cls");
	system("color A");
	cout << "———————————————————————————————————————————————————————————" << endl;
	cout << "1.注销登录    2.初始化课程信息    3.查看全部课程信息    4.增加课程    5.删除课程    6.修改课程    7.查看具体课程" << endl;
	cout << "———————————————————————————————————————————————————————————" << endl;
	cout << "请选择所需功能：";
}
void studentShow(){ //学生菜单显示
	system("cls");
	system("color A");
	cout << "———————————————————————————————————————————————————————————" << endl;
	cout << "1.注销登录    2.查看课程信息    3.选课    4.查看个人课表    5.退课   6.举手报名助教   7.选择个人助教   8.退选个人助教" << endl;
	cout << "9.查看助教学生名单     10.修改密码" << endl;
	cout << "———————————————————————————————————————————————————————————" << endl;
	cout << "请选择所需功能：";
}