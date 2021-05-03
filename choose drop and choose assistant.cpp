#include"Head.h"
void ChooseLesson(){
	if (CountmyLessons() == 10){
		cout << "已达选课上限，无法再选课！请按任意键返回学生菜单" << endl;
		system("pause");
		studentpage();
	}
	else{
		cout << "输入课程ID：";
		string keylessonID;   //要添加的课的ID
		cin >> keylessonID;
		size_t n;  //看学生课程列表里有无此课
		for (n = 0; n < Students[StudentkeyID].PersonalLessons.size(); n++){
			if (Students[StudentkeyID].PersonalLessons[n].LessonID == keylessonID) {
				cout << "添加失败，该课程已存在！请按任意键返回学生菜单" << endl;
				system("pause");
				studentpage();
			}
		}
		if (n == Students[StudentkeyID].PersonalLessons.size()){ //还未选过这个课
			size_t m;
			for (m = 0; m < Lessons.size(); m++){
				if (Lessons[m].LessonID == keylessonID){
					if (Lessons[m].NowNop < Lessons[m].MaxNoP){
						Students[StudentkeyID].PersonalLessons.push_back(Lessons[m]);
						Students[StudentkeyID].PersonalLessons[Students[StudentkeyID].PersonalLessons.size() - 1].assistants.resize(0);
						Students[StudentkeyID].PersonalLessons[Students[StudentkeyID].PersonalLessons.size()-1].assistants.push_back("NULL");
						Lessons[m].NowNop++;
						BubblesortmyLessons();
						personalstudentVector2File();//修改个人课表文件
						lessonVector2File();//更新currentcourse文件
						cout << "**********已添加到个人课表中！**********" << endl;
						break;
					}
					else {
						cout << "人数已达上限，无法添加！请按任意键返回学生菜单" << endl;
						system("pause");
						studentpage();
					}
				}
			}
			if (m == Lessons.size()) {
				cout << "不存在此课程,添加失败！请按任意键返回学生菜单" << endl;
				system("pause");
				studentpage();
			}
			else{
				cout << "请按任意键返回学生菜单" << endl;
				system("pause");
				studentpage();
			}
		}
	}
}
void BubblesortmyLessons(){       // 个人课程列表课程信息始终按课程ID升序显示
	for (size_t i = 0; i < Students[StudentkeyID].PersonalLessons.size() - 1; ++i)
		for (size_t j = 0; j < Students[StudentkeyID].PersonalLessons.size() - 1 - i; ++j)
			if (Students[StudentkeyID].PersonalLessons[j].LessonID>Students[StudentkeyID].PersonalLessons[j + 1].LessonID){
				swap(Students[StudentkeyID].PersonalLessons[j],Students[StudentkeyID].PersonalLessons[j + 1]);
			}
}
int CountmyLessons(){//返回一共几门课
	pcourse = 0; npcourse = 0;
	for (size_t n = 0; n < Students[StudentkeyID].PersonalLessons.size(); n++){
		for (size_t m = 0; m < Lessons.size(); m++){
			if (Students[StudentkeyID].PersonalLessons[n].LessonID == Lessons[m].LessonID){
				if (Lessons[m].LessonType == "专业课")
					pcourse++;
				else npcourse++;
				allcourse = pcourse + npcourse;
				break;
			}
		}
	}
	return allcourse;
}
void DropLesson(){
	cout << "输入课程ID或课程名称：";
	string keyLesson;
	cin >> keyLesson;
	size_t i;  //在课程列表的下标
	for (i = 0; i < Lessons.size(); i++){
		if (Lessons[i].LessonID == keyLesson || Lessons[i].LessonName == keyLesson)
			break;
	}
	if (i == Lessons.size()) {
		cout << "该门课不存在！请按任意键返回学生菜单" << endl;
		system("pause");
		studentpage();
	}
	else{   //该门课存在
		size_t j;
		for (j = 0; j < Students[StudentkeyID].PersonalLessons.size(); j++){
			if (Students[StudentkeyID].PersonalLessons[j].LessonID == Lessons[i].LessonID){ //如果选了这门课
				Students[StudentkeyID].PersonalLessons.erase(Students[StudentkeyID].PersonalLessons.begin() + j);
				Lessons[i].NowNop--;
				lessonVector2File();//更新Lessons文件
				personalstudentVector2File(); //更新个人课表
				for (size_t n = 0; n < Lessons[i].assistants.size(); n++){
					if (Lessons[i].assistants[n] == Students[StudentkeyID].StudentID){
						Lessons[i].assistants.erase(Lessons[i].assistants.begin() + n);
						assistantsVector2File(); //更新assistants文件
						break;
					}
					//下次提示某学生该助教退课
				}
				cout << "课程删除成功！" << endl;
				SearchPersonalLesson(); //查看个人课表
			}
		}
		if (j == Students[StudentkeyID].PersonalLessons.size()){
			cout << "尚未选改门课！删除失败！请按任意键返回学生菜单" << endl;
			system("pause");
			studentpage();
		}
	}
}
void SignForAssistant(){  //举手报名助教
	if (CountforOtherAssistant() == 2){
		cout << "已达到报名助教上限！请按任意键返回学生菜单" << endl;
		system("pause");
		studentpage();
	}
	else{  //未达上限
		cout << "输入对应课程ID或课程名称：";
		string keyLesson;
		cin >> keyLesson;
		size_t i;  //在课程列表的下标
		for (i = 0; i < Lessons.size(); i++){
			if (Lessons[i].LessonID == keyLesson || Lessons[i].LessonName == keyLesson)
				break;
		}
		if (i == Lessons.size()) {
			cout << "该门课不存在！请按任意键返回学生菜单" << endl;
			system("pause");
			studentpage();
		}
		else{  //所有课程中有这门课
			size_t j;
			for (j = 0; j < Students[StudentkeyID].PersonalLessons.size();){ //如果学生课表有这门课
				if (Students[StudentkeyID].PersonalLessons[j].LessonID == Lessons[i].LessonID){
					vector<string>::iterator it = find(Lessons[i].assistants.begin(), Lessons[i].assistants.end(), Students[StudentkeyID].StudentID);
					if (it != Lessons[i].assistants.end()){  //已经报名过这门课助教
						cout << "你已报名该门课助教！无法重复报名，请按任意键返回学生菜单" << endl;
						system("pause");
						studentpage();
					}
					else{ //没报名这门课助教
						Lessons[i].assistants.push_back(Students[StudentkeyID].StudentID);  //更新Lessons助教列表
						assistantsVector2File();  //更新助教文件
						cout << "报名助教成功！请按任意键返回学生菜单" << endl;
						system("pause");
						studentpage();
					}
				}
				else j++;
			}
			if (j == Students[StudentkeyID].PersonalLessons.size()){
				cout << "尚未选择这门课！报名助教失败！请按任意键返回学生菜单" << endl;
				system("pause");
				studentpage();
			}
		}
	}
}
int CountforOtherAssistant(){
	lessonmark1 = -1, lessonmark2 = -1;
	int count = 0;
	for (size_t i = 0; i < Lessons.size(); i++){
		for (size_t j = 0; j < Lessons[i].assistants.size();j++){
			if (Lessons[i].assistants[j] == Students[StudentkeyID].StudentID){
				if (lessonmark1 == -1) lessonmark1 = i;
				else if(lessonmark1!=i) lessonmark2 = i;
				count++;
				break;
			}
		}
	}
	return count;
}
void ChoosemyLessonAssistant(){//选择某门课的助教
	cout << "输入课程ID或课程名称：";
	string keyLesson;
	cin >> keyLesson;
	size_t i;  //在课程列表的下标
	for (i = 0; i < Lessons.size(); i++){
		if (Lessons[i].LessonID == keyLesson || Lessons[i].LessonName == keyLesson)
			break;
	}
	if (i == Lessons.size()) {
		cout << "该门课不存在！请按任意键返回学生菜单" << endl;
		system("pause");
		studentpage();
	}
	else{  //这门课在Lessons中有
		size_t j;  //在个人课程表的下标
		for (j = 0; j < Students[StudentkeyID].PersonalLessons.size(); j++){
			if (Students[StudentkeyID].PersonalLessons[j].LessonID == Lessons[i].LessonID){  //这门课他选了
				if (CountmyLessonAssistant(j)){  //选了助教了
					cout << "你已选择该课程助教，无法继续选择，请按任意键返回学生菜单" << endl;
					system("pause");
					studentpage();
				}
				else{  //没选助教呢
					size_t n = Lessons[i].assistants.size();
					if (n == 0){
						cout << "该课程尚无助教！无法选择！请按任意键返回学生菜单" << endl;
						system("pause");
						studentpage();
					}
					else{  //该门课有助教
						cout << "目前这门课的助教有：";
						for (n = 0; n < Lessons[i].assistants.size(); n++){
							if (n == Lessons[i].assistants.size() - 1)
								cout << Lessons[i].assistants[n];
							else cout << Lessons[i].assistants[n] << ",";
						}
						cout << endl << "请在上述的助教中，选择你的个人助教：";
						string myassistant;
						cin >> myassistant;
						//vector<string>::iterator it = find(Lessons[i].assistants.begin(), Lessons[i].assistants.end(), myassistant);
						size_t n;
						for (n = 0; n < Lessons[i].assistants.size(); n++){
							if (Lessons[i].assistants[n]==myassistant){  //该课程有这个助教
								if (Students[StudentkeyID].StudentID == myassistant){
									cout << "无法选择自己作为助教，请按任意键返回学生菜单" << endl;
									system("pause");
									studentpage();
								}
								else{
									Students[StudentkeyID].PersonalLessons[j].assistants.erase(Students[StudentkeyID].PersonalLessons[j].assistants.begin());
									Students[StudentkeyID].PersonalLessons[j].assistants.push_back(myassistant);
									personalstudentVector2File(); //更新学生个人文件
									cout << "已完成个人助教选择！请按任意键返回学生菜单" << endl;
									system("pause");
									studentpage();
								}
							}
						}
						if (n == Lessons[i].assistants.size()){
							cout << "该课程无此助教，请按任意键返回学生菜单" << endl;
							system("pause");
							studentpage();
						}
					}
				}
			}
		}
		if (j == Students[StudentkeyID].PersonalLessons.size()){  //这门课他没选
			cout << "尚未选择该门课！请按任意键返回学生菜单" << endl;
			system("pause");
			studentpage();
		}
	}
}
bool CountmyLessonAssistant(int j){
	if (Students[StudentkeyID].PersonalLessons[j].assistants[0] != "NULL")
		return true;
	else return false;
}

