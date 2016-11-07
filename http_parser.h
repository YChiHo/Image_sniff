#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

#endif // HTTP_PARSER_H
#include <string>
#include <iostream>
#include <tins/tins.h>
using namespace std;
using namespace Tins;

class Get_Request_Line{
public:
    int cnt;
    string Get;
    string Path;
    string Version;
public:
    Get_Request_Line(string request);
    void Request_clear();
};
