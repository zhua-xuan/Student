#include"Head.h"
#define AdminID "Admin"
#define AdminP "admin"
void movecursor(int x, int y){
	HANDLE hout;
	COORD pos = { x, y };
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, pos);
}
bool AdministratorLogion(){ //����Ա��¼
	cout << "�������ԱID��" << endl;
	cout << "�������Ա���룺" << endl;
	string Admin, Password;
	movecursor(13, 7);
	cin >> Admin;
	movecursor(15, 8);
	cin >> Password;
	if (Admin == AdminID&&Password == AdminP){
		cout << "*************��¼�ɹ���*************";
		system("pause");
		return true;
	}
	else{
		cout << "*************�û�����������󣬵�¼ʧ�ܣ��밴�����������ѡ�����*************" << endl;
		system("pause");
		system("cls");
		cout << "������������������������������������������������������" << endl << endl;
		cout << "      ";
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED);
		cout << "1.ѧ����¼";
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "    ";
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED);
		cout << "2.ѧ��ע��";
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "    ";
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED);
		cout << "3.����Ա��¼";
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "    " << endl << endl;
		cout << "������������������������������������������������������" << endl << endl << endl;
		AdministratorLogion();
	}
}

bool StudentSignin(){//ѧ��ע��
	//�ȶ�һ��students�ļ�¼��Students��
	studentsFile2Students();
	cout << "����ѧ��ID��" << endl << "����ѧ���������룺";
	StudentsInformation temp;
	movecursor(11, 7);
	cin >> temp.StudentID;
	movecursor(17, 8);
	cin >> temp.Password;
	int i; //���Ƿ��Ѿ����ڴ�ѧ��
	for (i = 0; i < Students.size(); i++){
		if (Students[i].StudentID == temp.StudentID){
			cout << "��ѧ��ID�Ѵ��ڣ�ע��ʧ�ܣ�";
			cout << "�밴������������˵�" << endl;
			system("pause");
			system("cls");
			return false;
		}
	}
	if (i == Students.size()){ //δע���
		StudentkeyID = i;   //StudentKeyID��ȫ����������¼���ѧ���±�
		Students.push_back(temp);
		studentVector2File();            //����ѧ���б�
		personalstudentVector2File();  //����ѧ��ID�ļ�
		cout << "***********ע��ɹ�����¼�ɹ���***********" << endl;
		cout << "�밴���������ѧ���˵�" << endl;
		system("pause");
		return true;
	}
}
void studentVector2File(){//ѧ��ϵͳ�У���vectorѧ�����ݵ�ID���������students�ļ�
	ofstream fp("students.txt", ios::out);
	if (!fp){
		cerr << "�ļ���ʧ�ܣ�" << endl;
		exit(-1);
	}
	for (int i = 0; i < Students.size(); i++){
		string secretpassword = Students[i].Password; //��������
		for (size_t j = 0; j < Students[i].Password.size(); j++){
			secretpassword[j] = ~secretpassword[j] + 95;
		}
		fp << Students[i].StudentID << " ";
		fp << secretpassword;
		fp << endl;
	}
	fp.close();
}
void personalstudentVector2File(){
	string fileStudentkeyID = Students[StudentkeyID].StudentID;
	fileStudentkeyID += ".txt";
	ofstream fp(fileStudentkeyID,ios::out);
	if (!fp){
		cerr << "�ļ���ʧ�ܣ�" << endl;
		exit(-1);
	}
	for (size_t j = 0; j < Students[StudentkeyID].PersonalLessons.size(); j++){
		fp << Students[StudentkeyID].PersonalLessons[j].LessonID << " ";
		fp << Students[StudentkeyID].PersonalLessons[j].assistants[0];
		fp << endl;
	}
	fp.close();
}
void studentsFile2Students(){
	ifstream fp("students.txt", ios::in);
	if (!fp){
		cout << "�ļ���ʧ��" << endl;
		exit(-1);
	}
	if (!fp.eof()){   //���students�ļ���Ϊ��
		if (Students.size() == 0){  //���δ���ļ�������
			while (!fp.eof()){
				StudentsInformation temp;
				string coverpassword;
				fp >> temp.StudentID;
				fp >> coverpassword;
				for (size_t j = 0; j <coverpassword.size(); j++){ //����
					coverpassword[j] = coverpassword[j] - 95;
					coverpassword[j] = ~coverpassword[j];
				}
				temp.Password = coverpassword;
				Students.push_back(temp);
			}
			Students.pop_back();
		}
	}
	fp.close();
}
bool StudentLogin(){//ѧ����¼
	studentsFile2Students();  //����ѧ���б�
	cout << "����ѧ��ID��" << endl << "����ѧ���������룺";
	StudentsInformation temp;
	movecursor(11, 7);
	cin >> temp.StudentID;
	movecursor(17, 8);
	cin >> temp.Password;
	size_t i;
	for (i = 0; i < Students.size(); i++){
		if (Students[i].StudentID == temp.StudentID&&Students[i].Password == temp.Password){
			StudentkeyID = i;
			personalstudentFile2Vector();  //�����˿α���Ϣ¼��Students[StudentkeyID].PersonalLessons
			cout << "**********��¼�ɹ����밴���������ѧ���˵�**********" << endl;
			system("pause");
			return true;
		}
	}
	if (i == Students.size()){
		cout << "��¼ʧ�ܣ��û������������!�밴��������ص�¼ҳ��" << endl;
		system("pause");
		system("cls");
		return false;
	}
}
void personalstudentFile2Vector(){
	string fileStudentkeyID = Students[StudentkeyID].StudentID;
	fileStudentkeyID += ".txt";
	ifstream fp(fileStudentkeyID, ios::in);
	if (!fp){
		cerr << "�ļ���ʧ��" << endl;
		exit(-1);
	}
	if (Students[StudentkeyID].PersonalLessons.size() == 0){//û�ж�����
		while (!fp.eof()){
			LessonsInformation temp; string tempassistant;
			fp >> temp.LessonID;
			fp >> tempassistant;
			temp.assistants.push_back(tempassistant);
			Students[StudentkeyID].PersonalLessons.push_back(temp);
		}
		Students[StudentkeyID].PersonalLessons.pop_back();
	}
	fp.close();
}

