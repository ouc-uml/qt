#include "connect.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <library.h>
#define BRMAX 4
#define RSMAX 4

void replace_str(string & str, const string & old_value, const string & new_value)
{
    for(string::size_type pos(0); pos!=string::npos; pos+=new_value.length())
        if(   (pos=str.find(old_value,pos)) != string::npos   )
            str.replace(pos,old_value.length(),new_value);
        else
            break;
}

void norm_val(string & val){
    replace_str(val, "'", "\\'");
    val = "'" + val + "'";
}

template<class out_type,class in_value>
out_type convert(const in_value & t){
    stringstream stream;
    stream << t;
    out_type result;
    stream >> result;
    return result;
}

int add_user(vector<string> & user)
//返回2是用户名不能为空
{
    int ret = 0;
    vector<vector<string> > temp;
    string command, values;
    int i;
    for(i = 0; i < user.size(); i++)
        norm_val(user.at(i));
    command = "select Urank from User where Uname = " + user.at(0);
    ret = server(command, temp);
    if(ret)
        return ret;
    if(temp.size() != 1)
        return 3;
    if(user.size() < 3)
        return 1;
    if(user[0] == "")
        return 2;
    values = user.at(0);
    for(i = 1; i < 3; i++)
    {
        values += ", ";
        values += user.at(i);
    }
    string time_s = get_ntime();
    norm_val(time_s);
    command = "insert into User values (" + values + ", " + time_s + ", 0)";
    ret = server(command);
    if(ret)
        return ret;
    values = user.at(0) + ", 0";
    for(i = 3; i < user.size(); i++)
        values += ", " + user.at(i);
    command = "insert into 用户信息表 values (" + values + ")";
    return server(command);
}

int delete_user(string id)
//返回3是用户还有书未归还
{
    vector<vector<string> > temp;
    int ret = 0;
    norm_val(id);
    string command;
    command = "select 状态 from 借阅表 where 用户名 = " + id + " and 状态 = 1";
    ret = server(command, temp);
    if(ret)
        return ret;
    if(temp.size() > 1)
        return 3;
    command = "update 预约表 set 状态 = 0 where 用户名 = " + id;
    ret = server(command);
    if(ret)
        return ret;
    command = "delete from User where Uname = " + id;
    ret = server(command);
    if(ret)
        return ret;
    command = "delete from 用户信息表 where 用户名 = " + id;
    return server(command);
}

vector<string> user_info(string userid){
    vector<vector<string> > temp;
    vector<string> result;
    string command, table_name;
    norm_val(userid);
    command = "select * from 用户信息表 where 用户名 = " + userid;
    if(server(command, temp))
        return result;
    if(temp.size() < 2)
        return result;
    result = temp[1];
    for(int i = 0; i < result.size(); i++)
        replace_str(result.at(i), "\\'", "'");
    return result;
}

vector<string> all_user(){
    vector<vector<string> > temp;
    vector<string> result;
    string command = "select 用户名 from 用户信息表";
    if(server(command, temp))
        return result;
    for(int i = 1; i < temp.size(); i++)
    {
        replace_str(temp.at(i).at(0), "\\'", "'");
        result.push_back(temp.at(i).at(0));
    }
    return result;
}

int update_user(vector<string> val)
{
    int i;
    vector<vector<string> > temp;
    string command;
    for(i = 0; i < val.size(); i++)
        norm_val(val.at(i));
    command = "select * from 用户信息表 where 用户名 = " + val.at(0);
    int ret = -1;
    ret=server(command, temp);
    if(ret)
        return ret;
    if(temp.size() < 2)
        return 3;
    if(temp.at(0).size() != val.size())//原：val.size()+1
        return 1;
    //cout<<temp[0].size()<<" "<<val.size()<<endl;
    command = "update 用户信息表 set ";
    for(i = 1; i < temp.at(0).size() - 1; i++)
    {
        command += temp.at(0).at(i) + " = ";
        command += val.at(i) + ", ";
    }
    command += temp.at(0).at(i) + " = ";
    command += val.at(i) + " where 用户名 = " + val.at(0);
    return server(command);
}

