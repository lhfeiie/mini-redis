#include <iostream>

int add(int a, int b)
{
    int result = a + b;
    return result;
}

int main() {
    int x = 10;
    int y = 20;
    int sum = add(x, y);
    std::cout << "sum = " << sum << std::endl;

    // 故意制造一个问题：访问空指针
    int* ptr = nullptr;
    std::cout << "ptr的值：" << *ptr << std::endl;  // 这行会崩溃
    return 0;
}
