#include <string>
#include <vector>
#define UPLOAD 8
using namespace std;

extern int s_connecting();
extern int s_sending(char* msg,int n);
extern int s_recving(char* buff);
extern void s_close();
extern int server(string command);
extern int server(string command,vector<vector<string> >&result);
extern int login(string id,string password);
extern int logout();
extern int change_pwd(string old_pwd,string new_pwd);
extern string get_ntime();

extern int upload(string command);//成功返回0,语法错误返回-1,没有权限返回-2
