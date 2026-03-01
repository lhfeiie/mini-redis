// src/main.cpp
#include <iostream>
#include <sys/wait.h>
#include <signal.h> 
#include "server/server.h"

int main ()
{
    // 注册 SIGCHLD 信号处理函数
    // 子进程退出时内核自动发 SIGCHLD 给父进程
    // SIG_DFL 改为自定义处理：自动清理所有已退出的子进程
    signal(SIGCHLD, [](int) {
        while(waitpid(-1, nullptr, WNOHANG) > 0);
    });

    std::cout << "Mini-Redis 启动中..." << std::endl;

    Server server(6379);
    if (!server.init())
    {
        std::cerr << "服务器初始化失败" << std::endl;
        return 1;
    }

    std::cout << "等待客户端连接（多进程版）..." << std::endl;

    while(true)
    {
        int client_fd = server.acceptClient();
        if (client_fd == -1)
        {
            break;
        }

        // 来了一个客户端，fork 一个子进程服务它
        pid_t pid = fork();

        if (pid < 0)
        {
            // fork 失败
            std::cerr << "fork() 失败" << std::endl;
            close(client_fd);
            continue;
        }

        if (pid == 0)
        {
            // ===== 子进程 =====
            // 子进程不需要监听 socket，关掉它
            close(server.getFd());

            // 子进程专心服务这个客户端
            char buf[1024];
            while(true)
            {
                int bytes = server.recvData(client_fd, buf, sizeof(buf));
                if (bytes <= 0)
                    break;
                server.sendData(client_fd, std::string(buf, bytes));
            }

            close(client_fd);
            std::cout << "子进程退出，pid=" << getpid() << std::endl;
            return 0;
        }

        // ===== 父进程 =====
        // 父进程不需要 client_fd, 关掉它（子进程会服务这个客户端）
        close(client_fd);
        std::cout << "已 fork 子进程，pid=" << pid << std::endl; 
        // 继续循环，等下一个客户端
    }
    
    return 0;
}