#pragma once

#include <jni.h>
#include <string>
#include "internal/utils.h"
#include "Object.h"

namespace jpp {
    class Class {
    public:
        Class(JNIEnv *env, const char *class_name);
        Class(const Class &other);
        ~Class();

        bool is_valid() const;
        const std::string& get_class_name() const;
        JNIEnv *get_env() const;
        jclass get_jclass() const;

        template<class ... Types>
        Object construct(Types ... args) {
            auto signature = utils::generate_signature((void*)0, args...);
            return do_construct(signature.c_str(), args...);
        }

        static Class resolve_class(JNIEnv *env, jobject object);

    private:
        Class(JNIEnv *env, jclass _class, const char *class_name);
        Object do_construct(const char *signature, ...);

        JNIEnv *const m_env;
        jclass m_jclass = nullptr;
        std::string m_class_name;
    };
}
