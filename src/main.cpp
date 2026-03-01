// src/main.cpp
#include <iostream>
#include <pthread.h>
#include "server/server.h"

// 线程函数的参数：需要把两样东西传给新线程
struct ClientArgs
{
    Server* server;     // 指向Server对象的指针
    int client_fd;      // 这个客户端的fd
};

// 线程函数：每个线程执行这个函数
// 注意：pthread 规定线程函数的签名必须是 void* func(void*)
void* handleClient(void* arg)
{
    // 把void*转回我们自己定义的类型
    ClientArgs* args = static_cast<ClientArgs*>(arg);
    Server* server = args->server;
    int client_fd = args->client_fd;
    delete args;    // 释放堆上分配的参数结构体（下面解释为什么在堆上）

    char buf[1024];
    while(true)
    {
        int bytes = server->recvData(client_fd, buf, sizeof(buf));
        if (bytes <= 0)
        {
            break;
        }
        server->sendData(client_fd, std::string(buf, bytes));
    }

    close(client_fd);
    std::cout << "线程退出，client_fd=" << client_fd << std::endl;
    return nullptr;
}

int main ()
{
    std::cout << "Mini-Redis 启动中..." << std::endl;

    Server server(6379);
    if (!server.init())
    {
        std::cerr << "服务器初始化失败" << std::endl;
        return 1;
    }

    std::cout << "等待客户端连接（多线程版）..." << std::endl;

    while(true)
    {
        int client_fd = server.acceptClient();
        if (client_fd == -1)
        {
            break;
        }

        // 在堆上分配参数，确保新线程拿到时数据还有效
        ClientArgs* args = new ClientArgs{&server, client_fd};

        pthread_t tid;  // 线程id
        int ret = pthread_create(&tid, nullptr, handleClient, args);

        if (ret != 0)
        {
            std::cerr << "pthread_create() 失败" << std::endl;
            delete args;
            close(client_fd);
            continue;
        }

        // 分离线程：线程结束后自动释放资源，不需要 join 等待
        pthread_detach(tid);
        std::cout << "已创建线程, tid=" << tid << std::endl;
    }
    
    return 0;
}