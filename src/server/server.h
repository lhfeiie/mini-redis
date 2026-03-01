// src/server/server.h
#pragma once    // 防止头文件被重复包含

#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
class Server
{
public:
    // 构造函数：指定监听端口
    Server(int port);

    // 析构函数：关闭server_fd
    ~Server();

    // 初始化：创建 socket，bind，listen
    bool init();

    // 获取 server_fd（供外部使用）
    int getFd() const
    {
        return server_fd_;
    }

    // 等待并接受一个客户端连接，返回 client_fd
    // 失败返回 -1
    int acceptClient();

private:
    int port_;      // 监听端口
    int server_fd_; // 监听 socket 的fd
};