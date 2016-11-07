#include "http_parser.h"

void Request_clear(){
    cnt = 0;
    Get.clear();
    Path.clear();
    Version.clear();
}
void Get_Request_Line(string request){
    request.substr(0, request.find("\r\n"));
}
