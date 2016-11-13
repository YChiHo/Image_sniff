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
        fprintf(stderr, "Failed to mysql_query : %s\n", mysql_error(&mysql));
        exit(1);
    }
    else cout<<"USE joongbu\n";
}

void DB::DB_insert(){

}

void DB::DB_loaddata(){

}

void DB::DB_Close(){
    mysql_close(&mysql);
}
