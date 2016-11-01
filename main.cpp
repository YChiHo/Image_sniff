#include <iostream>
#include <string>
#include <iomanip>
#include <pcap.h>
using namespace std;
#define pcap_src_if_string "rpcap://"
#define BUFSIZ 65536
int main(int argc, char **argv){
    pcap_t *handle;
    char *dev, *net, *mask;
    int ret = 0, i = 0, inum = 0, num = 0;
    pcap_if_t *alldevs, *d;
    char errbuf[PCAP_ERRBUF_SIZE];
    bpf_u_int32 netp, maskp;
    //struct in_addr addr;

    ret = pcap_findalldevs(&alldevs, errbuf);

    if (ret == -1) {
            printf("pcap_findalldevs: %s\n", errbuf);
            exit(1);
    }
    for (d = alldevs; d; d = d->next) {
        printf("%d. %s\n    ", ++i, d->name);
        if (d->description)	printf(" (%s)\n", d->description);
        else printf(" (no description available)\n");
    }
    cout << "select number : ";
    cin >> num;
    for (d = alldevs, i = 0; i < num - 1; d = d->next, i++);
    if ((handle = pcap_open_live(d->name, BUFSIZ, 0, 1, errbuf)) == NULL) {	//장치이름, 패킷캡쳐부분, promiscuous mode, 시간, 에러버퍼
        fprintf(stderr, "Couldn't open device %s: %s\n", d->name, errbuf);
        return(2);
    }
}