int user_lev(string userid, int & level)
{
    vector<vector<string> > temp;
    norm_val(userid);
    string command = "select Urank from User where Uname = " + userid;
    int ret = server(command, temp);
    if(ret)
        return ret;
    if(temp.size() < 2)
        return 3;
    level = convert<int>(temp.at(1).at(0));
    return 0;
}

int update_user_lev(string userid, int level)
{
    norm_val(userid);
    string command = "update User set Urank = " + convert<string>(level) + " where Uname = " + userid;
    //cout<<command<<endl;
    return server(command);
}




int add_book(string userid, vector<string> & book)
//返回2未知错误,返回3是ISBN不能为空
{
    if(book.size() < 1)
        return 2;
    if(book[0] == "")
        return 3;
    vector<vector<string> > temp;
    string command, values;
    command = "select ISBN from 图书信息表 where ISBN = " + book.at(0);
    int ret = server(command, temp);
    if(ret)
        return ret;
    for(int i = 0; i < book.size(); i++)
        norm_val(book.at(i));
    if(temp.size() == 1)
    {
        values = book.at(0);
        string time_s = get_ntime();
        norm_val(time_s);
        values += ", " + time_s + ", " + userid;
        for(int i = 3; i < book.size(); i++)
            values += ", " + book.at(i);
        command = "insert into 图书信息表 values (" + values + ")";
        ret = server(command);
        if(ret)
            return ret;
    }
    else
    {
        command = "select 状态 from 单本表 where ISBN = " + book.at(0) + " and 单本编号 = " + book.at(1);
        ret = server(command, temp);
        if(ret)
            return ret;
        if(temp.size() != 1)
            return 1;
    }
    command = "insert into 单本表 values (" + book.at(0) + ", " + book.at(1) + ", " + book.at(2) + ")";
    return server(command);
}

int delete_book(string bno, unsigned int eno)
{
    vector<vector<string> > temp;
    string command;
    command = "select 状态 from 单本表 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
    int ret = server(command, temp);
    if(ret)
        return ret;
    if(temp.size() < 2)
        return 1;
    int state = convert<int>(temp.at(1).at(0));
    if(state == 3)
        return 3;
    command = "delete from 单本表 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
    ret = server(command);
    if(ret)
        return ret;
    command = "update 预约表 set 状态 = 0 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
    ret = server(command);
    if(ret)
        return ret;
    command = "select 状态 from 单本表 where ISBN = " + bno;
    ret = server(command, temp);
    if(ret)
        return ret;
    if(temp.size() > 1)
        return 0;
    command = "delete from 图书信息表 where ISBN = " + bno;
    ret = server(command);
    if(ret)
        return ret;
    return 0;
}

int update_book(vector<string> val)
{
    vector<vector<string> > temp;
    string command;
    command = "select * from 图书信息表 where ISBN = " + val.at(0);
    int ret = server(command, temp);
    if(ret)
        return ret;
    if(temp.size() < 2)
        return 3;
    if(temp.at(0).size() != val.size() + 1)
        return 1;
    command = "update 图书信息表 set ";
    for(int i = 0; i < val.size(); i++)
        norm_val(val.at(i));
    int i;
    for(i = 2; i < temp.at(0).size() - 1; i++)
        command += temp.at(0).at(i) + " = " + val.at(i - 1) + ", ";
    command += temp.at(0).at(i) + " = " + val.at(i-1) + " where ISBN = " + val.at(0);
    return server(command);
}

