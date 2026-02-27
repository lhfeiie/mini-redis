#include <iostream>
#include <string>

// 函数模板：求较大值
template <typename T>
T myMax(T a, T b)
{
    return a > b ? a : b;
}

// 函数模板：打印数组
template <typename T>
void printArray(const T* arr, int size)
{
    std::cout << "[";
    for (int i = 0; i < size; ++ i)
    {
        std::cout << arr[i];
        if (i < size - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

// 类模板：通用容器 Box
template <typename T>
class Box
{
public:
    Box(T value) : value_(value)
    {
        std::cout << "Box 创建，存入值" << std::endl;
    }

    T get() const 
    {
        return value_;
    }
    void set(T value)
    {
        value_ = value;
    }
    void print() const
    {
        std::cout << "Box 里的值：" << value_ << std::endl;
    }

private:
    T value_;
};

int main() {
    
    // 函数模板演示
    std::cout << "=== 函数模板 ===" << std::endl;
    std::cout << "max(3, 5) = " << myMax(3, 5) << std::endl;
    std::cout << "max(3.14, 2.71) = " << myMax(3.14, 2.71) << std::endl;
    std::cout << "max('a', 'z') = " << myMax('a', 'z') << std::endl;

    // printArray 模板演示
    std::cout << "\n=== printArray 模板 ===" << std::endl;
    int    ints[]    = {1, 2, 3, 4, 5};
    double doubles[] = {1.1, 2.2, 3.3};
    printArray(ints, 5);
    printArray(doubles, 3);

    // 类模板演示
    std::cout << "\n=== 类模板 ===" << std::endl;
    Box<int>         intBox(42);
    Box<std::string> strBox(std::string("Hello Template"));

    intBox.print();
    strBox.print();

    intBox.set(100);
    std::cout << "修改后：" << intBox.get() << std::endl;

    return 0;
}
