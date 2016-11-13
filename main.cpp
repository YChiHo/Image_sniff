#include"http_parser.h"
#include"db.h"
#include<time.h>
using namespace std;
using namespace Tins;
string save_path = "wget -P /root/Documents/pic ";
time_t time_;
struct tm *c_time;
struct packet{

    void snf_set(char *arg){
        SnifferConfiguration config;
        config.set_promisc_mode(true);
        config.set_filter("tcp");
        Sniffer sniffer(arg, config);
        sniffer.sniff_loop(make_sniffer_handler(this, &packet::handle));
    }

    bool handle(PDU& pdu){
        const EthernetII &eth = pdu.rfind_pdu<EthernetII>();
        const IP &ip = pdu.rfind_pdu<IP>();
        const TCP &tcp = pdu.rfind_pdu<TCP>();
        const RawPDU &rp = pdu.rfind_pdu<RawPDU>();
        const RawPDU::payload_type &pay_t = rp.payload();
        if(tcp.dport() == 80)
            http_parse((char*)pay_t.data(), eth, ip, tcp);
        return true;
    }

    bool http_parse(char *payload, EthernetII eth, IP ip, TCP tcp){
        string total;
        string data = payload;
        string data2 = payload;
        string tmp;
        Request_Line rl;
        Request_Line();
        tmp = rl.Get_Line(data);
        rl.request_line_parser(tmp);
        if(rl.isPicture(rl.path)){
            if(rl.request_option()){
                rl.Request(data);
                total = rl.domain + rl.path;
                print(eth, ip, tcp, total);
            }
        }
        return true;
    }

    void print(EthernetII eth, IP ip, TCP tcp, string total){
        cout<<"*********************************************\n";
        cout<<"Packet Start\n";
        cout<<"Src : "<<hex<<eth.src_addr()<<"     "<<dec<<ip.src_addr()<<"\n";
        cout<<"Dst : "<<hex<<eth.dst_addr()<<"     "<<dec<<ip.dst_addr()<<"\n";
        cout<<"TCP size : "<<tcp.size()<<"\n";
        cout<<"Packet End\n";
        cout<<"*********************************************\n";
        DB_(eth.src_addr().to_string(), ip.src_addr().to_string(), total);
        //system(total.c_str());
    }

    void DB_(string eth, string ip, string total){
        time(&time_);
        c_time = localtime(&time_);
        DB db;
        DB();
        db.DB_set();
        db.DB_insert(c_time->tm_year, c_time->tm_mon, c_time->tm_mday, c_time->tm_hour, c_time->tm_min, c_time->tm_sec, eth, ip, total);
    }
};

int main(int argc, char *argv[]){
    if(argc < 2)
        cout << "Image_sniff [interface]\n"<<"Example : Image_sniff eth0\n";
    packet pk;
    pk.snf_set(argv[1]);

}
