#include <iostream>

// 1. 接口类
class Subject {
public:
    virtual void request() = 0;
    virtual ~Subject() {}
};

// 2. 真实类
class RealSubject : public Subject {
public:
    void request() override {
        std::cout << "RealSubject: Handling request." << std::endl;
    }
};

// 3. 代理类
class Proxy : public Subject {
private:
    RealSubject* realSubject;

    bool checkAccess() {
        // 在这里可以添加访问控制逻辑
        std::cout << "Proxy: Checking access prior to firing a real request." << std::endl;
        return true;
    }

    void logAccess() {
        // 记录请求的日志
        std::cout << "Proxy: Logging the time of request." << std::endl;
    }

public:
    Proxy(RealSubject* realSubject) : realSubject(new RealSubject(*realSubject)) {}
    ~Proxy() {
        delete realSubject;
    }

    void request() override {
        if (this->checkAccess()) {
            this->realSubject->request();
            this->logAccess();
        }
    }
};

// 客户端代码
int main() {
    std::cout << "Client: Executing the client code with a real subject:" << std::endl;
    RealSubject* realSubject = new RealSubject();
    realSubject->request();

    std::cout << "\nClient: Executing the same client code with a proxy:" << std::endl;
    Proxy* proxy = new Proxy(realSubject);
    proxy->request();

    delete realSubject;
    delete proxy;
    return 0;
}
