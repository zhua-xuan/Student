#include"Head.h"
void DeleteLesson(){
	if (!ifInitializationCourse()){
		cout << "�γ̻�δ��ʼ������!�밴��������ز˵�" << endl;
		system("pause");
		adminpage();
	}
	else{
		cout << "������γ̱�ţ�";
		string keyID;
		cin >> keyID;
		int i;
		for (i = 0; i < Lessons.size(); i++){
			if (Lessons[i].LessonID == keyID){
				if (Lessons[i].NowNop) { 
					cout << "�ÿγ�����ѧ��ѡ�����޷�ɾ��!�밴��������ع���Աҳ��" << endl;
					system("pause");
					adminpage();
				}
				else{
					Lessons.erase(Lessons.begin() + i);
					lessonVector2File();
					cout << "ɾ���˿γ̳ɹ����밴��������ع���Աҳ��" << endl;
					system("pause");
					adminpage();
				}
			}
		}
		if (i == Lessons.size()) {
			cout << "�ÿγ̲����ڣ�ɾ��ʧ��" << endl;
			cout << "�밴��������ع���Աҳ��" << endl;
			system("pause");
			adminpage();
		}
	}
}