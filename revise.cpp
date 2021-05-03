#include"Head.h"
void ReviseTeacherName(int i){
	cout << "具体修改为：";
	cin >> Lessons[i].TeacherName;
	lessonVector2File();
	cout << "修改成功！" << endl;
	cout << "请按任意键返回管理员菜单" << endl;
	system("pause");
	adminpage();
}
void ReviseMaxNop(int i){
	cout << "具体修改为：";
	int newNop;
	cin >> newNop;
	if (newNop < Lessons[i].NowNop) {
		cout << "修改失败！修改后的容纳人数小于目前已选人数！" << endl;
		cout << "请按任意键返回管理员菜单" << endl;
		system("pause");
		adminpage();
	}
	else {
		Lessons[i].MaxNoP = newNop;
		lessonVector2File();
		cout << "修改成功！" << endl;
		cout << "请按任意键返回管理员菜单" << endl;
		system("pause");
		adminpage();
	}
}
void mainReviseLesson(){
	if (!ifInitializationCourse()){
		cout << "课程还未初始化导入!请按任意键返回菜单" << endl;
		system("pause");
		adminpage();
	}
	else{
		cout << "需要修改的课程ID：";
		string keyID;
		cin >> keyID;
		int i;
		for (i = 0; i < Lessons.size(); i++){
			if (Lessons[i].LessonID == keyID){
				cout << "需要修改的具体字段（1.授课教师名字   2.上限人数 请输入数字1或2）：";
				int k;
				cin >> k;
				while (k != 1 && k != 2){
					cout << "输入错误！请输入1或2:";
					cin >> k;
				}
				if (k == 1) ReviseTeacherName(i);
				else ReviseMaxNop(i);
			}
		}
		if (i == Lessons.size()) {
			cout << "修改失败，该课程不存在！" << endl;
			cout << "请按任意键返回管理员菜单" << endl;
			system("pause");
			adminpage();
		}
	}
}