void assistantsVector2File(){
	ofstream fp("assistants.txt", ios::out);
	if (!fp){
		cerr << "�ļ���ʧ��" << endl;
		exit(-1);
	}
	for (size_t i = 0; i < Lessons.size();){
		if (Lessons[i].assistants.size() == 0) i++;
		else{
			fp << Lessons[i].LessonID << " ";
			for (size_t j = 0; j < Lessons[i].assistants.size(); j++){
				if (j == Lessons[i].assistants.size() - 1)
					fp << Lessons[i].assistants[j];
				else fp << Lessons[i].assistants[j] << ",";
			}
			fp << endl;
			i++;
		}
	}
	fp.close();
}

void assistantsFile2Vector(){
	ifstream fp("assistants.txt", ios::in);
	if (!fp){
		cerr << "�ļ���ʧ��" << endl;
		exit(-1);
	}
	while (!fp.eof()){
		string LessonID;
		fp >> LessonID;
		for (size_t i = 0; i < Lessons.size(); i++)
			if (Lessons[i].LessonID == LessonID&&Lessons[i].assistants.size()==0) {
				string assistants;
				fp >> assistants;
				SplitString(assistants, Lessons[i].assistants, ",");
				break;
			}
	}
	fp.close();
}

void SplitString(const string &s,vector<string>&v, const string &c){
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2){
		v.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length()) v.push_back(s.substr(pos1));
}

void StudentLogout(){//ѧ��ע��
	cout << "�밴��������ص�¼����" << endl;  //Ҫ���ѧ�����˿α�����пεı�
	Students[StudentkeyID].PersonalLessons.clear();
	Lessons.clear();
	Students.clear();
	system("pause");
	system("cls");
	mainpage();
}
void AdministratorLogout(){//����Աע��
	cout << "�밴��������ص�¼����" << endl;
	Lessons.clear();
	Students.clear();
	system("pause");
	system("cls");
	mainpage();
}

void StudentChangePassword(){
	C:cout << "������ԭ���룺";
	string oldpassword;
	cin >> oldpassword;
	if (oldpassword == Students[StudentkeyID].Password){
		cout << "�����������룺";
		string newpassword;
		cin >> newpassword;
		if (newpassword == oldpassword){
			cout << "��ԭ������ͬ���޸�ʧ�ܣ��밴���������ѧ���˵���" << endl;
			system("pause");
			studentpage();
		}
		else{
			Students[StudentkeyID].Password = newpassword;
			studentVector2File();
			cout << "*********�޸�����ɹ���************" << endl;
			cout << "�밴��������ص�¼�˵����µ�¼��" << endl;
			system("pause");
			system("cls");
			mainpage();
		}
	}
	else {
		cout << "ԭ�����������" << endl;
		goto C;
	}
}