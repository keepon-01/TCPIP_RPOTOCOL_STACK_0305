#ifndef NET_H
#define NET_H

#include "net_err.h"

//init protocol stack
net_err_t net_init(void);
net_err_t net_start(void);

#endif