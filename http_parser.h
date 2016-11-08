#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H

#endif // HTTP_PARSER_H
#include <string>
#include <iostream>
#include <tins/tins.h>
using namespace std;
using namespace Tins;

class Request_Line{
public:
    string method;
    string path;
    string version;
    string Lines[10];
    string domain;
public:
    Request_Line(); //init
    string Get_Line(string request); //Line get
    void request_line_parser(string line);
    bool request_option();
    void Request(string request);
    string request_Lines();
};
