#ifndef USER_H
#define USER_H
#include<iostream>
#include<string.h>
#include<string>
#include<Winsock2.h>
#include<mysql.h>
#include<windows.h>
using namespace std;
const char* host = "localhost";          //������������ݿ⣬���˴���Ϊ������ݿ�ip��������
const char* db_user = "root";             //���ݿ��û���
const char* db_pawd = "123456";     //���ݿ�����     �����ڰ�װ���������õ�
class User                                            //���ڱ������ݿ⣬����������û��������룬������������һ�ΰ�װ�������Խ����޸�
{
private:
    string name;//����
    string sex;//�Ա� 
    string Telnumber;//�ֻ�����
    string address;//��ַ
    string user_name;
public:
    User() {}
    User(const string n, const string s,const string t,const string a, const string u_n);//���캯��
    User(string t, string a);
    void Modify(string user_name);//�޸���Ϣ
    void display();//��ʾ��Ϣ
    string getname() { return name; }
    string getaddr() { return address; }
    string get_tele() { return Telnumber; }
    string getsex() { return sex; }
    string getuser_name() { return user_name; }
};
User::User(const string n, const string s, const string t, const string a,const string u_n)
{
    Telnumber = t;
    address = a;
    name = n;
    sex = s;
    user_name = u_n;
}
User::User(string t, string a)
{
    Telnumber = t;
    address = a;
}

void User::Modify(string user_name) {
    char input[30];
    system("cls");
    cout << "<1.����>,<2.�Ա�>,<3.�绰>,<4.��ַ>,<5.ȡ���޸�>\n" << endl;
    while(1){
        cout << "��������Ҫ�޸ĵ���Ϣǰ�ı�����(��134)��";
        cin >> input;
        int len = strlen(input);
        int ok[30], have_error = 0, have_true = 0;
        for (int i = 0; i < 5; i++) ok[i] = 0;
        for (int i = 0; i < len; i++) {
            if (input[i] >= '1' && input[i] <= '5') {
                ok[input[i] - '0'] = 1;
                have_true = 1;
            }
            else have_error = 1;
        }

        if (have_true) {
            if (have_error) {
                cout << "�����˼����Ҫ�޸�";
                for (int i = 1; i <= 4; i++)
                    if (ok[i]) cout << i << ",";
                cout << "\b \b";
                cout << "����\n<1.��>,<2.��,��������>,<3.��,ȡ���޸�>��";
                string n;
                cin >> n;
                if (n == "2") continue;
                if (n == "3") break;
                if (n != "1")  cout << "������������ȷ�Ĳ�������";
            }
                MYSQL modif;
                MYSQL_RES* res;
                MYSQL_ROW row;
                string sql;
                mysql_init(&modif);
                if (!mysql_real_connect(&modif, host, db_user, db_pawd, "info", 3306, NULL, 0))
                    cout << "���ݿ�����ʧ�ܣ��޸�δ�ɹ���" << endl;
                mysql_set_character_set(&modif, "utf8");
                mysql_query(&modif, "SET NAMES GB2312");
                if (ok[1]) {
                    cout << "������";
                    cin >> name;
                    sql = "update user set name='" + name + "' where user_name='" + user_name + "';";
                    mysql_query(&modif, sql.c_str());
                }
                if (ok[2]) {
                    cout << "�Ա�";
                    cin >> sex;
                    sql = "update user set sex='" + sex + "' where user_name='" + user_name + "';";
                    mysql_query(&modif, sql.c_str());
                }
                if (ok[3]) {
                    cout << "�绰��";
                    cin >> Telnumber;
                    sql = "update user set phone_number='" + Telnumber + "' where user_name='" + user_name + "';";
                    mysql_query(&modif, sql.c_str());
                }
                if (ok[4]) {
                    cout << "��ַ��";
                    cin >> address;
                    sql = "update user set address='" + address + "' where user_name='" + user_name + "';";
                    mysql_query(&modif, sql.c_str());
                }
                cout << "�޸���ɣ������ص�������...";
                Sleep(3 * 1000);
                system("cls");
                return;
        }
     }
}

void print_star(int n) {
    for (int i = 0; i < n; i++) cout << "*";
}



void User::display()
{                            
    print_star(max(Telnumber.length(), address.length()) / 2);
    cout << "������Ϣ";
    print_star(max(Telnumber.length(), address.length()) / 2);
    cout << "\n����:" << name << endl;
    cout << "�Ա�:" << sex << endl;
    cout << "�绰:" << Telnumber << endl;
    cout << "��ַ:" << address << endl;
    print_star(max(Telnumber.length(), address.length()) + 8);
}

void personalinfo(User user) {
    while (1) {
        string n;
        user.display();
        cout << "\n<1.�޸ĸ�����Ϣ>,<2.����>" << endl;
        cout << "�������������";
        cin >> n;
        if (n == "1") user.Modify(user.getuser_name());
        if (n == "2") {
            system("cls");
            return;
        }
    }
}

#endif 
