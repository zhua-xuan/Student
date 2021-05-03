#include"Head.h"
string LessonIDPlus(LessonsInformation table){
	string zero = "00";
	int temp;
	stringstream stream(table.LessonID);
	stream >> temp;
	temp++;
	stringstream stream1;
	stream1 << temp;
	stream1>> table.LessonID;
	table.LessonID=zero + table.LessonID;
	stream.clear(); stream1.clear();
	return table.LessonID;
}
void mainLessonIDPlus(){
	if (!ifInitializationCourse()){
		cout << "课程还未初始化导入!请按任意键返回菜单" << endl;
		system("pause");
		adminpage();
	}
	else{
		cout << "请输入需要添加的课程个数：";
		int n; cin >> n;
		for (int i = 0; i < n; i++){
			cout << "请输入课程具体信息(不同信息之间以空格隔开,从左向右依次为：课程名称、教师名、上限人数、已选人数、课程属性（专业课/非专业课，例：课程1 教师1 60 0 专业课 ）：";
			LessonsInformation temp;
		A:cin >> temp.LessonName >> temp.TeacherName >> temp.MaxNoP >> temp.NowNop >> temp.LessonType;
			int j;
			for (j = 0; j < Lessons.size(); j++){
				if (Lessons[j].LessonName == temp.LessonName&&Lessons[j].TeacherName == temp.TeacherName){
					cout << "该课程已存在，添加失败！请重新输入(不同信息之间以空格隔开）：";
					goto A;
				}
			}

			if (j == Lessons.size()){
				temp.LessonID = Lessons[j - 1].LessonID;
				temp.LessonID = LessonIDPlus(temp);
				Lessons.push_back(temp);
				cout << "此课程添加成功！" << endl;
			}
		}
		cout << "所有课程添加成功！" << endl;
		lessonVector2File();
		adminSearchAllLessons();
	}
}