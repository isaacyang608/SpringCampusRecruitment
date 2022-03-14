#include <iostream>
#include <process.h>
//#include <windows.h>
#include <pthread.h>
using namespace std;

class singleton
{
protected:
    singleton()
    {
        // ≥ı ºªØ
        pthread_mutex_init(&mutex);
    }
private:
    static singleton* p;
public:
    static pthread_mutex_t mutex;
    static singleton* initance();
};

pthread_mutex_t singleton::mutex;
singleton* singleton::p = NULL;
singleton* singleton::initance()
{
    if (p == NULL)
    {
        // º”À¯
        pthread_mutex_lock(&mutex);
        if (p == NULL)
            p = new singleton();
        pthread_mutex_unlock(&mutex);
    }
    return p;
}