bool ifmyassistantloss(){
	int flag = 0;
	size_t i;
	for (i = 0; i < Students[StudentkeyID].PersonalLessons.size();i++){
		if (Students[StudentkeyID].PersonalLessons[i].assistants[0] == "NULL"); //本来就没助教
		else{ //这门课本来有助教
			for (size_t j = 0; j < Lessons.size();j++){
				if (Students[StudentkeyID].PersonalLessons[i].LessonID == Lessons[j].LessonID){ //找到这个学生的这个课在课程列表的下标
					size_t n;
					for (n = 0; n < Lessons[j].assistants.size(); n++)
						if (Students[StudentkeyID].PersonalLessons[i].assistants[0] == Lessons[j].assistants[n])//助教还在
							goto B;
					if (n == Lessons[j].assistants.size()) {  //助教不在了
						Students[StudentkeyID].PersonalLessons[i].assistants[0] = "NULL";
						personalstudentVector2File();//更新我的课表
						flag = 1;
					}
				}
			}
		}
	B:;
	}
	if (flag == 1) return true;
	else return false;
}
void DropmyAssistant(){  //退选助教
	cout << "请输入需要退选助教的课程ID：";
	string keyLessonID;
	cin >> keyLessonID;
	size_t i;
	for (i = 0; i < Students[StudentkeyID].PersonalLessons.size(); i++){
		if (Students[StudentkeyID].PersonalLessons[i].LessonID == keyLessonID){
			if (Students[StudentkeyID].PersonalLessons[i].assistants[0] != "NULL"){
				Students[StudentkeyID].PersonalLessons[i].assistants[0] = "NULL";
				personalstudentVector2File(); //更新个人课程文件
				cout << "已成功退选该助教！请按任意键返回学生菜单！" << endl;
				system("pause");
				studentpage();
			}
			else{
				cout << "你尚未选择该课程的助教！退选失败，请按任意键返回学生菜单！" << endl;
				system("pause");
				studentpage();
			}
			break;
		}
	}
	if (i == Students[StudentkeyID].PersonalLessons.size()){
		cout << "你尚未选择该门课！无法退选，请按任意键返回学生菜单！" << endl;
		system("pause");
		studentpage();
	}
}