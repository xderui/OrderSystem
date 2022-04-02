#ifndef LOGIN_REGISTER_H
#define LOGIN_REGISTER_H
#include<cstdio>
#include<iostream>
#include<string.h>
#include<Winsock2.h>
#include<mysql.h>
#include<conio.h>
#include<windows.h>
#include "User.h"
using namespace std;
/*const char* host = "localhost";
const char* db_user = "root";
const char* db_pawd = "123456";*/
User user_login() {
	string usr_name, usr_pawd;
	char pw[30], ch;
	MYSQL login;
	MYSQL_RES* res;
	MYSQL_ROW row;
	mysql_init(&login);
	if (!mysql_real_connect(&login, host, db_user, db_pawd, "info", 3306, NULL, 0)) {
		cout << "连接失败" << endl;
	}
	mysql_set_character_set(&login, "utf8");
	mysql_query(&login, "SET NAMES GB2312");
	while (1) {
		cout << "用户名：";
		cin >> usr_name;
		cout << "密码：";
		int i = 0;
		while ((ch = _getch()) != '\r') {
			if (ch == '\b' && i > 0) {
				cout << "\b \b";
				i--;
			}
			else if (ch != '\b') {
				pw[i++] = ch;
				cout << "*";
			}
		}
		pw[i] = '\0';
		usr_pawd = pw;
		cout << endl;
		string sql1 = "select * from user where user_name='" + usr_name + "'";
		mysql_query(&login, sql1.c_str());
		res = mysql_store_result(&login);
		if (mysql_num_rows(res)) {
			row = mysql_fetch_row(res);
			if (row[2] == usr_pawd) {
				cout << "登录成功！正在加载";
				for (int i = 1; i <= 5; i++) {
					cout << ".";
					Sleep(1200 / i);
				}
				system("cls");
				return User(row[3], row[4], row[5], row[6], row[1]);
			}
			else cout << "密码错误，请重新输入！" << endl;
		}
		else cout << "用户名不存在，请重新输入！" << endl;
	}
}

void user_register() {
	string usr_name, usr_pawd_1, usr_pawd_2;
	char pw[30], ch;
	MYSQL reg;
	MYSQL_RES* res;
	string sql;
	mysql_init(&reg);
	if (!mysql_real_connect(&reg, host, db_user, db_pawd, "info", 3306, NULL, 0)) {
		cout << "连接失败！" << endl;
	}
	mysql_set_character_set(&reg, "utf8");
	while (1) {
		cout << "用户名：";
		cin >> usr_name;
		sql = "select * from user where user_name='" + usr_name + "'";
		mysql_query(&reg, sql.c_str());
		res = mysql_store_result(&reg);
		if (mysql_num_rows(res)) {
			cout << "注册终止！  原因：用户名已存在！\n";
			cout << "1.重新注册  2.返回   请选择：";
			int n;
			while (1) {
				cin >> n;
				if (n != 1 && n != 2) cout << "请选择1或2！：";
				else if (n == 2) {
					system("cls");
					return;
				}
				else break;
			}
		}
		else break;
	}
	while (1) {
		cout << "密码：";
		int i = 0;
		while ((ch = _getch()) != '\r') {
			if (ch == '\b' && i > 0) {
				cout << "\b \b";
				i--;
			}
			else if (ch != '\r') {
				pw[i++] = ch;
				cout << "*";
			}
		}
		pw[i] = '\0';
		usr_pawd_1 = pw;
		cout << "\n确认密码：";
		memset(pw, '\0', sizeof(pw));
		i = 0;
		while ((ch = _getch()) != '\r') {
			if (ch == '\b' && i > 0) {
				cout << "\b \b";
				i--;
			}
			else if (ch != '\r') {
				pw[i++] = ch;
				cout << "*";
			}
		}
		pw[i] = '\0';
		usr_pawd_2 = pw;
		cout << endl;
		if (usr_pawd_1 == usr_pawd_2) {
			//sql = "INSERT INTO user(user_name,password) VALUES('" + usr_name + "','" + usr_pawd_1 + "')";
			//cout << sql << endl;
			mysql_query(&reg, "SET NAMES GB2312");
			cout << "马上就要注册成功了，下面请完善个人信息" << endl;
			string name, tele, addr, sex;
			cout << "姓名：";
			cin >> name;
			cout << "性别：";
			cin >> sex;
			cout << "手机号码：";
			cin >> tele;
			cout << "地址：";
			cin >> addr;
			sql = "INSERT INTO user(user_name,password,name,sex,phone_number,address) VALUES('" + usr_name + "','" + usr_pawd_1 + "','" + name + "','" + sex + "','" + tele + "','" + addr + "')";
			if (!mysql_query(&reg, sql.c_str())) {
				cout << "注册成功，开始登录吧！" << endl;
				Sleep(3 * 1000);
				system("cls");
				return;
			}
			else {
				cout << "注册失败！" << mysql_error(&reg) << endl;
				user_register();
				break;
			}
		}
		else cout << "两次密码不一致，重新输入！" << endl;
	}
}
#endif

void user_test() {
	string usr_name, usr_pawd;
	char pw[30], ch;
	MYSQL login;
	MYSQL_RES* res;
	MYSQL_ROW row;
	mysql_init(&login);
	if (!mysql_real_connect(&login, host, db_user, db_pawd, "order", 3306, NULL, 0))
		cout << "连接失败" << endl;
	mysql_set_character_set(&login, "utf8");
	mysql_query(&login, "SET NAMES GB2312");
	string sql = "CREATE TABLE IF NOT EXISTS `test`  ( \
		`id` int AUTO_INCREMENT,\
		`store_name` text,\
		`scores` text,\
		`date` text,\
		PRIMARY KEY(`id`)\
		) ";
	if (!mysql_query(&login, sql.c_str())) {
		cout << "创建成功！" << endl;
	}
	else cout << mysql_error(&login) << endl;
	sql = "INSERT INTO test(store_name,scores,date) VALUES('火锅店','5.0','2020年7月10日')";
	if (!mysql_query(&login, sql.c_str())) {
		cout << "创建成功！" << endl;
	}
	else cout << mysql_error(&login) << endl;
	sql = "select * from  test";
	if (!mysql_query(&login, sql.c_str())) {
		cout << "创建成功！" << endl;
	}
	res = mysql_store_result(&login);
	cout << mysql_num_rows(res);
	while (row = mysql_fetch_row(res)) {
		cout << row[0] << row[1] << row[2] << row[3] << endl;
	}
	return;
}