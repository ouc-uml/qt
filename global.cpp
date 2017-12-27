#include<iostream>
#include<cstdio>
#include<cstring>
#include<fstream>
#include<string>

int user_Type;
int user_rank;
std::string sUser;
std::string sPwd;
using namespace std;
void outfilechar(char* str)
{
    ofstream out;
    out.open("E:\\out.txt",ios::app);
    if(out.is_open())
    {
        out << str <<endl;
        out.close();
    }
}
void outfileint(int str)
{
    ofstream out;
    out.open("E:\\out.txt",ios::app);
    if(out.is_open())
    {
        out << str <<endl;
        out.close();
    }
}
void outfilestring(string str)
{
    ofstream out;
    out.open("E:\\out.txt",ios::app);
    if(out.is_open())
    {
        out << str <<endl;
        out.close();
    }
}
void outfilelong(long long str)
{
    ofstream out;
    out.open("E:\\out.txt",ios::app);
    if(out.is_open())
    {
        out << str <<endl;
        out.close();
    }
}