vector<vector<string> > search_Bno(string bno, bool mode)
{
    vector<vector<string> > result;
    string command, table_name;
    if(mode)
        table_name = "单本表";
    else
        table_name = "图书信息表";
    command = "select * from " + table_name + " where ISBN = " + bno;
    if(server(command, result))
        result.clear();
    for(int i = 0; i < result.size(); i++)
        for(int j = 0; j < result.at(i).size(); j++)
            replace_str(result.at(i).at(j), "\\'", "'");
    return result;
}

vector<vector<string> > search_Bclm(string clm_name, string val)
{
    vector<vector<string> > result;
    string command;
    norm_val(val);
    command = "select * from 图书信息表 where " + clm_name + " like " + val;
    if(server(command, result))
        result.clear();
    for(int i = 0; i < result.size(); i++)
        for(int j = 0; j < result.at(i).size(); j++)
            replace_str(result.at(i).at(j), "\\'", "'");
    return result;
}

vector<string> all_book()
{
    vector<vector<string> > temp;
    vector<string> result;
    string command = "select ISBN from 图书信息表";
    if(server(command, temp))
        return result;
    for(int i = 1; i < temp.size(); i++)
        result.push_back(temp.at(i).at(0));
    return result;
}




int borrow(string bno, unsigned int eno, string uno, int day)
//返回6是到达借阅上限，返回7是你被冻结了
{
    vector<vector<string> > temp;
    string command;
    int ret;

    if(uno != "uml")
    {
        command = "select 状态 from 用户信息表 where 用户名 = " + uno;
        ret = server(command, temp);
        if(ret)
            return ret;
        if(temp.size() != 2 || temp[1].size() != 1)
            return 5;
        if(convert<int>(temp[1][0]) != 0)
            return 7;
    }

    command = "select 状态 from 单本表 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
    ret = server(command, temp);
    if(ret)
        return ret;
    if(temp.size() < 2)
        return 2;
    int state = convert<int>(temp.at(1).at(0));
    cout<<"state "<<state<<endl;
    if(state != 2)
        return state;
    command = "select 状态 from 借阅表 where 用户名 = '" + uno + "' and 状态 = 1";
    ret = server(command, temp);
    if(ret)
        return ret;
    if(temp.size() > BRMAX)
        return 6;
    command = "select 用户名 from 预约表 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno) + " and 状态 = 1";
    ret = server(command, temp);
    if(ret)
        return ret;
    if(temp.size() > 2)
        return 5;
    if(temp.size() == 2)
    {
        replace_str(temp.at(1).at(0), "\\'", "'");
        if(temp.at(1).at(0) == uno)
        {
            norm_val(uno);
            command = "update 预约表 set 状态 = 0 where 用户名 = " + uno + " and ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
            ret = server(command);
            if(ret)
                return ret;
        }
        else
            return 4;
    }
    command = "update 单本表 set 状态 = 3 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
    ret = server(command);
    if(ret)
        return ret;
    string time_s = get_ntime();
    norm_val(time_s);
    command = "insert into 借阅表 values(" + uno + ", " + bno + ", " + convert<string>(eno) + ", " + time_s + ", " + convert<string>(day) + ", 1)";
    return server(command);
}

int return_book(string bno, unsigned int eno)
//成功返回0，不存在返回1，以在馆返回2
{
    vector<vector<string> > temp;
    string command = "select 状态 from 单本表 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
    int ret = server(command, temp);
    if(ret)
        return ret;
    if(temp.size() < 2)
        return 1;
    int state = convert<int>(temp.at(1).at(0));
    if(state != 3)
        return 2;
    command = "update 单本表 set 状态 = 2 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
    ret = server(command);
    if(ret)
        return ret;
    command = "update 借阅表 set 状态 = 0 where ISBN = " + bno + " and 单本编号= " + convert<string>(eno);
    return server(command);
}

