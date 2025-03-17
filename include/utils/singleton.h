#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
#include <mutex>
#include <iostream>

namespace Utils
{
    template <typename T>
    class Singleton
    {
        public:
            Singleton(const Singleton&) = delete;
            Singleton& operator=(const Singleton&) = delete;

            // Get the only instance
            static T& Instance()
            {
                static std::once_flag initFlag;
                std::call_once(initFlag, [](){
                    instance_.reset(new T());
                });
                return *instance_;
            }

            // Destroy the only instance
            static void DestroyInstance()
            {
                instance_.reset(nullptr);
            }

        protected:
            Singleton() = default;
            virtual ~Singleton() = default;

        private:
            static std::unique_ptr<T> instance_;
    };
}

#endif // SINGLETON_H