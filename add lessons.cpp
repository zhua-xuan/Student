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
		cout << "�γ̻�δ��ʼ������!�밴��������ز˵�" << endl;
		system("pause");
		adminpage();
	}
	else{
		cout << "��������Ҫ��ӵĿγ̸�����";
		int n; cin >> n;
		for (int i = 0; i < n; i++){
			cout << "������γ̾�����Ϣ(��ͬ��Ϣ֮���Կո����,������������Ϊ���γ����ơ���ʦ����������������ѡ�������γ����ԣ�רҵ��/��רҵ�Σ������γ�1 ��ʦ1 60 0 רҵ�� ����";
			LessonsInformation temp;
		A:cin >> temp.LessonName >> temp.TeacherName >> temp.MaxNoP >> temp.NowNop >> temp.LessonType;
			int j;
			for (j = 0; j < Lessons.size(); j++){
				if (Lessons[j].LessonName == temp.LessonName&&Lessons[j].TeacherName == temp.TeacherName){
					cout << "�ÿγ��Ѵ��ڣ����ʧ�ܣ�����������(��ͬ��Ϣ֮���Կո��������";
					goto A;
				}
			}

			if (j == Lessons.size()){
				temp.LessonID = Lessons[j - 1].LessonID;
				temp.LessonID = LessonIDPlus(temp);
				Lessons.push_back(temp);
				cout << "�˿γ���ӳɹ���" << endl;
			}
		}
		cout << "���пγ���ӳɹ���" << endl;
		lessonVector2File();
		adminSearchAllLessons();
	}
}