int reserve_book(string bno, unsigned int eno, string uno, int day)
//返回8是超过预约上限,返回9是你被冻结了
{
    vector<vector<string> > temp;
    string command;
    int ret;

    if(uno != "uml")
    {
        command = "select 状态 from 用户信息表 where 用户名 = " + uno;
        ret = server(command, temp);
        if(ret)
            return ret;
        if(temp.size() != 2 || temp[1].size() != 1)
            return 3;
        if(convert<int>(temp[1][0]) != 0)
            return 9;
    }
    command = "select 状态 from 单本表 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno);
    ret = server(command, temp);
    if(ret)
        return ret;
    if(temp.size() < 2)
        return 6;
    int state = convert<int>(temp.at(1).at(0));
    if(state != 3)
        return state;
    command = "select 状态 from 预约表 where 用户名 = '" + uno + "' and 状态 = 1";
    ret = server(command, temp);
    if(ret)
        return ret;
    if(temp.size() > RSMAX)
        return 8;
    command = "select 用户名 from 预约表 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno) + " and 状态 = 1";
    ret = server(command, temp);
    if(ret)
        return ret;
    if(temp.size() > 1)
        return 4;
    command = "select 用户名 from 借阅表 where ISBN = " + bno + " and 单本编号 = " + convert<string>(eno) + " and 状态 = 1";
    ret = server(command, temp);
    if(ret)
        return ret;
    if(temp.size() < 2)
        return 3;
    replace_str(temp.at(1).at(0), "\\'", "'");
    if(temp.at(1).at(0) == uno)
        return 7;
    string time_s = get_ntime();
    norm_val(uno);
    norm_val(time_s);
    command = "insert into 预约表 values(" + uno + ", " + bno + ", " + convert<string>(eno) + ", " + time_s + ", " + convert<string>(day) + ", 1)";
    return server(command);
}

string recommend(string bno, string bname, string userid)
{
    vector<vector<string> > result;
    result = search_Bno(bno, 0);
    if(result.size() != 1)
        return "已经存在此书";
    string time_s, command;
    time_s = get_ntime();
    norm_val(time_s);
    norm_val(userid);
    norm_val(bname);
    command = "select 状态 from 荐购表 where ISBN = " + bno;
    int ret = server(command, result);
    if(ret)
        return "网络错误";
    if(result.size() != 1)
        return "已经有人推荐此书了";
    command = "insert into 荐购表 values (" + userid + ", " + bno + ", " + bname + ", " + time_s + ", 1)";
    ret = server(command);
    if(ret)
        return "网络错误";
    return "推荐成功";
}

vector<vector<string> > reader_history(string userid)
{
    vector<vector<string> > result;
    string command;
    norm_val(userid);
    command = "select * from 借阅表 where 用户名 = " + userid;
    if(server(command, result))
        result.clear();
    for(int i = 0; i < result.size(); i++)
        for(int j = 0; j < result.at(i).size(); j++)
            replace_str(result.at(i).at(j), "\\'", "'");
    return result;
}

vector<vector<string> > reader_current(string userid)
{
    vector<vector<string> > result;
    string command;
    if(userid == "0")
        command = "select * from 借阅表 where 状态 = 1";
    else
    {
        norm_val(userid);
        command = "select * from 借阅表 where 用户名 = " + userid + " and 状态 = 1";
    }
    if(server(command, result))
        result.clear();
    for(int i = 0; i < result.size(); i++)
        for(int j = 0; j < result.at(i).size(); j++)
            replace_str(result.at(i).at(j), "\\'", "'");
    return result;
}

vector<vector<string> > search_recommend(string uno)
{
    vector<vector<string> > temp;
    string command;
    if(uno == "0")
        command = "select * from 荐购表 where 状态 = 1";
    else
    {
        norm_val(uno);
        command = "select * from 荐购表 where 用户名 = " + uno;
    }
    if(server(command, temp))
        temp.clear();
    for(int i = 0; i < temp.size(); i++)
        for(int j = 0; j < temp.at(i).size(); j++)
            replace_str(temp.at(i).at(j), "\\'", "'");
    return temp;
}

