#include"http_parser.h"
#include"db.h"
#include<time.h>
using namespace std;
using namespace Tins;
string save_path = "wget -P /root/Documents/pic ";

struct tm *c_time(const time_t timer);

struct packet{

    void snf_set(char *arg){
        SnifferConfiguration config;
        config.set_promisc_mode(true);
        config.set_filter("tcp");
        Sniffer sniffer("eth0", config);
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

    void print(EthernetII eth, IP ip, TCP tcp, string total){
        cout<<"**************************************\n";
        cout<<"Packet Start\n";
        cout<<"Src : "<<hex<<eth.src_addr()<<"     "<<dec<<ip.src_addr()<<"\n";
        cout<<"Dst : "<<hex<<eth.dst_addr()<<"     "<<dec<<ip.dst_addr()<<"\n";
        cout<<"TCP size : "<<tcp.size()<<"\n";
        system(total.c_str());
        cout<<"Packet End\n";
        cout<<"**************************************\n";
        DB_send();
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
                total = save_path  + rl.domain + rl.path;
                print(eth, ip, tcp, total);
            }
        }
        return true;
    }

    void DB_send(){
        DB db;
        DB();
        db.DB_set();
    }
};

int main(int argc, char **argv){
    //if(argc < 2)
    //    cout << "snf [interface]\n"<<"example : snf eth0\n";
    packet pk;
    pk.snf_set(argv[1]);
}
