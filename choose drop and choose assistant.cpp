#include"Head.h"
void ChooseLesson(){
	if (CountmyLessons() == 10){
		cout << "�Ѵ�ѡ�����ޣ��޷���ѡ�Σ��밴���������ѧ���˵�" << endl;
		system("pause");
		studentpage();
	}
	else{
		cout << "����γ�ID��";
		string keylessonID;   //Ҫ��ӵĿε�ID
		cin >> keylessonID;
		size_t n;  //��ѧ���γ��б������޴˿�
		for (n = 0; n < Students[StudentkeyID].PersonalLessons.size(); n++){
			if (Students[StudentkeyID].PersonalLessons[n].LessonID == keylessonID) {
				cout << "���ʧ�ܣ��ÿγ��Ѵ��ڣ��밴���������ѧ���˵�" << endl;
				system("pause");
				studentpage();
			}
		}
		if (n == Students[StudentkeyID].PersonalLessons.size()){ //��δѡ�������
			size_t m;
			for (m = 0; m < Lessons.size(); m++){
				if (Lessons[m].LessonID == keylessonID){
					if (Lessons[m].NowNop < Lessons[m].MaxNoP){
						Students[StudentkeyID].PersonalLessons.push_back(Lessons[m]);
						Students[StudentkeyID].PersonalLessons[Students[StudentkeyID].PersonalLessons.size() - 1].assistants.resize(0);
						Students[StudentkeyID].PersonalLessons[Students[StudentkeyID].PersonalLessons.size()-1].assistants.push_back("NULL");
						Lessons[m].NowNop++;
						BubblesortmyLessons();
						personalstudentVector2File();//�޸ĸ��˿α��ļ�
						lessonVector2File();//����currentcourse�ļ�
						cout << "**********����ӵ����˿α��У�**********" << endl;
						break;
					}
					else {
						cout << "�����Ѵ����ޣ��޷���ӣ��밴���������ѧ���˵�" << endl;
						system("pause");
						studentpage();
					}
				}
			}
			if (m == Lessons.size()) {
				cout << "�����ڴ˿γ�,���ʧ�ܣ��밴���������ѧ���˵�" << endl;
				system("pause");
				studentpage();
			}
			else{
				cout << "�밴���������ѧ���˵�" << endl;
				system("pause");
				studentpage();
			}
		}
	}
}
void BubblesortmyLessons(){       // ���˿γ��б�γ���Ϣʼ�հ��γ�ID������ʾ
	for (size_t i = 0; i < Students[StudentkeyID].PersonalLessons.size() - 1; ++i)
		for (size_t j = 0; j < Students[StudentkeyID].PersonalLessons.size() - 1 - i; ++j)
			if (Students[StudentkeyID].PersonalLessons[j].LessonID>Students[StudentkeyID].PersonalLessons[j + 1].LessonID){
				swap(Students[StudentkeyID].PersonalLessons[j],Students[StudentkeyID].PersonalLessons[j + 1]);
			}
}
int CountmyLessons(){//����һ�����ſ�
	pcourse = 0; npcourse = 0;
	for (size_t n = 0; n < Students[StudentkeyID].PersonalLessons.size(); n++){
		for (size_t m = 0; m < Lessons.size(); m++){
			if (Students[StudentkeyID].PersonalLessons[n].LessonID == Lessons[m].LessonID){
				if (Lessons[m].LessonType == "רҵ��")
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
	cout << "����γ�ID��γ����ƣ�";
	string keyLesson;
	cin >> keyLesson;
	size_t i;  //�ڿγ��б���±�
	for (i = 0; i < Lessons.size(); i++){
		if (Lessons[i].LessonID == keyLesson || Lessons[i].LessonName == keyLesson)
			break;
	}
	if (i == Lessons.size()) {
		cout << "���ſβ����ڣ��밴���������ѧ���˵�" << endl;
		system("pause");
		studentpage();
	}
	else{   //���ſδ���
		size_t j;
		for (j = 0; j < Students[StudentkeyID].PersonalLessons.size(); j++){
			if (Students[StudentkeyID].PersonalLessons[j].LessonID == Lessons[i].LessonID){ //���ѡ�����ſ�
				Students[StudentkeyID].PersonalLessons.erase(Students[StudentkeyID].PersonalLessons.begin() + j);
				Lessons[i].NowNop--;
				lessonVector2File();//����Lessons�ļ�
				personalstudentVector2File(); //���¸��˿α�
				for (size_t n = 0; n < Lessons[i].assistants.size(); n++){
					if (Lessons[i].assistants[n] == Students[StudentkeyID].StudentID){
						Lessons[i].assistants.erase(Lessons[i].assistants.begin() + n);
						assistantsVector2File(); //����assistants�ļ�
						break;
					}
					//�´���ʾĳѧ���������˿�
				}
				cout << "�γ�ɾ���ɹ���" << endl;
				SearchPersonalLesson(); //�鿴���˿α�
			}
		}
		if (j == Students[StudentkeyID].PersonalLessons.size()){
			cout << "��δѡ���ſΣ�ɾ��ʧ�ܣ��밴���������ѧ���˵�" << endl;
			system("pause");
			studentpage();
		}
	}
}
void SignForAssistant(){  //���ֱ�������
	if (CountforOtherAssistant() == 2){
		cout << "�Ѵﵽ�����������ޣ��밴���������ѧ���˵�" << endl;
		system("pause");
		studentpage();
	}
	else{  //δ������
		cout << "�����Ӧ�γ�ID��γ����ƣ�";
		string keyLesson;
		cin >> keyLesson;
		size_t i;  //�ڿγ��б���±�
		for (i = 0; i < Lessons.size(); i++){
			if (Lessons[i].LessonID == keyLesson || Lessons[i].LessonName == keyLesson)
				break;
		}
		if (i == Lessons.size()) {
			cout << "���ſβ����ڣ��밴���������ѧ���˵�" << endl;
			system("pause");
			studentpage();
		}
		else{  //���пγ��������ſ�
			size_t j;
			for (j = 0; j < Students[StudentkeyID].PersonalLessons.size();){ //���ѧ���α������ſ�
				if (Students[StudentkeyID].PersonalLessons[j].LessonID == Lessons[i].LessonID){
					vector<string>::iterator it = find(Lessons[i].assistants.begin(), Lessons[i].assistants.end(), Students[StudentkeyID].StudentID);
					if (it != Lessons[i].assistants.end()){  //�Ѿ����������ſ�����
						cout << "���ѱ������ſ����̣��޷��ظ��������밴���������ѧ���˵�" << endl;
						system("pause");
						studentpage();
					}
					else{ //û�������ſ�����
						Lessons[i].assistants.push_back(Students[StudentkeyID].StudentID);  //����Lessons�����б�
						assistantsVector2File();  //���������ļ�
						cout << "�������̳ɹ����밴���������ѧ���˵�" << endl;
						system("pause");
						studentpage();
					}
				}
				else j++;
			}
			if (j == Students[StudentkeyID].PersonalLessons.size()){
				cout << "��δѡ�����ſΣ���������ʧ�ܣ��밴���������ѧ���˵�" << endl;
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
void ChoosemyLessonAssistant(){//ѡ��ĳ�ſε�����
	cout << "����γ�ID��γ����ƣ�";
	string keyLesson;
	cin >> keyLesson;
	size_t i;  //�ڿγ��б���±�
	for (i = 0; i < Lessons.size(); i++){
		if (Lessons[i].LessonID == keyLesson || Lessons[i].LessonName == keyLesson)
			break;
	}
	if (i == Lessons.size()) {
		cout << "���ſβ����ڣ��밴���������ѧ���˵�" << endl;
		system("pause");
		studentpage();
	}
	else{  //���ſ���Lessons����
		size_t j;  //�ڸ��˿γ̱���±�
		for (j = 0; j < Students[StudentkeyID].PersonalLessons.size(); j++){
			if (Students[StudentkeyID].PersonalLessons[j].LessonID == Lessons[i].LessonID){  //���ſ���ѡ��
				if (CountmyLessonAssistant(j)){  //ѡ��������
					cout << "����ѡ��ÿγ����̣��޷�����ѡ���밴���������ѧ���˵�" << endl;
					system("pause");
					studentpage();
				}
				else{  //ûѡ������
					size_t n = Lessons[i].assistants.size();
					if (n == 0){
						cout << "�ÿγ��������̣��޷�ѡ���밴���������ѧ���˵�" << endl;
						system("pause");
						studentpage();
					}
					else{  //���ſ�������
						cout << "Ŀǰ���ſε������У�";
						for (n = 0; n < Lessons[i].assistants.size(); n++){
							if (n == Lessons[i].assistants.size() - 1)
								cout << Lessons[i].assistants[n];
							else cout << Lessons[i].assistants[n] << ",";
						}
						cout << endl << "���������������У�ѡ����ĸ������̣�";
						string myassistant;
						cin >> myassistant;
						//vector<string>::iterator it = find(Lessons[i].assistants.begin(), Lessons[i].assistants.end(), myassistant);
						size_t n;
						for (n = 0; n < Lessons[i].assistants.size(); n++){
							if (Lessons[i].assistants[n]==myassistant){  //�ÿγ����������
								if (Students[StudentkeyID].StudentID == myassistant){
									cout << "�޷�ѡ���Լ���Ϊ���̣��밴���������ѧ���˵�" << endl;
									system("pause");
									studentpage();
								}
								else{
									Students[StudentkeyID].PersonalLessons[j].assistants.erase(Students[StudentkeyID].PersonalLessons[j].assistants.begin());
									Students[StudentkeyID].PersonalLessons[j].assistants.push_back(myassistant);
									personalstudentVector2File(); //����ѧ�������ļ�
									cout << "����ɸ�������ѡ���밴���������ѧ���˵�" << endl;
									system("pause");
									studentpage();
								}
							}
						}
						if (n == Lessons[i].assistants.size()){
							cout << "�ÿγ��޴����̣��밴���������ѧ���˵�" << endl;
							system("pause");
							studentpage();
						}
					}
				}
			}
		}
		if (j == Students[StudentkeyID].PersonalLessons.size()){  //���ſ���ûѡ
			cout << "��δѡ����ſΣ��밴���������ѧ���˵�" << endl;
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
		if (Students[StudentkeyID].PersonalLessons[i].assistants[0] == "NULL"); //������û����
		else{ //���ſα���������
			for (size_t j = 0; j < Lessons.size();j++){
				if (Students[StudentkeyID].PersonalLessons[i].LessonID == Lessons[j].LessonID){ //�ҵ����ѧ����������ڿγ��б���±�
					size_t n;
					for (n = 0; n < Lessons[j].assistants.size(); n++)
						if (Students[StudentkeyID].PersonalLessons[i].assistants[0] == Lessons[j].assistants[n])//���̻���
							goto B;
					if (n == Lessons[j].assistants.size()) {  //���̲�����
						Students[StudentkeyID].PersonalLessons[i].assistants[0] = "NULL";
						personalstudentVector2File();//�����ҵĿα�
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
void DropmyAssistant(){  //��ѡ����
	cout << "��������Ҫ��ѡ���̵Ŀγ�ID��";
	string keyLessonID;
	cin >> keyLessonID;
	size_t i;
	for (i = 0; i < Students[StudentkeyID].PersonalLessons.size(); i++){
		if (Students[StudentkeyID].PersonalLessons[i].LessonID == keyLessonID){
			if (Students[StudentkeyID].PersonalLessons[i].assistants[0] != "NULL"){
				Students[StudentkeyID].PersonalLessons[i].assistants[0] = "NULL";
				personalstudentVector2File(); //���¸��˿γ��ļ�
				cout << "�ѳɹ���ѡ�����̣��밴���������ѧ���˵���" << endl;
				system("pause");
				studentpage();
			}
			else{
				cout << "����δѡ��ÿγ̵����̣���ѡʧ�ܣ��밴���������ѧ���˵���" << endl;
				system("pause");
				studentpage();
			}
			break;
		}
	}
	if (i == Students[StudentkeyID].PersonalLessons.size()){
		cout << "����δѡ����ſΣ��޷���ѡ���밴���������ѧ���˵���" << endl;
		system("pause");
		studentpage();
	}
}