//====================
//
// how use?
// (1)Singleton<Class>::instance(Args...)->publicfun();
// (2)class Ex : public Singleton<Ex>
//
//====================

#ifndef COM_SINGLETON
#define COM_SINGLETON

#include <thread>
#include <mutex>
using namespace std;

#define SINGLETON_INIT(Class) \
    public:\
    Class(){ init(); }\
    virtual ~Class(){ clear(); }\
    protected:\
    virtual void init();\
    virtual void clear();

template<typename T>
class Singleton
{
public:
    template<typename... Args>
    static T* instance(Args&&... arg)
    {
        static std::mutex mutex;
        std::lock_guard<std::mutex> glock(mutex);
        if (m_instance == nullptr)
        {
            m_instance = new T(std::forward<Args>(arg)...);
        }
        return m_instance;
    }

    static void freeinstance()
    {
        static std::mutex mutex;
        std::lock_guard<std::mutex> glock(mutex);
        if (m_instance)
        {
            delete m_instance;
            m_instance = nullptr;
        }
    }

protected:
    Singleton() {}
    virtual ~Singleton() {}
    Singleton(const Singleton&) = delete;
    Singleton& operator = (const Singleton&) = delete;

    virtual void init() = 0;
    virtual void clear() = 0;

private:
    static T* m_instance;
};

template<typename T>
T* Singleton<T>::m_instance = nullptr;

#endif //COM_SINGLETON
