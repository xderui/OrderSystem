#ifndef USER_H
#define USER_H
#include<iostream>
#include<string.h>
#include<string>
#include<Winsock2.h>
#include<mysql.h>
#include<windows.h>
using namespace std;
const char* host = "localhost";          //如果你有云数据库，将此处改为你的数据库ip或者域名
const char* db_user = "root";             //数据库用户名
const char* db_pawd = "123456";     //数据库密码     都是在安装过程中配置的
class User                                            //对于本地数据库，如果忘记了用户名和密码，可以重新运行一次安装包，可以进行修改
{
private:
    string name;//姓名
    string sex;//性别 
    string Telnumber;//手机号码
    string address;//地址
    string user_name;
public:
    User() {}
    User(const string n, const string s,const string t,const string a, const string u_n);//构造函数
    User(string t, string a);
    void Modify(string user_name);//修改信息
    void display();//显示信息
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
    cout << "<1.姓名>,<2.性别>,<3.电话>,<4.地址>,<5.取消修改>\n" << endl;
    while(1){
        cout << "请输入需要修改的信息前的编号组合(如134)：";
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
                cout << "你的意思是需要修改";
                for (int i = 1; i <= 4; i++)
                    if (ok[i]) cout << i << ",";
                cout << "\b \b";
                cout << "项吗？\n<1.是>,<2.否,重新输入>,<3.否,取消修改>：";
                string n;
                cin >> n;
                if (n == "2") continue;
                if (n == "3") break;
                if (n != "1")  cout << "请重新输入正确的操作数！";
            }
                MYSQL modif;
                MYSQL_RES* res;
                MYSQL_ROW row;
                string sql;
                mysql_init(&modif);
                if (!mysql_real_connect(&modif, host, db_user, db_pawd, "info", 3306, NULL, 0))
                    cout << "数据库连接失败，修改未成功！" << endl;
                mysql_set_character_set(&modif, "utf8");
                mysql_query(&modif, "SET NAMES GB2312");
                if (ok[1]) {
                    cout << "姓名：";
                    cin >> name;
                    sql = "update user set name='" + name + "' where user_name='" + user_name + "';";
                    mysql_query(&modif, sql.c_str());
                }
                if (ok[2]) {
                    cout << "性别：";
                    cin >> sex;
                    sql = "update user set sex='" + sex + "' where user_name='" + user_name + "';";
                    mysql_query(&modif, sql.c_str());
                }
                if (ok[3]) {
                    cout << "电话：";
                    cin >> Telnumber;
                    sql = "update user set phone_number='" + Telnumber + "' where user_name='" + user_name + "';";
                    mysql_query(&modif, sql.c_str());
                }
                if (ok[4]) {
                    cout << "地址：";
                    cin >> address;
                    sql = "update user set address='" + address + "' where user_name='" + user_name + "';";
                    mysql_query(&modif, sql.c_str());
                }
                cout << "修改完成！即将回到主界面...";
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
    cout << "个人信息";
    print_star(max(Telnumber.length(), address.length()) / 2);
    cout << "\n姓名:" << name << endl;
    cout << "性别:" << sex << endl;
    cout << "电话:" << Telnumber << endl;
    cout << "地址:" << address << endl;
    print_star(max(Telnumber.length(), address.length()) + 8);
}

void personalinfo(User user) {
    while (1) {
        string n;
        user.display();
        cout << "\n<1.修改个人信息>,<2.返回>" << endl;
        cout << "请输入操作数：";
        cin >> n;
        if (n == "1") user.Modify(user.getuser_name());
        if (n == "2") {
            system("cls");
            return;
        }
    }
}

#endif 
