#include <iostream>
#include <process.h>
#include <windows.h>
using namespace std;
//验证了饿汉式的单例模式是线程安全的
class Singelton {
private:
    Singelton() {
        m_count++;
        printf("Singelton begin\n");
        Sleep(1000);                            // 加sleep为了放大效果
        printf("Singelton end\n");
    }
    static Singelton* single;
public:
    static Singelton* GetSingelton();
    static void print();
    static int m_count;
};
// 饿汉模式的关键：初始化即实例化
Singelton* Singelton::single = new Singelton;
int Singelton::m_count = 0;

Singelton* Singelton::GetSingelton() {
    // 不再需要进行实例化
    //if(single == nullptr){
    //    single = new Singelton;
    //}
    return single;
}

void Singelton::print() {
    cout << m_count << endl;
}
// 回调函数
void threadFunc(void* p) {
    DWORD id = GetCurrentThreadId();        // 获得线程id
    cout << id << endl;
    Singelton::GetSingelton()->print();      // 构造函数并获得实例，调用静态成员函数
}

int main(int argc, const char* argv[]) {
    int threadNum = 3;
    HANDLE threadHdl[100];

    // 创建3个线程
    for (int i = 0; i < threadNum; i++) {
        threadHdl[i] = (HANDLE)_beginthread(threadFunc, 0, nullptr);
    }

    // 让主进程等待所有的线程结束后再退出
    for (int i = 0; i < threadNum; i++) {
        WaitForSingleObject(threadHdl[i], INFINITE);
    }
    cout << "main" << endl;                 // 验证主进程是否是最后退出
    return 0;
}