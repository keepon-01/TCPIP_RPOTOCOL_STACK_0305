#include <stdio.h>
#include "sys_plat.h"
#include "net.h"
#include "netif_pcap.h"

//init netcard
net_err_t netdev_init(void)
{   
    //...
    //every card will have two thread to slove packets
    netif_pcap_open();
    return NET_ERR_OK;
}
int main(void)
{   
    net_init();
    net_start();

    //init netcard after everything are ready, so the packets can sloved correctly
    netdev_init();

    while(1)
    {
        sys_sleep(1);
    }
    return 0;
    
}