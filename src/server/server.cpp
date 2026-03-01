// src/server/server.cpp
#include "server.h"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

Server::Server(int port) : port_(port), server_fd_(-1)
{
    // 构造函数：只初始化成员变量，不做 socket 操作
    // socket 操作在 init() 里做，方便处理错误返回值
}

Server::~Server()
{
    if (server_fd_ != -1)
    {
        close(server_fd_);
        std::cout << "server_fd 已关闭" << std:: endl;
    }
}

bool Server::init()
{
    // 第一步：创建socket
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd_ == -1)
    {
        std::cerr << "socket() 失败" << std::endl;
        return false;
    }
    std::cout << "socket 创建成功，fd = " << server_fd_ << std::endl;

    // 第二步：SO_REUSEADDR，防止服务器关闭后处于等待状态期间无法重启
    int opt = 1;
    setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 第三步：配置地址
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family         = AF_INET;
    addr.sin_port           = htons(port_);
    addr.sin_addr.s_addr    = INADDR_ANY;

    // 第四步：bind
    if (bind(server_fd_, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    {
        std::cerr << "bind() 失败" << std::endl;
        return false;
    }
    std::cout << "bind 成功，端口" << port_ << std::endl;

    // 第五步：listen
    if (listen(server_fd_, 5) == -1)
    {
        std::cerr << "listen() 失败" << std::endl;
        return false;
    }
    std::cout << "开始监听..." << std::endl;

    return true;
}