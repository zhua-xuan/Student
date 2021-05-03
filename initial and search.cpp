#include"Head.h"
void InitializationCourse(){  //初始化课程文件
	cout << "请输入需要导入的文件名称：";
	string initial; //导入文件的名称
	cin >> initial;
	while (initial != "defaultcourse.txt"){
		cout << "未找到该文件名，请重新输入:";
		cin >> initial;
	}
	ifstream fp("defaultcourse.txt", ios::in);
	if (!fp){
		cerr << "文件打开失败！" << endl;
		exit(-1);
	}
	while (!fp.eof()){
		struct LessonsInformation temp;
		fp >> temp.LessonID;
		fp >> temp.LessonName;
		fp >> temp.TeacherName;
		fp >> temp.MaxNoP;
		fp >> temp.NowNop;
		fp >> temp.LessonType;
		Lessons.push_back(temp);
	}
	Lessons.pop_back();
	fp.close();
	lessonVector2File();
	assistantsFile2Vector();
	cout << "初始化成功！" << endl;
	cout << "请按任意键返回管理员菜单" << endl;
	system("pause");
	adminpage();
}
void lessonVector2File(){   //将Lessons读入currentcourse
	ofstream fp2("currentcourse.txt", ios::out);
	if (!fp2){
		cerr << "文件打开失败！" << endl;
		exit(-1);
	}
	for (int i = 0; i < Lessons.size(); i++){
		fp2 << Lessons[i].LessonID << " ";
		fp2 << Lessons[i].LessonName << " ";
		fp2 << Lessons[i].TeacherName << " ";
		fp2 << Lessons[i].MaxNoP << " ";
		fp2 << Lessons[i].NowNop << " ";
		fp2 << Lessons[i].LessonType << " ";
		fp2 << endl;
	}
	fp2.close();
}


void SearchCertainLesson(){  //查看具体某门课
	if (!ifInitializationCourse()){
		system("pause");
		adminpage();
	}
	else{
		cout << "输入需要查看的课程ID或名称：";
		string key;
		cin >> key;
		int i;
		for (i = 0; i < Lessons.size(); i++){
			if (Lessons[i].LessonID == key || Lessons[i].LessonName == key){
				cout << "****************************************************************************************" << endl;
				cout << setiosflags(ios::left);
				cout <<setw(12)<< Lessons[i].LessonID << setw(22)<< Lessons[i].LessonName;
				cout <<setw(16)<< Lessons[i].TeacherName << setw(12) << Lessons[i].MaxNoP;
				cout <<setw(12)<<Lessons[i].NowNop << setw(12) << Lessons[i].LessonType << endl;
				cout << "****************************************************************************************" << endl;
				break;
			}
		}
		if (i == Lessons.size()){
			cout << "查看失败！没有找到此课程！" << endl;
			cout << "请按任意键返回管理员菜单" << endl;
			system("pause");
			adminpage();
		}
		else{
			cout << "还希望进行以下哪项操作：1.查看选课学生名单   2.查看课程报名助教名单" << endl;
			cout << "输入操作编号：";
			string k;
			cin >> k;
			while (k != "1"&&k != "2"){
				cout << "无法查询到此功能，请重新输入，1或2！" << endl;
				cin >> k;
			}
			if (k =="1") StudentsforLesson(i);
			else if (k == "2"){
				assistantsFile2Vector();
				if (Lessons[i].assistants.size() == 0){
					cout << "此课暂无助教！请按任意键返回管理员菜单" << endl;
				}
				else{
					cout << "目前报名这门课的助教有：";
					for (int j = 0; j < Lessons[i].assistants.size(); j++)
						cout << Lessons[i].assistants[j] << " ";
					cout << endl << "请按任意键返回管理员菜单" << endl;
				}
				system("pause");
				adminpage();
			}
		}
	}
} 

void StudentsforLesson(int i){ //报名这门课的学生有
	if (Lessons[i].NowNop != 0){
		studentsFile2Students();  //读入学生列表
		cout << "目前选择该门课的学生有：";
		size_t n;
		for (n = 0; n < Students.size(); n++){
			StudentkeyID = n;
			personalstudentFile2Vector(); //读此同学课程表
			for (size_t j = 0; j < Students[n].PersonalLessons.size(); j++)
				if (Students[n].PersonalLessons[j].LessonID == Lessons[i].LessonID)
					cout << Students[n].StudentID << " ";
		}
		cout << endl;
	}
	cout <<"共计" << Lessons[i].NowNop << "名学生，距离满课还差" << Lessons[i].MaxNoP - Lessons[i].NowNop << "人！";
	cout << "请按任意键返回管理员菜单" << endl;
	system("pause");
	adminpage();
}

