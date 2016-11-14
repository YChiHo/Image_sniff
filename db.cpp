#include"http_parser.h"
#include"db.h"

DB::DB(){
    ID = "root";
    PW = "12345";
}

void DB::DB_set(){
    mysql_init(&mysql);

    if(mysql_real_connect(&mysql, "127.0.0.1", ID, PW, "joongbu", 3306, NULL, 0)) //mysql, IP(localhost), ID, PW, database, port(3306), socket, 0
        cout << "DB Connect Success\t";
    else
        fprintf(stderr, "Failed to Connect : Error %s\n", mysql_error(&mysql));

    if(mysql_query(&mysql, "use joongbu")){
        fprintf(stderr, "Failed to mysql_query : Error %s\n", mysql_error(&mysql));
        exit(1);
    }
    else cout<<"USE joongbu\n";
}

void DB::DB_insert(int year, int mon, int day, int hour, int min, int sec, string eth, string ip, string total){
    char query[500];
    sprintf(query, "insert into info value(%d,%d,%d,%d,%d,%d,'%s','%s','%s')", year+1900, mon+1, day, hour, min, sec, ip.c_str(), eth.c_str(), total.c_str());
    if(mysql_query(&mysql, query)){
        fprintf(stderr, "Failed to query : Error %s\n", mysql_error(&mysql));
        exit(1);
    }
}

void DB::DB_loaddata(){

}

void DB::DB_Close(){
    mysql_close(&mysql);
}
