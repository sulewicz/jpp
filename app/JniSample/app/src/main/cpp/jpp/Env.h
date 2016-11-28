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

        Cache &get_cache();
        JNIEnv *get_jenv();

        Class find_class(const char *name);

        Class wrap(jclass _jclass);
        Object wrap(jobject _jobject);
        Array<Object> wrap(jobjectArray _jobjectArray);
        Array<jbyte> wrap(jbyteArray _jobjectArray);

        Array<Object> create_array(size_t size, Class& element_class);
        template<class Type>
        Array<Type> create_array(size_t size, Type* type = nullptr);

        // Casted wraps
        Object wrap(const char *name, jobject);
        Object wrap(Class &_class, jobject);
        template<class Ret>
        Array<Ret> wrap(Class &_class, jarray _array) {
            return Array<Ret>(_class, _array);
        }

        Class get_superclass(Class &_class);

        jmethodID find_method_id(Class &_class, const char *name, const char *signature);
        Object call_method(Object &object, const char *method_name,
                           const char *signature, va_list vl);
        void call_method(Object &object, const char *method_name,
                         const char *signature, va_list vl, void *type);
        template<class Ret>
        Ret call_method(Object &object, const char *method_name,
                        const char *signature, va_list vl, Ret type = Ret());

        jmethodID find_static_method_id(Class &_class, const char *name, const char *signature);
        Object call_static_method(Class &_class, const char *method_name,
                           const char *signature, va_list vl);
        void call_static_method(Class &_class, const char *method_name,
                         const char *signature, va_list vl, void *type);
        template<class Ret>
        Ret call_static_method(Class &_class, const char *method_name,
                        const char *signature, va_list vl, Ret type = Ret());

    private:
        JNIEnv *const m_jenv;
        Cache &m_cache;
        jmethodID m_get_name_method_id = nullptr;
    };
}