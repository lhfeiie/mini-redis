#include <iostream>
#include <vector>
#include <string>
#include <memory>

void printVector(const std::string& name, const std::vector<int>& v)
{
    std::cout << name << ": 大小=" << v.size();
    if (!v.empty())
    {
        std::cout << ", 首元素=" << v[0];
    }
    else
    {
        std::cout << ", （已被移走，为空）";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "=== 拷贝 vs 移动 ===" << std::endl;

    // 拷贝：数据被完整复制，a不变
    std::vector<int> a = {1, 2, 3, 4, 5};
    std::vector<int> b = a;         // 拷贝构造
    printVector("a（拷贝后）", a);  // a 仍然有数据    
    printVector("b（拷贝所得）", b);// b 也有数据

    std::cout << std::endl;

    // 移动：数据被“偷走”，a变空
    std::vector<int> c = {10, 20, 30, 40, 50};
    std::vector<int> d = std::move(c);  // 移动构造
    printVector("c（移动后）", c);      // c已被掏空
    printVector("d（移动所得）", d);    // d拥有数据

    std::cout << std::endl;

    // unique_ptr 也只能移动，不能拷贝
    std::cout << "=== unique_ptr 的移动 ===" << std::endl;
    std::unique_ptr<int> p1 = std::make_unique<int>(42);
    std::cout << "移动前 p1：" << *p1 << std::endl;

    std::unique_ptr<int> p2 = std::move(p1); // 移交所有权
    std::cout << "移动后 p1 为空：" << (p1 == nullptr ? "是" : "否") << std::endl;
    std::cout << "移动后 p2：" << *p2 << std::endl;

    return 0;
}
