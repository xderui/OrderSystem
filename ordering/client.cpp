#include<iostream>
#include<string.h>
#include<stdio.h>
#include "User.h"
#include "login_register.h"
#include "order.h"
using namespace std;
int main() {
	string welcome(User u);
	while (1) {
		User user;
		while (1) {
			string n;
			cout << "<1.��¼> or <2.ע��>" << endl;
			cout << "��ѡ����еĲ���:";
			cin >> n;
			while (n != "1" && n != "2") {
				cout << "��������ȷ�Ĳ�����(1 or 2) :";
				cin >> n;
			}
			if (n == "1") {
				user = user_login();
				break;
			}
			if (n == "2") user_register();
		}

		while (1) {
			string n;
			n = welcome(user);
			if (n == "1") showmenu(user);
			if (n == "2") queryorder(user.getuser_name());
			if (n == "3") personalinfo(user);
			if (n == "4") break;
		}
	}
	return 0;
}

string welcome(User u) {
	string n;
	cout << "******************\n";
	cout << "���ã�" << u.getname();
	if (u.getsex() == "��") cout << "����" << endl;
	else cout << "Ůʿ" << endl;
	cout << "******************\n";
	cout << "<1.���>   <2.��ѯ����>   <3.������Ϣ>   <4.�˳���¼>" << endl;
	cout << "��ѡ����еĲ���:";
	cin >> n;
	system("cls");
	return n;
}