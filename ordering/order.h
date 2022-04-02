#ifndef ORDER_H
#define ORDER_H
#include<stdio.h>
#include<iostream>
#include<Winsock2.h>
#include<mysql.h>
#include<string>
#include<iomanip>
#include <time.h>
#include<Windows.h>
#include "User.h"
#include "client.h"
using namespace std;

void print(int n) {
    for (int i = 0; i < n; i++) cout << "-";
}

void print_s(int n) {
    for (int i = 0; i < n; i++) cout << " ";
}

int order_ok[28] = {0};

void showmenu(User user) {
    string account_order(MYSQL_ROW rows[], User user);
    MYSQL menu;
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_init(&menu);
    if (!mysql_real_connect(&menu, host, db_user, db_pawd, "info", 3306, NULL, 0))
        cout << "����ʧ��" << endl;
    mysql_set_character_set(&menu, "utf8");
    mysql_query(&menu, "SET NAMES GB2312");
    string sql = "select * from  store";
    if (mysql_query(&menu, sql.c_str())) {
        cout << mysql_error(&menu) << endl;
        return;
    }
    res = mysql_store_result(&menu);
    int n = mysql_num_rows(res);
    MYSQL_ROW rows[29];
    int i = 1;
    while (rows[i] = mysql_fetch_row(res)) {
        i++;
        if (i > n) break;
    }
    string sign;
    int page = 1, first_time = 1, f_error = 0, l_error = 0, o_error = 0;
    while (1) {
        cout << "|";
        print(51 / 2);
        cout << " menu ";
        print(51 / 2 + 1);
        cout << "|";
        cout << left << "\n|id";
        print_s(2);
        print_s(15);
        cout << left << "�̼�����";
        print_s(14);
        print_s(2);
        cout << left << "����";
        print_s(2);
        cout << left << "ƽ���۸�|";
        print_s(8);
        cout << "\n";
        for (int i = (page - 1) * 9 + 1; i <= page * 9 && i <= n; i++) 
            cout << "|" << left << setw(6) << rows[i][0] << left << setw(37) << rows[i][1] << left << setw(8) << rows[i][2] << left << setw(6) << rows[i][3] << "|" << endl;
        cout << "|";
        print_s(2);
        print(53);
        print_s(2);
        cout << "|\n";
        cout << "|" << left << setw(45) << "<1.��һҳ>,<2.��һҳ>,<3.�ر�>" << "<" << page << left << setw(10) << "/3>" << "|" << endl;
        cout << "|" << left << setw(57) << "<4.���붩��>,<5.����>" << "|" << endl;
        cout << "|";
        print(57);
        cout << "|" << endl;
        if (f_error) cout << "�Ѿ��ǵ�һҳ��";
        if (l_error) cout << "�Ѿ������һҳ��";
        if (!o_error||first_time) cout << "������ִ�в�����:";
        else cout << "��������ȷ�Ĳ�������(1,2,3,4 or 5) :";
        first_time = 0;
        cin >> sign;
        if (sign == "1") {
            o_error = 0;
            if (page == 1) f_error = 1;
            else {
                --page;
                f_error = 0;
                l_error = 0;
            }
            system("cls");
            continue;
        }
        if (sign == "2") {
            o_error = 0;
            if (page == 3) l_error = 1;
            else {
                ++page;
                l_error = 0;
                f_error = 0;
            }
            system("cls");
            continue;
        }
        if (sign == "3") {
            system("cls");
            return;
        }
        if (sign == "4") {
            string str,order="";
            cout << "�����id(���id֮����Ӣ�Ķ��Ÿ���):";
            cin >> str;
            order += (str + ",");
            int num = 0;
            for (int i = 0; i < order.length(); i++) {
                if (order[i] >= '0' && order[i] <= '9') {
                    num *= 10;
                    num += order[i] - '0';
                    if (num > 27) num = 0;
                }
                if (order[i] == ',') {
                    order_ok[num] = 1;
                    num = 0;
                }
            }
            system("cls");
            continue;
        }
        if (sign == "5") {
            string c = account_order(rows, user);
            if (c == "1") {
                for (int i = 0; i < 28; i++) order_ok[i] = 0;
                return;
            }
            else {
                system("cls");
                continue;
            }
        }
        o_error = 1;
        system("cls");
    }
}

