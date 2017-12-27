#ifndef GLOBAL_H
#define GLOBAL_H
#include <string>

#define HEIGHT 100
#define MAXLENGTH 20
#define WIDTH 200
using namespace std;

extern int user_Type;
extern int user_rank;
extern std::string sUser;
extern std::string sPwd;
extern void outfilechar(char* str);
extern void outfileint(int str);
extern void outfilestring(string str);
extern void outfilelong(long long  str);

#endif // GLOBAL_H