void adminSearchAllLessons(){
	if (!ifInitializationCourse()){
		cout << "课程还未初始化导入!请按任意键返回菜单" << endl;
		system("pause");
		adminpage();
	}
	else{
		cout << "****************************************************************************************" << endl;
		cout << setiosflags(ios::left);
		cout << setw(12)<<"课程ID" << setw(22)<<"课程名称" <<setw(16)<< "授课教师" <<setw(12)<< "上限人数" <<setw(12)<< "目前已选" <<setw(12)<< "课程类型" << endl;
		for (int i = 0; i < Lessons.size(); i++){
			cout << setw(12) << Lessons[i].LessonID << setw(22) << Lessons[i].LessonName;
			cout << setw(16) << Lessons[i].TeacherName << setw(12) << Lessons[i].MaxNoP;
			cout << setw(12) << Lessons[i].NowNop << setw(12) << Lessons[i].LessonType << endl;
		}
		cout << "****************************************************************************************" << endl;
		cout << "请按任意键返回管理员菜单" << endl;
		system("pause");
		adminpage();
	}
}
void studentSearchAllLessons(){
	if (!ifInitializationCourse()){
		system("pause");
		studentpage();
	}
	else{
		cout << "****************************************************************************************" << endl;
		cout << setiosflags(ios::left);
		cout << setw(12) << "课程ID" << setw(22) << "课程名称" << setw(16) << "授课教师" << setw(12) << "上限人数" << setw(12) << "目前已选" << setw(12) << "课程类型" << endl;
		for (int i = 0; i < Lessons.size(); i++){
			cout << setw(12) << Lessons[i].LessonID << setw(22) << Lessons[i].LessonName;
			cout << setw(16) << Lessons[i].TeacherName << setw(12) << Lessons[i].MaxNoP;
			cout << setw(12) << Lessons[i].NowNop << setw(12) << Lessons[i].LessonType << endl;
		}
		cout << "****************************************************************************************" << endl;
		cout << "请按任意键返回学生菜单" << endl;
		system("pause");
		studentpage();
	}
}
bool ifInitializationCourse(){
	ifstream fp("currentcourse.txt", ios::in);
	if (!fp){
		return false;
	}
	else{
		if (Lessons.size() == 0){  //没读进Lessons过
			while (!fp.eof()){
				struct LessonsInformation temp;
				fp >> temp.LessonID;
				fp >> temp.LessonName;
				fp >> temp.TeacherName;
				fp >> temp.MaxNoP;
				fp >> temp.NowNop;
				fp >> temp.LessonType;
				Lessons.push_back(temp);
			}
			Lessons.pop_back();
		}
		fp.close();
		return true;
	}
}

void  SearchPersonalLesson(){ //查看个人课表
	personalstudentFile2Vector();
	cout << "目前所选课程有：" << endl;
	cout << "*****************************************************************************************" << endl;
	cout << setiosflags(ios::left);
	cout << setw(12) << "课程ID" << setw(22) << "课程名称" << setw(18) << "授课教师" << setw(18) << "课程类型" << setw(18) << "个人助教"<< endl;
	for (size_t i = 0; i < Students[StudentkeyID].PersonalLessons.size(); i++){
		for (size_t j = 0; j < Lessons.size(); j++){
			if (Students[StudentkeyID].PersonalLessons[i].LessonID == Lessons[j].LessonID){
				cout << setw(12) << Students[StudentkeyID].PersonalLessons[i].LessonID <<setw(22)<< Lessons[j].LessonName;
				cout << setw(18) << Lessons[j].TeacherName;
				cout << setw(18) << Lessons[j].LessonType << setw(18) << Students[StudentkeyID].PersonalLessons[i].assistants[0] << endl;
				break;
			}
		}
	}
	cout << "*****************************************************************************************" << endl;
	int unip = CountmyLessons();
	if (pcourse < 4){
		if (npcourse < 2)
			cout << "根据学院要求，目前所选课程数不达标！仍差" << P - pcourse << "门专业课，以及" << NP - npcourse << "门非专业课！请及时选课！" << endl;
		else
			cout << "根据学院要求，目前所选课程数不达标！仍差" << P - pcourse << "门专业课"<<endl;
	}
	else if (npcourse<2)
		cout << "根据学院要求，目前所选课程数不达标！仍差" << NP - npcourse << "门非专业课！请及时选课！" << endl;
	cout << "请按任意键返回学生菜单" << endl;
	system("pause");
	studentpage();
}
void SearchmyStudents(){  //查看自己作为助教的学生
	int temp; //储存本人学生列表下标
	temp = StudentkeyID;
	if (CountforOtherAssistant() == 0) //没报名过助教
		cout << "   您尚未报名过助教！请按任意键返回学生菜单！" << endl;
	else{  //报名过至少一个
		cout << "目前报名助教的课程有：";
		cout << Lessons[lessonmark1].LessonID << " ";
		if (lessonmark2 != -1) cout << Lessons[lessonmark2].LessonID << endl;
		else cout << endl;
		cout << "请输入需查询的课程ID：";
		string keyLessonID;
		cin >> keyLessonID;
		if (keyLessonID == Lessons[lessonmark1].LessonID || (lessonmark2 != -1 && keyLessonID == Lessons[lessonmark2].LessonID)){//如果查询的是上述两门课之一
			cout << "这门课选择你作为助教的学生有：";
			int flag = 0;//看是否有学生选我
			for (size_t n = 0; n < Students.size(); n++){
				StudentkeyID = n;
				personalstudentFile2Vector();
				for (size_t m = 0; m < Students[n].PersonalLessons.size(); m++){
					if (Students[n].PersonalLessons[m].LessonID==keyLessonID&&Students[n].PersonalLessons[m].assistants[0] == Students[temp].StudentID){
						flag = 1;
						cout << Students[n].StudentID << " ";
						break;
					}
				}
			}
			if (flag == 0) cout << "无";
			cout << endl << "请按任意键返回学生菜单！" << endl;
		}
		else
			cout << "输入的课程ID有误，请按任意键返回学生菜单！" << endl;
	}
	StudentkeyID = temp;// 将StudentkeyID还回去
	system("pause");
	studentpage();
}
