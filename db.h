#ifndef DB_H
#define DB_H

#endif // DB_H
#include <iostream>
#include <string.h>
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
    void DB_insert(int year, int mon, int day, int hour, int min, int sec, string eth, string ip, string total);
    void DB_Close();
};
