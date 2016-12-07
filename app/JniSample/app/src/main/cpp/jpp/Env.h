#pragma once

#include <jni.h>
#include <string>
#include "Class.h"
#include "Object.h"
#include "Array.h"

namespace jpp {
    class Cache;

    class Env {
    public:
        Env(JNIEnv *jenv);
        Env(JNIEnv *jenv, Cache &cache);
        ~Env();

        Cache &get_cache();
        JNIEnv *get_jenv();

        bool is_exception_pending();
        Object consume_exception();
        void cancel_exception();
        void check_for_exception();
        bool throw_exception(Object &exception);

        Class find_class(const char *class_name);
        Class find_array_class(const char *class_name);
        Class find_array_class(int dim, const char *class_name);
        template<class Type>
        Class find_array_class(int dim = 1, Type t = 0) {
            char type = internal::type_to_str(t);
            auto class_name = std::string(dim, '[') + type;
            return find_class(class_name.c_str());
        }

        Class wrap(jclass _jclass);
        Object wrap(jobject _jobject);
        Array<Object> wrap(jobjectArray _jarray);
        Array<jboolean> wrap(jbooleanArray _jarray);
        Array<jbyte> wrap(jbyteArray _jarray);
        Array<jchar> wrap(jcharArray _jarray);
        Array<jshort> wrap(jshortArray _jarray);
        Array<jint> wrap(jintArray _jarray);
        Array<jlong> wrap(jlongArray _jarray);
        Array<jfloat> wrap(jfloatArray _jarray);
        Array<jdouble> wrap(jdoubleArray _jarray);

        Array<Object> create_array(size_t size, Class &element_class);
        template<class Type>
        Array<Type> create_array(size_t size, Type *type = nullptr);

        // Casted wraps
        Object wrap(const char *name, jobject);
        Object wrap(Class &_class, jobject);

        template<class Ret>
        Array<Ret> wrap(Class &_class, jarray _array) {
            return Array<Ret>(_class, _array);
        }

        Class get_superclass(Class &_class);

        jmethodID find_method_id(Class &_class, const char *name, const char *signature);

        Object call_constructor(Class &_class, const char *signature, va_list vl);

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
