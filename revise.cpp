#include"Head.h"
void ReviseTeacherName(int i){
	cout << "�����޸�Ϊ��";
	cin >> Lessons[i].TeacherName;
	lessonVector2File();
	cout << "�޸ĳɹ���" << endl;
	cout << "�밴��������ع���Ա�˵�" << endl;
	system("pause");
	adminpage();
}
void ReviseMaxNop(int i){
	cout << "�����޸�Ϊ��";
	int newNop;
	cin >> newNop;
	if (newNop < Lessons[i].NowNop) {
		cout << "�޸�ʧ�ܣ��޸ĺ����������С��Ŀǰ��ѡ������" << endl;
		cout << "�밴��������ع���Ա�˵�" << endl;
		system("pause");
		adminpage();
	}
	else {
		Lessons[i].MaxNoP = newNop;
		lessonVector2File();
		cout << "�޸ĳɹ���" << endl;
		cout << "�밴��������ع���Ա�˵�" << endl;
		system("pause");
		adminpage();
	}
}
void mainReviseLesson(){
	if (!ifInitializationCourse()){
		cout << "�γ̻�δ��ʼ������!�밴��������ز˵�" << endl;
		system("pause");
		adminpage();
	}
	else{
		cout << "��Ҫ�޸ĵĿγ�ID��";
		string keyID;
		cin >> keyID;
		int i;
		for (i = 0; i < Lessons.size(); i++){
			if (Lessons[i].LessonID == keyID){
				cout << "��Ҫ�޸ĵľ����ֶΣ�1.�ڿν�ʦ����   2.�������� ����������1��2����";
				int k;
				cin >> k;
				while (k != 1 && k != 2){
					cout << "�������������1��2:";
					cin >> k;
				}
				if (k == 1) ReviseTeacherName(i);
				else ReviseMaxNop(i);
			}
		}
		if (i == Lessons.size()) {
			cout << "�޸�ʧ�ܣ��ÿγ̲����ڣ�" << endl;
			cout << "�밴��������ع���Ա�˵�" << endl;
			system("pause");
			adminpage();
		}
	}
}