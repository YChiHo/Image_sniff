#include <iostream>
#include <iomanip>
#include <tins/tins.h>
using namespace std;
using namespace Tins;

struct packet{
    void snf_set(){
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
        if(!false){
            print(eth, ip, tcp);
        }
        return true;
    }
    void print(EthernetII eth, IP ip, TCP tcp){
        cout<<"Packet Start\n";
        cout<<"Src : "<<hex<<eth.src_addr()<<setw(5)<<dec<<ip.src_addr()<<"\n";
        cout<<"Dst : "<<hex<<eth.dst_addr()<<setw(5)<<dec<<ip.dst_addr()<<"\n";
        cout<<"Packet End\n";
    }
};

int main(int argc, char **argv){
    packet pk;
    pk.snf_set();
}
