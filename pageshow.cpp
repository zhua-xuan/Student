#include"Head.h"
BOOL SetConsoleColor(WORD wAttributes)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
		return FALSE;
	return SetConsoleTextAttribute(hConsole, wAttributes);
}
void mainShow(){  //�������չʾ
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "������������������������������������������������������" << endl << endl;
	cout << "      ";
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE| BACKGROUND_RED);
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
	cout << "    "<< endl << endl;
	cout << "������������������������������������������������������" << endl << endl;
	cout << "�����������";
}
void adminShow(){ //����Ա�˵���ʾ
	system("cls");
	system("color A");
	cout << "����������������������������������������������������������������������������������������������������������������������" << endl;
	cout << "1.ע����¼    2.��ʼ���γ���Ϣ    3.�鿴ȫ���γ���Ϣ    4.���ӿγ�    5.ɾ���γ�    6.�޸Ŀγ�    7.�鿴����γ�" << endl;
	cout << "����������������������������������������������������������������������������������������������������������������������" << endl;
	cout << "��ѡ�����蹦�ܣ�";
}
void studentShow(){ //ѧ���˵���ʾ
	system("cls");
	system("color A");
	cout << "����������������������������������������������������������������������������������������������������������������������" << endl;
	cout << "1.ע����¼    2.�鿴�γ���Ϣ    3.ѡ��    4.�鿴���˿α�    5.�˿�   6.���ֱ�������   7.ѡ���������   8.��ѡ��������" << endl;
	cout << "9.�鿴����ѧ������     10.�޸�����" << endl;
	cout << "����������������������������������������������������������������������������������������������������������������������" << endl;
	cout << "��ѡ�����蹦�ܣ�";
}