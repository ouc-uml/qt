#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock2.h>
#include<windows.h>
#include "global.h"
#include"connect.h"
#include "md5.h"
#define LOGIN 1         //登陆
#define REGISTER 2      //注册
#define PASSWORD 3      //改密码
#define TIME 4          //服务器精确到秒的时间，格式如2017.12.12.12.0.0精确到秒吧
#define SQL1 5          //不带动态数组的sql
#define SQL2 6          //带动态数组的sql
#define LOGOUT 7
#define CONERR (char*)"connect error %s errno: %d\n"
#define SENERR (char*)"send mes error %s errno: %d\n"
#define MAXLINE 1024
#define MSGLEN  256
#define SERVER_ADDR (char*)"101.200.42.79"
#define SERVER_PORT 10004
#define MESSAGE (char*)"%d\n%s\n%s"
#define SPACER ","

using namespace std;
struct{
    WSADATA wsd;
    SOCKET sClient;
    struct sockaddr_in server;
    struct hostent *host = NULL;
    unsigned short port;
}connection;

vector<vector<string>> toVector(char* str){
    vector<vector<string>> *resl=new vector<vector<string>>;
    vector<string> mid;
    char *buff;
    mid.push_back(string(strtok(str,(char*)"\t")));
    while(buff=strtok(NULL,(char*)"\t"))
        mid.push_back(string(buff));
    for(int i=0;i<mid.size();i++){
        vector<string>* array;
        array=new vector<string>;
        char tmp[MAXLINE];
        strcpy(tmp,mid[i].c_str());
        array->push_back(string(strtok(tmp,(char*)SPACER)));
        while(buff=strtok(NULL,(char*)SPACER))
            array->push_back(string(buff));
        resl->push_back(*array);
        delete array;
    }

    return *resl;
}

int s_connecting(){
    if(WSAStartup(MAKEWORD(2,2),&connection.wsd)!=0)
        return WSAGetLastError();

    connection.sClient = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    if (connection.sClient == INVALID_SOCKET)
        return WSAGetLastError();

        connection.server.sin_family = AF_INET;
    connection.port = SERVER_PORT;
    connection.server.sin_port = htons(connection.port);
    connection.server.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    if(connect(connection.sClient , (struct sockaddr*)&connection.server ,sizeof(connection.server)) == SOCKET_ERROR)
        return WSAGetLastError();

        return 0;
}

int s_sending(char* msg,int n=1){
    char mssg[MAXLINE];
    sprintf(mssg,"%d\n%s",n,msg);
    if((send(connection.sClient,mssg,strlen(mssg),0)) < 0)
        return WSAGetLastError();

    return 0;
}

int s_recving(char* buff){
    int n;
    n = recv(connection.sClient,buff,MAXLINE,0);
    buff[n] = '\0';
    if(n>0)return 0;
    else if (n == SOCKET_ERROR)
        return WSAGetLastError();

       return 0;
}


void s_close(){
    closesocket(connection.sClient);
    WSACleanup();    //关闭socket和套接字
}

int server(string command){//成功返回0,语法错误返回-1,没有权限返回-2
    int n=0;
    char buff[MAXLINE]={0};
    char cmd[MAXLINE];
    strcpy(cmd,command.c_str());
    while(n=s_sending(cmd,SQL1)) if(n>0) login(sUser,sPwd);else return n;
    while(n=s_recving(buff)) if(n>0) login(sUser,sPwd);else return n;
    return atoi(buff);
}

int server(string command,vector<vector<string> >&result){
    vector<vector<string> > resl;
    int n=0;
    char buff[MAXLINE]={0};
    char cmd[MAXLINE];
    strcpy(cmd,command.c_str());
    while(n=s_sending(cmd,SQL2)) if(n>0) login(sUser,sPwd);else return n;
    while(n=s_recving(buff)) if(n>0) login(sUser,sPwd);else return n;
    n=atoi(strtok(buff,(char*)"\n"));
    //cout<<strtok(NULL,(char*)"\n");
    if(!n)result=vector<vector<string> >(toVector(strtok(NULL,(char*)"\n")));
    return n;
}



int login(string id,string password){//-1用户名密码不匹配;-3网络错误
    int zztmp = s_connecting();
    outfileint(zztmp);
    MD5 pwd(password);
    string msg=id+"\t"+pwd.hexdigest();
    int n=0;
    char buff[MAXLINE]={0};
    char cmd[MAXLINE];
    strcpy(cmd,msg.c_str());
    if(n=s_sending(cmd,LOGIN)) return -3;
    if(n=s_recving(buff)) return -3;
    return atoi(strtok(buff,(char*)"\n"));
}

int signIn(string id,string password){//-1重名;-3网络错误
    s_connecting();
    MD5 pwd(password);
    string msg=id+"\t"+pwd.hexdigest();
    int n=0;
    char buff[MAXLINE]={0};
    char cmd[MAXLINE];
    strcpy(cmd,msg.c_str());
    if(n=s_sending(cmd,REGISTER)) return -3;
    if(n=s_recving(buff)) return -3;
    return atoi(strtok(buff,(char*)"\n"));
}

int change_pwd(string old_pwd,string new_pwd){//-1重名;-3网络错误
    MD5 old(old_pwd);
    MD5 neww(new_pwd);
    string msg = old.hexdigest() + "\t" + neww.hexdigest();
    int n=0;
    char buff[MAXLINE]={0};
    char cmd[MAXLINE];
    strcpy(cmd,msg.c_str());
    while(n=s_sending(cmd,PASSWORD)) if(n>0) login(sUser,sPwd);else return n;
    while(n=s_recving(buff)) if(n>0) login(sUser,sPwd);else return n;
    return atoi(strtok(buff,(char*)"\n"));
}


int logout(){//-1用户名密码不匹配;-3网络错误
    int n=0;
    char buff[MAXLINE]={0};
    if(n=s_sending((char*)"",LOGOUT)) return -3;
    if(n=s_recving(buff)) return -3;
    return atoi(strtok(buff,(char*)"\n"));
}

string get_ntime(){
    int n=0;
    char buff[MAXLINE]={0};
    while(n=s_sending((char*)"",TIME/*获取服务器时间*/)) if(n>0) login(sUser,sPwd);else return "OUTTIME";
    while(n=s_recving(buff)) if(n>0) login(sUser,sPwd);else return "OUTTIME";
    if(atoi(strtok(buff,(char*)"\n"))) return "Error!";
    else return string(strtok(NULL,(char*)"\n"));
}
