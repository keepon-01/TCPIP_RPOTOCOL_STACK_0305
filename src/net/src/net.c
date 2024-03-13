#include "net.h"
#include "exmsg.h"
#include "net_plat.h"
net_err_t net_init(void)
{   
    //init process base different platform
    net_plat_init();
    //init exchange messages
    exmsg_init();
    return NET_ERR_OK;
}

net_err_t net_start(void)
{   
    exmsg_start();
    return NET_ERR_OK;
}