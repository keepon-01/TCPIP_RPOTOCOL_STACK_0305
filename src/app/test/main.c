#include <stdio.h>
#include "sys_plat.h"

int main(void)
{
    pcap_t * pcap = pcap_device_open(netdev0_phy_ip, netdev0_hwaddr);
    while(pcap)
    {
        //prepare for packet content
        static uint8_t buffer[1024];
        for(int i = 0; i < sizeof(buffer); i++)
        {
            buffer[i] = i;
        }

        if(pcap_inject(pcap, buffer, sizeof(buffer)) == -1)
        {
            plat_printf("pcap send: send packet failed %s/n", pcap_geterr(pcap));
            break;
        }
        sys_sleep(10);

    }
    printf("hello, world");
}