string account_order(MYSQL_ROW rows[], User user) {
    int num = 0, have_order = 0;
    //int price=0;
    while (1) {
        cout << "|";
        print(51 / 2);
        cout << "  ����  ";
        print(51 / 2 + 1);
        cout << "|" << endl;
        for (int i = 1; i <= 27; i++)
            if (order_ok[i]) { 
                have_order = 1;
                cout << "|" << left << setw(6) << rows[i][0] << left << setw(37) << rows[i][1] << left << setw(8) << rows[i][2] << left << setw(6) << rows[i][3] << "|" << endl; 
            }
        string n;
        // price += (int)rows[num][3];
        //  cout << "һ����" << price << "Ԫ" << endl;
        cout << "<1.����>,<2.ɾ������>,<3.����> :";
        cin >> n;
        if (n == "1") {
            if (have_order) {
                string information = "�µĶ�����\n�ͻ���" + user.getname();
                if (user.getsex() == "��") information += " ����\n�绰��";
                else information += " Ůʿ\n�绰��";
                information += user.get_tele() + "\n";
                information += "��ַ��" + user.getaddr() + "\n������";
                client(information);
                Sleep(200);
            }
            MYSQL menu;
            MYSQL_RES* res;
            MYSQL_ROW row;
            mysql_init(&menu);
            if (!mysql_real_connect(&menu, host, db_user, db_pawd, "order", 3306, NULL, 0)) {
                cout << "����ʧ�ܣ���������������..." << endl;
                Sleep(3 * 1000);
                return "";
            }
            mysql_set_character_set(&menu, "utf8");
            mysql_query(&menu, "SET NAMES GB2312");
            int num_order = 0;
            string order_bo = "";
            for (int i = 1; i <= 27; i++) {
                if (order_ok[i]) {
                    string sql = "CREATE TABLE IF NOT EXISTS `" + user.getuser_name() + "`  ( \
		            `id` int AUTO_INCREMENT,\
		            `store_name` text,\
		            `scores` text,\
		            `date` text,\
		            PRIMARY KEY(`id`)\
		            ) ";
                    if (mysql_query(&menu, sql.c_str())) {
                        cout << mysql_error(&menu) << endl;
                        return "";
                    }
                    SYSTEMTIME sys;
                    GetLocalTime(&sys);
                    string date;
                    char d[64];
                    sprintf(d, "%4d-%02d-%02d %02d:%02d:%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
                    date = d;
                    sql = "INSERT INTO " + user.getuser_name() + "(store_name,scores,date) VALUES('" + rows[i][1] + "','" + "-1" + "','" + date + "')";
                    if (mysql_query(&menu, sql.c_str())) {
                        cout << mysql_error(&menu) << endl;
                        return "";
                    }
                    order_bo += rows[i][1];
                    order_bo += "\n";
                }
            }
            if (have_order) {
                client(order_bo);
                Sleep(200);
            }
            cout << "����ɹ�,�Ѿ����͸��̼�,��������������...";
            Sleep(3 * 1000);
            system("cls");
            return "1";
        }
        if (n == "2") {
            int n = 0;
            string str,del;
            cout << "������ɾ���Ķ���id(���id֮����Ӣ�Ķ��Ÿ���):";
            cin >> str;
            del += (str + ",");
            for (int i = 0; i < del.length(); i++) {
                if (del[i] >= '0' && del[i] <= '9') {
                    n *= 10;
                    n += del[i] - '0';
                    if (n > 27) n = 0;
                }
                if (del[i] == ',') {
                    order_ok[n] = 0;
                    n = 0;
                }
            }
            return "";
        }
        if (n == "3") return "";
    }
}


void queryorder(string user_name) {
    MYSQL order;
    MYSQL_RES* res;
    MYSQL_ROW row;
    mysql_init(&order);
    if (!mysql_real_connect(&order, host, db_user, db_pawd, "order", 3306, NULL, 0))
        cout << "����ʧ��" << endl;
    mysql_set_character_set(&order, "utf8");
    mysql_query(&order, "SET NAMES GB2312");
    string sql = "select * from  " + user_name+" order by id desc";
    if (mysql_query(&order, sql.c_str())) {
        cout << "����Ϊ�գ���������������..." << endl;
        Sleep(3 * 1000);
        system("cls");
        return;
    }
    res = mysql_store_result(&order);
    int num = mysql_num_rows(res);
    MYSQL_ROW* rows = new MYSQL_ROW[num];
    int i = 1;
    while (rows[i] = mysql_fetch_row(res)) {
        i++;
        if (i > num) break;
    }
    string sign,eval="";
    int page = 1, first_time = 1, f_error = 0, l_error = 0, o_error = 0, not_found = 0;
    while (1) {
        cout << "|";
        print(60 / 2);
        cout << " ��ʷ���� ";
        print(59 / 2 + 1);
        cout << "|";
        cout << left << "\n|id";
        print_s(2);
        print_s(15);
        cout << left << "�̼�����";
        print_s(14);
        print_s(2);
        cout << left << "����";
        print_s(10);
        cout << left << "��������";
        print_s(5);
        cout << "|\n";
        for (int i = (page - 1) * 9 + 1; i <= page * 9 && i <= num; i++) {
            cout << "|" << left << setw(6) << rows[i][0] << left << setw(37) << rows[i][1];
            if (!strcmp(rows[i][2],"-1")) cout << left << setw(8) << "δ��" << left << setw(13) << rows[i][3] << "|" << endl;
            else cout<< left << setw(8) << rows[i][2] << left << setw(13) << rows[i][3] << "|" << endl;
        }
        cout << "|";
        print_s(2);
        print(66);
        print_s(2);
        cout << "|\n";
        cout << "|" << left << setw(45) << "<1.��һҳ>,<2.��һҳ>,<3.����><4.�ر�>" << "<" << page << left << "/" << (num / 9 + 1) << left << setw(21) << ">" << "|" << endl;
        cout << "|";
        print(70);
        cout << "|" << endl;
        if (f_error) cout << "�Ѿ��ǵ�һҳ��";
        if (l_error) cout << "�Ѿ������һҳ��";
        if (!o_error || first_time) cout << "������ִ�в�����:";
        else cout << "��������ȷ�Ĳ�������(1 or 2 or 3) :";
        first_time = 0;
        cin >> sign;
        if (sign == "1") {
            o_error = 0;
            if (page == 1) { 
                l_error = 0;
                f_error = 1;
            }
            else {
                --page;
                f_error = 0;
                l_error = 0;
            }
            system("cls");
            continue;
        }
        if (sign == "2") {
            o_error = 0;
            ++page;
            if (((page - 1) * 9 + 1) > num) {
                l_error = 1;
                f_error = 0;
                --page;
            }
            else {
                l_error = 0;
                f_error = 0;
            }
            system("cls");
            continue;
        }
        if (sign == "3") {
            while (1) {
                string str;
                if (not_found) cout << "��������ȷ�Ķ���id��(�������� -1 ����):";
                else cout << "�����۵Ķ���id(��������):";
                cin >> str;
                if (str == "-1") {
                    not_found = 0;
                    system("cls");
                    break;
                }
                int ok = 0;
                for (int i = 1; i <= num; i++) {
                    if (rows[i][0] == str) {
                        ok = 1;
                        break;
                    }
                }
                if (!ok) {
                    not_found = 1;
                    continue;
                }
                not_found = 0;
                float sc;
                cout << "������(1-5��):";
                cin >> sc;

                sql = "update " + user_name + " set scores='" + to_string(sc).substr(0,3) + "' where id='" + str + "';";
                if (!mysql_query(&order, sql.c_str())) {
                    cout << "���ֳɹ���";
                    Sleep(2500);
                    system("cls");
                    return;
                }
            }
        }
        if (sign == "4") {
            system("cls");
            return;
        }
    }
}

#endif