int read_recommend(string userid, string isbn)
{
    norm_val(userid);
    string command = "update 荐购表 set 状态 = 0 where 用户名 = " + userid + " and ISBN = " + isbn;
    return server(command);
}






int send_message(string userid1, string userid2, string message)
{
    norm_val(userid1);
    norm_val(userid2);
    norm_val(message);
    string command = "insert into 消息表 values(" + userid1 + ", " + userid2 + ", " + message + ")";
    return server(command);
}

vector<string> get_message(string userid)
{
    vector<vector<string> > temp;
    vector<string> result;
    string command;
    command = "select 消息 from 消息表 where 用户名2 = " + userid + " or 用户名2 = 0";
    if(server(command, temp))
        return result;
    if(temp.size() < 2)
        return result;
    for(int i = 1; i < temp.size(); i++)
        result.push_back(temp.at(i).at(0));
    for(int i = 0; i < result.size(); i++)
        replace_str(result.at(i), "\\'", "'");
    return result;
}


vector<vector<string> > search_res(string uno)//预约记录查询，uno为0为查询所有未处理记录
{
    vector<vector<string> > temp;
    string command;
    if(uno == "0")
        command = "select * from 预约表 where 状态 = 1";
    else
    {
        norm_val(uno);
        command = "select * from 预约表 where 用户名 = " + uno + " and 状态 = 1";
    }
    if(server(command, temp))
        temp.clear();
    for(int i = 0; i < temp.size(); i++)
        for(int j = 0; j < temp.at(i).size(); j++)
            replace_str(temp.at(i).at(j), "\\'", "'");
    return temp;
}

void cut_by_reg(string obj, string reg, vector<string>& res_str)        //通过正则表达式切割字符串，不分大小写
{
    res_str.clear();
    regex ip_reg(reg, regex::icase);
    std::sregex_token_iterator p(obj.begin(), obj.end(), ip_reg, -1);
    std::sregex_token_iterator end;
    while(p != end)
    {
        res_str.push_back(*p);
        p++;
    }
}

string add_users(string path, int & num)
//增加用户，成功返回0,返回1文件读取失败
//顺序 用户名,密码,昵称,年纪
//批量导入文件第一行无效
{
    int i;
    vector<string> user;
    vector<vector<string> > temp;
    string input, command, values, time_s;
    fstream file(path);
    if(!file.is_open())
        return "文件路径错误";

    unsigned char  s2;
    file.read((char*)&s2, sizeof(s2));//读取第一个字节，然后左移8位
    int p = s2<<8;
    file.read((char*)&s2, sizeof(s2));//读取第二个字节
    p +=s2;
    if(p != 0xefbb)
        return "文件编码不是utf8";
    file.seekg(0, ios::beg);
    int line = 1;
    getline(file, input);
    do
    {
        getline(file, input);
        if(file.eof())
            break;
        line++;
        cut_by_reg(input, "\\s*,\\s*", user);
        if(user.size() != 4)
            return "第" + convert<string>(line) + "行格式不正确";
        for(int j = 0; j < 4; j++)
            if(user[j].empty())
                return "第" + convert<string>(line) + "行格式不正确";
        for(i = 0; i < user.size(); i++)
            if(user[i].size() > 60)
                return "第" + convert<string>(line) + "行字符串长度不能大于60";
    }
    while(1);
    file.close();
    file.open(path);
    file.seekg(0, ios::beg);
    getline(file, input);

    time_s = get_ntime();
    norm_val(time_s);
    num = 0;
    do
    {
        getline(file, input);
        if(file.eof())
            break;

        cut_by_reg(input, "\\s*,\\s*", user);
        //cout << "user:" << user.size() << endl;
        if(user.size() < 2)
            continue;
        MD5 md5(user[1]);
        user[1]=md5.hexdigest();
        for(i = 0; i < user.size(); i++)
            norm_val(user.at(i));
        command = "select Urank from User where Uname = " + user.at(0);
        temp.clear();
        if(server(command, temp))
            continue;
        if(temp.size() != 1)        //如果学生已经存在
            continue;
        values = user.at(0) + ", " + user[1] + ", 6";
        command = "insert into User values (" + values + ", " + time_s + ", 0)";
        //cout << command << endl;
        if(server(command))
            continue;
        num++;
        values = user.at(0) + ", 0";
        for(i = 2; i < user.size(); i++)
            values += ", " + user.at(i);
        command = "insert into 用户信息表 values (" + values + ")";
        //cout << command << endl;
        if(server(command))
            continue;
    }
    while(1);
    file.close();
    return "导入成功";
}

