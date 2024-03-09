#include <stdio.h>
#include "sys_plat.h"

void thread1_entry(void * arg)
{
    while (1)
    {
        plat_printf("this is thread1 %s\n", (char *)arg);
        sys_sleep(100);
    }
}

void thread2_entry(void * arg)
{
    while (1)
    {
        plat_printf("this is thread2 %s\n", (char *)arg);
        sys_sleep(100);
    }
}
int main(void)
{   
    //thread example
    sys_thread_create(thread1_entry, "aaaa");
    sys_thread_create(thread2_entry, "bbbb");


    pcap_t * pcap = pcap_device_open(netdev0_phy_ip, netdev0_hwaddr);
    while(pcap)
    {
        //prepare for packet content
        static uint8_t buffer[1024];
        for(int i = 0; i < sizeof(buffer); i++)
        {
            buffer[i] = i;
        }

        //receive packets
        struct pcap_pkthdr  *pkthdr;
        const uint8_t * pkt_data;
        if(pcap_next_ex(pcap, &pkthdr, &pkt_data) != 1)
        {
            continue;
        }

        int len = pkthdr->len > sizeof(buffer) ? sizeof(buffer) : pkthdr->len;
        plat_memcpy(buffer, pkt_data, len);
        buffer[0] = 1;
        buffer[1] = 2;


        if(pcap_inject(pcap, buffer, sizeof(buffer)) == -1)
        {
            plat_printf("pcap send: send packet failed %s/n", pcap_geterr(pcap));
            break;
        }
        sys_sleep(10);

    }
    printf("hello, world");
}