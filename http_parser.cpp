#include "http_parser.h"

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
    string tmp;
    while(true){
        if(line.find(" ") != string::npos ){

            status = line.find(" ");
            method = line.substr(0, status+1);
            line.erase(0, status+1);

            status = line.find(" ");
            path = line.substr(0, status+1);
            line.erase(0, status+1);

            status = line.find(" ");
            version = line.substr(0, status+1);
            line.erase(0, status+1);

            ++cnt;
        }
        if(cnt > 2 || line.find(" ") == string::npos) {
            cnt = 0;
            break;
        }
    }
}
bool Request_Line::isPicture(string path){
    string str = path;
    if(     str.find(".jpg") != string::npos ||
            str.find(".png") != string::npos  ) return true;
    else return false;
}

bool Request_Line::request_option(){
    if(     method == "GET "   ||
            method == "POST "  ||
            method == "HEAD "  ||
            method == "PUT "   ||
            method == "DELETE "||
            method == "TRACE "  )
        return true;
    else return false;
}

void Request_Line::Request(string request){
    int status, i = 0;
    do{
        Lines[i].clear();
        status = request.find("\r\n");
        Lines[i] = request.substr(0, status);
        request.erase(0, status+2);
        i++;
    }while(Lines[i].empty());
    request_Lines();
}
void Request_Line::request_Lines(){
    int status, i;
    for(i = 0;i < 10;i++){
        if((status = Lines[i].find("Host: ")) != string::npos){
            domain = Lines[i].substr(status + 6);
        }
    }
}

