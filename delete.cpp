#include"Head.h"
void DeleteLesson(){
	if (!ifInitializationCourse()){
		cout << "课程还未初始化导入!请按任意键返回菜单" << endl;
		system("pause");
		adminpage();
	}
	else{
		cout << "请输入课程编号：";
		string keyID;
		cin >> keyID;
		int i;
		for (i = 0; i < Lessons.size(); i++){
			if (Lessons[i].LessonID == keyID){
				if (Lessons[i].NowNop) { 
					cout << "该课程已有学生选定，无法删除!请按任意键返回管理员页面" << endl;
					system("pause");
					adminpage();
				}
				else{
					Lessons.erase(Lessons.begin() + i);
					lessonVector2File();
					cout << "删除此课程成功！请按任意键返回管理员页面" << endl;
					system("pause");
					adminpage();
				}
			}
		}
		if (i == Lessons.size()) {
			cout << "该课程不存在，删除失败" << endl;
			cout << "请按任意键返回管理员页面" << endl;
			system("pause");
			adminpage();
		}
	}
}