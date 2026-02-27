#include <iostream>
#include <fstream>
#include <stdexcept>

// RAII 文件管理类
class FileGuard
{
public:
    // 构造函数：获取资源（打开文件）
    FileGuard(const std::string& filename, const std::string& mode)
    {
        if (mode == "write")
        {
            file_.open(filename, std::ios::out);
        }
        else
        {
            file_.open(filename, std::ios::in);
        }
        if (!file_.is_open())
        {
            throw std::runtime_error("无法打开文件：" + filename);
        }
        std::cout << "文件已打开：" << filename << std::endl;
    }

    // 析构函数：释放资源（关闭文件）
    ~FileGuard()
    {
        if (file_.is_open())
        {
            file_.close();
            std::cout << "文件已自动关闭" << std::endl;
        }
    }

    // 禁止复制（防止两个对象管理同一文件）
    FileGuard(const FileGuard&) = delete;
    FileGuard& operator=(const FileGuard&) = delete;

    // 写入内容
    void write(const std::string& content)
    {
        file_ << content << std::endl;
    }

private:
    std::fstream file_;
};

int main() {
    // std::cout << "=== RAII 演示 ===" << std::endl;

    // {
    //     FileGuard fg("test.txt", "write");
    //     fg.write("Hello, RAII!");
    //     fg.write("资源会自动释放");
    //     std::cout << "写入完成，即将离开作用域..." << std::endl;
    // }   // fg离开作用域，析构函数自动关闭文件

    // std::cout << "已离开作用域，文件已被自动关闭" << std::endl;

    std::cout << "=== RAII 异常安全演示 ===" << std::endl;
    
    try
    {
        FileGuard fg("test.txt", "write");
        fg.write("第一行");

        // 模拟中途发生异常
        throw std::runtime_error("模拟业务逻辑出错！");

        fg.write("这行永远不会执行");
    }
    catch(const std::exception& e)
    {
        std::cerr << "捕获到异常：" << e.what() << '\n';
    }
    
    std::cout << "程序继续运行，文件已被自动关闭" << std::endl;
    return 0;
}
