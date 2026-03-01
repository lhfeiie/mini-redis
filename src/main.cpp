// src/main.cpp
#include <iostream>
#include "server/server.h"

int main ()
{
    std::cout << "Mini-Redis 启动中..." << std::endl;

    Server server(6379);

    if (!server.init())
    {
        std::cerr << "服务器初始化失败" << std::endl;
        return 1;
    }

    std::cout << "等待客户端连接..." << std::endl;

    // 接受一个客户端连接
    int client_fd = server.acceptClient();
    if (client_fd == -1)
    {
        return 1;
    }

    // 收数据
    char buf[1024];
    int bytes = server.recvData(client_fd, buf, sizeof(buf));

    // 发数据（固定回复，Day 20 改成 echo）
    if (bytes > 0)
    {
        server.sendData(client_fd, "+PONG\r\n");
    }
    
    close(client_fd);
    std::cout << "client_fd 已关闭" << std::endl; 
    return 0;
}