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
			cout << "<1.登录> or <2.注册>" << endl;
			cout << "请选择进行的操作:";
			cin >> n;
			while (n != "1" && n != "2") {
				cout << "请输入正确的操作数(1 or 2) :";
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
	cout << "您好！" << u.getname();
	if (u.getsex() == "男") cout << "先生" << endl;
	else cout << "女士" << endl;
	cout << "******************\n";
	cout << "<1.点餐>   <2.查询订单>   <3.个人信息>   <4.退出登录>" << endl;
	cout << "请选择进行的操作:";
	cin >> n;
	system("cls");
	return n;
}