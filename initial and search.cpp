#include"Head.h"
void InitializationCourse(){  //��ʼ���γ��ļ�
	cout << "��������Ҫ������ļ����ƣ�";
	string initial; //�����ļ�������
	cin >> initial;
	while (initial != "defaultcourse.txt"){
		cout << "δ�ҵ����ļ���������������:";
		cin >> initial;
	}
	ifstream fp("defaultcourse.txt", ios::in);
	if (!fp){
		cerr << "�ļ���ʧ�ܣ�" << endl;
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
	cout << "��ʼ���ɹ���" << endl;
	cout << "�밴��������ع���Ա�˵�" << endl;
	system("pause");
	adminpage();
}
void lessonVector2File(){   //��Lessons����currentcourse
	ofstream fp2("currentcourse.txt", ios::out);
	if (!fp2){
		cerr << "�ļ���ʧ�ܣ�" << endl;
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


void SearchCertainLesson(){  //�鿴����ĳ�ſ�
	if (!ifInitializationCourse()){
		system("pause");
		adminpage();
	}
	else{
		cout << "������Ҫ�鿴�Ŀγ�ID�����ƣ�";
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
			cout << "�鿴ʧ�ܣ�û���ҵ��˿γ̣�" << endl;
			cout << "�밴��������ع���Ա�˵�" << endl;
			system("pause");
			adminpage();
		}
		else{
			cout << "��ϣ�������������������1.�鿴ѡ��ѧ������   2.�鿴�γ̱�����������" << endl;
			cout << "���������ţ�";
			string k;
			cin >> k;
			while (k != "1"&&k != "2"){
				cout << "�޷���ѯ���˹��ܣ����������룬1��2��" << endl;
				cin >> k;
			}
			if (k =="1") StudentsforLesson(i);
			else if (k == "2"){
				assistantsFile2Vector();
				if (Lessons[i].assistants.size() == 0){
					cout << "�˿��������̣��밴��������ع���Ա�˵�" << endl;
				}
				else{
					cout << "Ŀǰ�������ſε������У�";
					for (int j = 0; j < Lessons[i].assistants.size(); j++)
						cout << Lessons[i].assistants[j] << " ";
					cout << endl << "�밴��������ع���Ա�˵�" << endl;
				}
				system("pause");
				adminpage();
			}
		}
	}
} 

void StudentsforLesson(int i){ //�������ſε�ѧ����
	if (Lessons[i].NowNop != 0){
		studentsFile2Students();  //����ѧ���б�
		cout << "Ŀǰѡ����ſε�ѧ���У�";
		size_t n;
		for (n = 0; n < Students.size(); n++){
			StudentkeyID = n;
			personalstudentFile2Vector(); //����ͬѧ�γ̱�
			for (size_t j = 0; j < Students[n].PersonalLessons.size(); j++)
				if (Students[n].PersonalLessons[j].LessonID == Lessons[i].LessonID)
					cout << Students[n].StudentID << " ";
		}
		cout << endl;
	}
	cout <<"����" << Lessons[i].NowNop << "��ѧ�����������λ���" << Lessons[i].MaxNoP - Lessons[i].NowNop << "�ˣ�";
	cout << "�밴��������ع���Ա�˵�" << endl;
	system("pause");
	adminpage();
}

void adminSearchAllLessons(){
	if (!ifInitializationCourse()){
		cout << "�γ̻�δ��ʼ������!�밴��������ز˵�" << endl;
		system("pause");
		adminpage();
	}
	else{
		cout << "****************************************************************************************" << endl;
		cout << setiosflags(ios::left);
		cout << setw(12)<<"�γ�ID" << setw(22)<<"�γ�����" <<setw(16)<< "�ڿν�ʦ" <<setw(12)<< "��������" <<setw(12)<< "Ŀǰ��ѡ" <<setw(12)<< "�γ�����" << endl;
		for (int i = 0; i < Lessons.size(); i++){
			cout << setw(12) << Lessons[i].LessonID << setw(22) << Lessons[i].LessonName;
			cout << setw(16) << Lessons[i].TeacherName << setw(12) << Lessons[i].MaxNoP;
			cout << setw(12) << Lessons[i].NowNop << setw(12) << Lessons[i].LessonType << endl;
		}
		cout << "****************************************************************************************" << endl;
		cout << "�밴��������ع���Ա�˵�" << endl;
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
		cout << setw(12) << "�γ�ID" << setw(22) << "�γ�����" << setw(16) << "�ڿν�ʦ" << setw(12) << "��������" << setw(12) << "Ŀǰ��ѡ" << setw(12) << "�γ�����" << endl;
		for (int i = 0; i < Lessons.size(); i++){
			cout << setw(12) << Lessons[i].LessonID << setw(22) << Lessons[i].LessonName;
			cout << setw(16) << Lessons[i].TeacherName << setw(12) << Lessons[i].MaxNoP;
			cout << setw(12) << Lessons[i].NowNop << setw(12) << Lessons[i].LessonType << endl;
		}
		cout << "****************************************************************************************" << endl;
		cout << "�밴���������ѧ���˵�" << endl;
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
		if (Lessons.size() == 0){  //û����Lessons��
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

void  SearchPersonalLesson(){ //�鿴���˿α�
	personalstudentFile2Vector();
	cout << "Ŀǰ��ѡ�γ��У�" << endl;
	cout << "*****************************************************************************************" << endl;
	cout << setiosflags(ios::left);
	cout << setw(12) << "�γ�ID" << setw(22) << "�γ�����" << setw(18) << "�ڿν�ʦ" << setw(18) << "�γ�����" << setw(18) << "��������"<< endl;
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
			cout << "����ѧԺҪ��Ŀǰ��ѡ�γ�������꣡�Բ�" << P - pcourse << "��רҵ�Σ��Լ�" << NP - npcourse << "�ŷ�רҵ�Σ��뼰ʱѡ�Σ�" << endl;
		else
			cout << "����ѧԺҪ��Ŀǰ��ѡ�γ�������꣡�Բ�" << P - pcourse << "��רҵ��"<<endl;
	}
	else if (npcourse<2)
		cout << "����ѧԺҪ��Ŀǰ��ѡ�γ�������꣡�Բ�" << NP - npcourse << "�ŷ�רҵ�Σ��뼰ʱѡ�Σ�" << endl;
	cout << "�밴���������ѧ���˵�" << endl;
	system("pause");
	studentpage();
}
void SearchmyStudents(){  //�鿴�Լ���Ϊ���̵�ѧ��
	int temp; //���汾��ѧ���б��±�
	temp = StudentkeyID;
	if (CountforOtherAssistant() == 0) //û����������
		cout << "   ����δ���������̣��밴���������ѧ���˵���" << endl;
	else{  //����������һ��
		cout << "Ŀǰ�������̵Ŀγ��У�";
		cout << Lessons[lessonmark1].LessonID << " ";
		if (lessonmark2 != -1) cout << Lessons[lessonmark2].LessonID << endl;
		else cout << endl;
		cout << "���������ѯ�Ŀγ�ID��";
		string keyLessonID;
		cin >> keyLessonID;
		if (keyLessonID == Lessons[lessonmark1].LessonID || (lessonmark2 != -1 && keyLessonID == Lessons[lessonmark2].LessonID)){//�����ѯ�����������ſ�֮һ
			cout << "���ſ�ѡ������Ϊ���̵�ѧ���У�";
			int flag = 0;//���Ƿ���ѧ��ѡ��
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
			if (flag == 0) cout << "��";
			cout << endl << "�밴���������ѧ���˵���" << endl;
		}
		else
			cout << "����Ŀγ�ID�����밴���������ѧ���˵���" << endl;
	}
	StudentkeyID = temp;// ��StudentkeyID����ȥ
	system("pause");
	studentpage();
}
