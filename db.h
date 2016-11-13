#ifndef DB_H
#define DB_H

#endif // DB_H
#include <iostream>
#include <mysql/mysql.h>
#include <time.h>
using namespace std;
class DB{
private:
    const char* ID;
    const char* PW;
public:
    MYSQL mysql;
public:
    DB();
    void DB_set();
    void DB_insert();
    void DB_loaddata();
    void DB_Close();
};
