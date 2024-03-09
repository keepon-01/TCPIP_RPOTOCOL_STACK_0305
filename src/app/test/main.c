#include <stdio.h>
#include "sys_plat.h"

static sys_sem_t sem;
void thread1_entry(void * arg)
{
    while (1)
    {
        plat_printf("this is thread1 %s\n", (char *)arg);
        sys_sleep(1000);
        sys_sem_notify(sem);
        sys_sleep(1000);
    }
}

void thread2_entry(void * arg)
{
    while (1)
    {   
        //0 value means wait all the time
        sys_sem_wait(sem, 0);
        plat_printf("this is thread2 %s\n", (char *)arg);
    }
}
int main(void)
{   
    //0 value means stop thead2 from start moment
    sem = sys_sem_create(0);
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