#include"Head.h"
vector<LessonsInformation>Lessons;
vector<StudentsInformation>Students;
int StudentkeyID;  //��¼����ϵͳ��ѧ��ID�±�
int pcourse = 0, npcourse = 0, allcourse = 0;//����רҵ�κͷ�רҵ������
int lessonmark1 = -1, lessonmark2 = -1;
int main(){
	mainpage();
	return 0;
}
void mainpage(){  //�û������¼��ʽ
	mainShow();
	string LoginChoose;
	cin >> LoginChoose;
	if (LoginChoose=="3"){
		if (AdministratorLogion()) //��¼�ɹ���,��¼���ɹ��������Ƕ���ͣ��¼��
			adminpage();
	}
	else if (LoginChoose == "2"){
		if (StudentSignin())  //ѧ��ע��ɹ���
			studentpage();
		else mainpage();  //ע�᲻�ɹ����������˵�
	}
	else if (LoginChoose == "1"){
		if (StudentLogin())  //ѧ����¼�ɹ���
			studentpage();
		else mainpage();
	}
	else{
		cout << "**********ѡ����ʧ�ܣ��밴��������ص�¼���棬����1��2��3��**********" << endl;
		system("pause");
		system("cls");
		mainpage();
	}
}
void adminpage(){
	adminShow();
	string FunctionChoose;
	cin >> FunctionChoose;
	if (FunctionChoose =="1")
		AdministratorLogout();
	else if (FunctionChoose =="2") {
		if (ifInitializationCourse()){
			cout << "�γ��Ѿ���ʼ�����밴���������ѡ�������";
			system("pause");
			adminpage();//�ص�����Ա�˵�ѡ��
		}
		else InitializationCourse();
	}
	else if (FunctionChoose == "3")
		adminSearchAllLessons();
	else if (FunctionChoose == "4")
		mainLessonIDPlus();
	else if (FunctionChoose == "5")
		DeleteLesson();
	else if (FunctionChoose == "6")
		mainReviseLesson();
	else if (FunctionChoose == "7")
		SearchCertainLesson();
	else{
		cout << "**********ѡ����ʧ�ܣ��밴��������ع���Ա���棬��1��2��3��4��5��6��7��ѡ���������룡**********" << endl;
		system("pause");
		adminpage();
	}
}

void studentpage(){
	studentShow();
	string FunctionChoose;
	cin >> FunctionChoose;
	if (FunctionChoose == "1")
		StudentLogout();
	else if (!ifInitializationCourse()){ //���γ���Ϣ����Lessons
		cout << "����Ա��δ��ʼ�����밴���������ѧ���˵�" << endl;
		system("pause");
		studentpage();
	}
	else{
		assistantsFile2Vector();  //����������¼��Lessons�������б�
		if (ifmyassistantloss())
			cout << "��ѡ�γ��������˿Σ���ע��鿴" << endl;
		if (FunctionChoose == "2")
			studentSearchAllLessons();
		else if (FunctionChoose == "3")
			ChooseLesson();
		else if (FunctionChoose == "4")
			SearchPersonalLesson();
		else if (FunctionChoose == "5")
			DropLesson();
		else if (FunctionChoose == "6")
			SignForAssistant();
		else if (FunctionChoose == "7")
			ChoosemyLessonAssistant();
		else if (FunctionChoose == "8")
			DropmyAssistant();
		else if (FunctionChoose == "9")
			SearchmyStudents();
		else if (FunctionChoose == "10")
			StudentChangePassword();
		else{
			cout << "**********ѡ����ʧ�ܣ��밴���������ѧ�����棬��1��2��3��4��5��6��7��ѡ���������룡**********" << endl;
			system("pause");
			studentpage();
		}
	}
}