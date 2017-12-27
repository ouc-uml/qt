#include "connect.h"
#include "md5.h"
#include <sstream>
#include <iostream>
#include <regex>

extern void replace_str(string & str, const string & old_value, const string & new_value);
extern void norm_val(string & val);
template<class out_type,class in_value>
extern out_type convert(const in_value & t);
extern int add_user(vector<string> & user);

extern int delete_user(string id);

extern vector<string> user_info(string userid);
extern vector<string> all_user();
extern int update_user(vector<string> val);

extern int user_lev(string userid, int & level);

extern int update_user_lev(string userid, int level);


extern int add_book(string userid, vector<string> & book);
extern int delete_book(string bno, unsigned int eno);

extern int update_book(vector<string> val);

extern vector<vector<string> > search_Bno(string bno, bool mode);

extern vector<vector<string> > search_Bclm(string clm_name, string val);

extern vector<string> all_book();

extern string add_books(string path, string mngid, int & num);
extern string add_users(string path, int & num);

extern int borrow(string bno, unsigned int eno, string uno, int day);
extern int return_book(string bno, unsigned int eno);
extern int reserve_book(string bno, unsigned int eno, string uno, int day);

extern string recommend(string bno, string bname, string userid);


extern vector<vector<string> > reader_history(string userid);

extern vector<vector<string> > reader_current(string userid);

extern vector<vector<string> > search_recommend(string uno);

extern int read_recommend(string userid, string isbn);





extern int send_message(string userid1, string userid2, string message);

extern vector<string> get_message(string userid);
extern vector<vector<string> > search_res(string uno);//预约记录查询，uno为0为查询所有未处理记录

extern void cut_by_reg(string obj, string reg, vector<string>& res_str);

