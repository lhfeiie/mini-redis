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

    // 循环收发：一直服务这个客户端，直到它断开
    char buf[1024];
    while(true)
    {
        int bytes = server.recvData(client_fd, buf, sizeof(buf));

        if (bytes == 0)
        {
            // 客户端正常断开
            break;
        }
        if (bytes == -1)
        {
            // 出错
            break;
        }

        // Echo: 把收到的内容原样发回去
        server.sendData(client_fd, std::string(buf, bytes));
    }

    
    close(client_fd);
    std::cout << "client_fd 已关闭" << std::endl; 
    return 0;
}