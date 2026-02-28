#include <iostream>
#include <sys/socket.h> // socket, bind, listen, accept
#include <netinet/in.h> // sockaddr_in
#include <unistd.h>     // close, read, write
#include <cstring>      // memset

int main ()
{
    // 第一步：创建 socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        std::cerr << "socket 创建失败" << std::endl;
        return 1;
    }
    std::cout << "socket 创建成功，fd = " << server_fd << std::endl;

    // 第二步：配置地址结构体
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));         // 先清零，防止垃圾数据
    addr.sin_family         = AF_INET;      // IPv4
    addr.sin_port           = htons(6379);  // 端口号（Redis默认端口）
    addr.sin_addr.s_addr    = INADDR_ANY;   // 监听所有网络接口

    // 设置 SO_REUSEADDR，解决 TIME_WAIT 导致的 bind 失败问题
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));                                       

    // 第三步：绑定端口
    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    {
        std::cerr << "bind 失败" << std::endl;
        return 1;
    }
    std::cout << "bing 成功，端口 6379" << std::endl;

    // 第四步：开始监听
    if (listen(server_fd, 5) == -1)
    {
        std::cerr << "listen 失败" << std::endl;
        return -1;
    }
    std::cout << "开始监听，等待客户连接..." << std::endl;

    // 第五步：接受连接
    int client_fd = accept(server_fd, nullptr, nullptr);
    if (client_fd == -1)
    {
        std::cerr << "accept 失败" << std::endl;
        return 1;
    }
    std::cout << "客户端已连接！client_fd = " << client_fd << std::endl;

    // 第六步：接收数据
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    int bytes = read(client_fd, buffer, sizeof(buffer) - 1);
    std::cout << "收到数据（" << bytes << " 字节）：" << buffer << std::endl;

    // 第七步：关闭连接
    close(client_fd);
    close(server_fd);
    std::cout << "连接已关闭" << std::endl;

    return 0;
}