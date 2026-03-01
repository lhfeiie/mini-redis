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

    std::cout << "连接成功！准备收发数据（Day 19 实现）" << std::endl;

    // 暂时直接关闭
    close(client_fd);
    return 0;
}