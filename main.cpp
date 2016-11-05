#include <iostream>
#include <tins/tins.h>
#include <vector>
#include <pthread.h>
using namespace std;
using namespace Tins;
string save_path = "wget -P /tmp/picture ";
vector<string> uri;
pthread_t tid;
struct packet{
    void *t_down(){
        string last = uri.back();
        uri.pop_back();
        system(last.c_str());
    }
    void thread_(){
        pthread_create(&tid, NULL, t_down, (void*)0);
    }

    void snf_set(){
        thread_();
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
        //if(html_parse(rp.payload().data() == true)){
        if(html_parse((char*)pay_t.data())){
            html_parse((char*)pay_t.data());
            print(eth, ip, tcp);
        }
        return true;
    }
    void print(EthernetII eth, IP ip, TCP tcp){
        cout<<"Packet Start\n";
        cout<<"Src : "<<hex<<eth.src_addr()<<"     "<<dec<<ip.src_addr()<<"\n";
        cout<<"Dst : "<<hex<<eth.dst_addr()<<"     "<<dec<<ip.dst_addr()<<"\n";
        cout<<"TCP size : "<<tcp.size()<<"\n";
        cout<<"Packet End\n";
    }
    bool html_parse(char *payload){
        string str = payload;
        string total, domain, pwd;

        if(str.find(".jpg HTTP/1.1") != string::npos){
            pwd = str.substr(str.find("GET")+4, str.find(".jpg HTTP/1.1"));
            domain = str.substr(str.find("Host:")+6, str.find("\r\n")-1);
            if(domain.find("\r\n")!= string::npos)
                domain.erase(domain.find("\r\n"), domain.back());
            total = save_path + domain + pwd;
            cout<<"Total : "<<total<<endl<<endl;
            save_uri(total);
            return true;
        }
        else if(str.find(".png HTTP/1.1") != string::npos){
            pwd = str.substr(str.find("GET")+4, str.find(".png HTTP/1.1"));
            domain = str.substr(str.find("Host:")+6, str.find("\r\n")-1);
            if(domain.find("\r\n")!= string::npos)
                domain.erase(domain.find("\r\n"), domain.back());
            total = save_path + domain + pwd;
            cout<<"Total : "<<total<<endl<<endl;
            save_uri(total);
            return true;
        }
    }
    void save_uri(string total){
        uri.push_back(total);
    }
};

int main(int argc, char **argv){
    packet pk;
    pk.snf_set();
}
