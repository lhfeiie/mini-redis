# Mini-Redis

从零实现轻量级内存键值数据库，用于深入学习 C++ 系统编程。

## 项目目标

通过亲手实现 Redis 的核心功能，掌握以下计算机基础知识：
- **计算机网络**：TCP、epoll、I/O 多路复用、RESP 协议
- **操作系统**：文件描述符、进程/线程、信号处理
- **数据结构**：哈希表（渐进式 rehash）、跳表、双向链表、LRU
- **C++ 能力**：智能指针、RAII、move 语义、模板

## 开发进度

### ✅ 阶段一：最简 TCP 服务器（已完成）
- TCP echo 服务器：socket/bind/listen/accept/read/write
- Server 类封装，RAII 管理文件描述符
- 多进程方案（fork + SIGCHLD 处理僵尸进程）
- 多线程方案（pthread_create + pthread_detach）
- 理解 C10K 问题，引出 epoll 的必要性

### 🔄 阶段二：epoll 事件驱动改造（进行中）
### ⬜ 阶段三：RESP 协议解析
### ⬜ 阶段四：核心数据结构
### ⬜ 阶段五：命令系统
### ⬜ 阶段六：持久化（RDB + AOF）
### ⬜ 阶段七：高级特性
### ⬜ 阶段八：收尾打磨

## 编译运行
```bash
mkdir build && cd build
cmake ..
make
./mini-redis
```

## 开发环境

- 操作系统：Ubuntu 24.04（WSL2）
- 编译器：g++ 13.3.0
- 构建工具：CMake 3.28 + Make