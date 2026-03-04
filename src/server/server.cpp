// src/server/server.cpp
#include "server.h"

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

int Server::acceptClient()
{
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_fd = accept(server_fd_, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd == -1)
    {
        std::cerr << "accept() 失败" << std::endl;
        return -1;
    }

    // 打印客户端的 IP 和端口
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, ip, sizeof(ip));
    int port = ntohs(client_addr.sin_port);

    std::cout << "新客户端连接：" << ip << ":" << port << " fd=" << client_fd << std::endl;

    return client_fd;
}

int Server::recvData(int client_fd, char* buf, int buf_size)
{
    // 先把 buf 全部清零，防止上次的数据残留
    memset(buf, 0, buf_size);

    int bytes = read(client_fd, buf, buf_size - 1);

    if (bytes > 0)
    {
        std::cout << "收到数据（" << bytes << " 字节）：" << buf << std::endl;
    }
    else if (bytes == 0)
    {
        std::cout << "客户端主动断开连接" << std::endl;
    }
    else
    {
        std::cerr << "read() 出错" << std::endl;
    }

    return bytes;
}

int Server::sendData(int client_fd, const std::string& msg)
{
    int bytes = write(client_fd, msg.c_str(), msg.size());

    if (bytes == -1)
    {
        std::cerr << "write() 出错" << std::endl;
    }
    else
    {
        std::cout << "已发送（" << bytes << " 字节）：" << msg << std::endl;
    }

    return bytes;
}

void Server::setNonBlocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
    {
        std::cerr << "fcntl(F_GETFL) 失败" << std::endl;
        return;
    }
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
    {
        std::cerr << "fcntl(F_SETFL) 失败" << std::endl;
    }
}