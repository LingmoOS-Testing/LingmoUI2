/*
 * (C) Copyright 2024 Elysia. All Rights Reserved.
 * Description: singleton.hpp
 * Author: Elysia <c.elysia@foxmail.com>
 * Original author: 朱子楚
 * Date: 24-7-17
 * Modify Record:
 */
#ifndef SINGLETON_HPP
#define SINGLETON_HPP

/**
 * @brief The Singleton class
 */
template <typename T>
class Singleton {
public:
    static T *getInstance();
};

template <typename T>
T *Singleton<T>::getInstance() {
    static T *instance = new T();
    return instance;
}

#define SINGLETON(Class)                                                                           \
private:                                                                                           \
    friend class Singleton<Class>;                                                                 \
                                                                                                   \
    public:                                                                                            \
    static Class *getInstance() {                                                                  \
        return Singleton<Class>::getInstance();                                                    \
}

#endif // SINGLETON_HPP
