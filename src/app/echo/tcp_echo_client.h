﻿/**
 * @brief 简单的tcp echo 客户端程序
 * @note 该程序仅限在Mac和Linux编程上编译通过，Windows由于套接字接口不同编译会失败
 */
#ifndef TCP_ECHO_CLIENT_H
#define TCP_ECHO_CLIENT_H

int tcp_echo_client_start(const char* ip, int port);

#endif // TECHO_H
