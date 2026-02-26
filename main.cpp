#include <iostream>
#include <memory>

// 用来演示的简单类
class Resource
{
public:
    Resource(int id) : id_(id)
    {
        std::cout << "Resource " << id_ << " 创建了" << std::endl;
    }
    ~Resource()
    {
        std::cout << "Resource " << id_ << " 销毁了" << std::endl;
    }
    int getId() const
    {
        return id_;
    }
private:
    int id_;
};

int main() {
    std::cout << "=== unique_ptr 演示 ===" << std::endl;
    {
        std::unique_ptr<Resource> p1 = std::make_unique<Resource>(1);
        std::cout << "p1 管理的资源id：" << p1->getId() << std::endl;
        // 离开这个{}作用域时，p1自动销毁Resource 1
    }
    std::cout << "p1 已离开作用域" << std::endl;

    std::cout << "\n=== shared_ptr 演示 ===" << std::endl;
    {
        std::shared_ptr<Resource> p2 = std::make_shared<Resource>(2);
        std::cout << "引用计数：" << p2.use_count() << std::endl;   // 1
        {
            std::shared_ptr<Resource> p3 = p2;
            std::cout << "引用计数：" << p2.use_count() << std::endl;   // 2
            std::cout << "p3 管理的资源 id：" << p3->getId() << std::endl;
        }   // p3离开作用域，引用计数-1
        std::cout << "p3 离开后引用计数：" << p2.use_count() << std::endl;  // 1
    }
    std::cout << "p2 已离开作用域" << std::endl;
    
    return 0;
}
