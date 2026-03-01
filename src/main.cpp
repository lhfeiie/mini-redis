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

    std::cout << "服务器初始化成功，fd = " << server.getFd() << std::endl;
    std::cout << "（本次只测试 socket/bind/listen, accept 下一天实现）" << std::endl;

    return 0;
    // main 返回时，server 对象析构，server_fd 自动关闭 ← RAII！
}