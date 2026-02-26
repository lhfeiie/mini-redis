#include <iostream>


int main() {
    
    // === 栈上的变量 ===
    int stack_var = 100;
    std::cout << "栈变量值：" << stack_var << std::endl;
    std::cout << "栈变量地址：" << &stack_var << std::endl;

    // === 堆上的单个变量 ===
    int* heap_var = new int(200);
    std::cout << "堆变量值：" << *heap_var << std::endl;
    std::cout << "堆变量地址：" << heap_var << std::endl;
    delete heap_var;
    heap_var = nullptr;

    // == 堆上的数组 ===
    int* arr = new int[3];
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    for (int i = 0; i < 3; ++ i)
    {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }
    delete[] arr;
    arr = nullptr;

    std::cout << "程序正常结束，内存已释放" << std::endl;
    return 0;
}
