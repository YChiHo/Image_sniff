#include "http_parser.h"
#include <string>
#include <iostream>
#include <tins/tins.h>

Request_Line::Request_Line(){
    method.clear();
    path.clear();
    version.clear();
}

string Request_Line::Get_Line(string request){
    string line;
    line = request.substr(0, request.find("\r\n"));
    return line;
}

void Request_Line::request_line_parser(string line){
    int status, cnt = 0;
    while(true){
        if(line.find(" ") != string::npos ){

            status = line.find(" ");
            method = line.substr(0, status);
            line.erase(0, status);

            status = line.find(" ");
            path = line.substr(0, status);
            line.erase(0, status);

            status = line.find(" ");
            version = line.substr(0, status);
            line.erase(0, status);

            ++cnt;
        }
        else if(cnt > 3 || line.find(" ") != string::npos) {
            cnt = 0;
            break;
        }
    }
}

bool Request_Line::request_option(){
    if(     method == "GET "   ||
            method == "POST "  ||
            method == "HEAD "  ||
            method == "PUT "   ||
            method == "DELETE "||
            method == "TRACE "  ){
        return true;
    }
    else false;
}

void Request_Line::Request(string request){
    int status;
    for(int i = 0;i < 10;i++) {
        if(Lines[i].empty()) break;
        Lines[i].clear();
        Lines[i] = request.substr(0, request.find("\r\n"));
        status = request.find("\r\n");
        request.erase(0, status);
    }
    request_Lines();
}
string Request_Line::request_Lines(){
    int status;
    for(int i = 0;i < 10;i++){
        if((status = Lines[i].find("Host: ")) != string::npos){
            domain = Lines[i].substr(status + 6, Lines[i].find("\r\n"));

        }
    }
}