string add_books(string path, string mngid, int & num)
//增加图书,book顺序：ISBN, 数量, 书名, 类别, 编著人, 出版社
{
    int i, smax = 0, j, tpnum;
    vector<string> book;
    vector<vector<string> > temp;
    string input, command, values, time_s;

    fstream file(path);
    if(!file.is_open())
        return "读取文件错误";

    unsigned char  s2;
    file.read((char*)&s2, sizeof(s2));//读取第一个字节，然后左移8位
    int p = s2<<8;
    file.read((char*)&s2, sizeof(s2));//读取第二个字节
    p +=s2;
    if(p != 0xefbb)
        return "不是utf8编码";
    file.seekg(0, ios::beg);
    int line = 1;
    getline(file, input);
    do
    {
        getline(file, input);
        if(file.eof())
            break;
        line++;
        cut_by_reg(input, "\\s*,\\s*", book);
        if(book.size() != 6)
            return "第" + convert<string>(line) + "行格式不正确";
        for(int j = 0; j < 6; j++)
            if(book[j].empty())
                return "第" + convert<string>(line) + "行格式不正确";
        tpnum = convert<int>(book[1]);
        if(tpnum <= 0 || tpnum > 10)
            return "第" + convert<string>(line) + "行书本数量超过上限请改正格式或分行";
        for(i = 0; i < book.size(); i++)
            if(book[i].size() > 60)
                return "第" + convert<string>(line) + "行字符串长度不能大于60";
    }
    while(1);
    file.close();
    file.open(path);
    file.seekg(0, ios::beg);
    getline(file, input);
    time_s = get_ntime();
    norm_val(time_s);
    norm_val(mngid);
    num = 0;
    do
    {

        getline(file, input);
        if(file.eof())
            break;
        cut_by_reg(input, "\\s*,\\s*", book);
        if(book.size() < 2)
            continue;
        tpnum = convert<int>(book[1]);
        if(tpnum <= 0)
            continue;
        for(i = 0; i < book.size(); i++)
        {
            norm_val(book.at(i));
            if(book[i].length() >= 60)
                book[i] = book[i].substr(0, 60);
        }

        command = "select ISBN from 图书信息表 where ISBN = " + book.at(0);
        if(server(command, temp))
            continue;
        //1
        if(temp.size() == 1)
        {
            values = book.at(0);
            values += ", " + time_s + ", " + mngid;
            for(i = 2; i < book.size(); i++)
                values += ", " + book.at(i);

            command = "insert into 图书信息表 values (" +  values + ")";
            if(server(command))
                continue;
            smax = 1;
        }
        else
        {
            command = "select 单本编号 from 单本表 where ISBN = " + book.at(0);
            if(server(command, temp))
                continue;
            if(temp.size() < 2)
                continue;
            for(i = 1, smax = 1; i < temp.size(); i++)
                if(temp[i].size() > 0)
                {
                    j = convert<int>(temp[i][0]);
                    if(j >= smax)
                        smax = j + 1;
                }
        }
        //0
        for(i = 0; i < tpnum; i++)
        {
            command = "insert into 单本表 values (" + book.at(0) + ", " + convert<string>(smax) + ", 2)";
            if(server(command))
                continue;
            smax++;
            num++;
        }
    }
    while(1);
    file.close();
    return "导入成功";
}
