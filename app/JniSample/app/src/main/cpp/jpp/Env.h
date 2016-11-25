#pragma once

#include <jni.h>
#include <string>
#include "Object.h"
#include "Array.h"

namespace jpp {
    class Cache;
    class Class;

    class Env {
    public:
        Env(JNIEnv *jenv);
        Env(JNIEnv *jenv, Cache &cache);
        ~Env();

        Cache& get_cache();
        JNIEnv *get_jenv();

        Class find_class(const char *name);
        Class wrap(jclass _jclass);
        Object wrap(jobject _jobject);
        Array<Object> wrap(jobjectArray _jobjectArray);
        Array<jbyte> wrap(jbyteArray _jobjectArray);

        // Casted wraps
        Object wrap(const char *name, jobject);
        Object wrap(Class& _class, jobject);
        template <class Ret>
        Array<Ret> wrap(Class& _class, jarray _array) {
            return Array<Ret>(_class, _array);
        }

        Class get_superclass(Class &_class);

    private:
        JNIEnv *const m_jenv;
        Cache &m_cache;
        jmethodID m_get_name_method_id = nullptr;
    };
}
