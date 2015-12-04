#ifndef CPP_DEMO_UTIL_NONCOPYABLE_H
#define CPP_DEMO_UTIL_NONCOPYABLE_H

template <typename T>
class Singleton
{
public:
    Singleton(Singleton &other) = delete;
    Singleton& operator= (Singleton &other) = delete;
    Singleton(Singleton &&moved) = delete;

    inline static T* getInstance();

protected:
    Singleton() {}
    virtual ~Singleton() {}

    virtual void destroyInstance()
    {
        if (instance_)
        {
            delete instance_;
            instance_ = nullptr;
        }
    }

private:
    static T    *instance_;
};

template <typename T>
T * Singleton<T>::instance_ = nullptr;

template <typename T>
inline T* Singleton<T>::getInstance()
{
    if (!instance_)
    {
        instance_ = new T();
    }
    return instance_;
}

#endif