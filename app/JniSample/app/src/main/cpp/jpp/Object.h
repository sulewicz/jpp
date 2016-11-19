#pragma once

#include <jni.h>
#include "internal/utils.h"

namespace jpp {
    class Class;

    class Object {
    public:
        Object(Class *_class, jobject object);
        Object(const Object &other);
        ~Object();

        bool is_valid() const;

        Class *get_class() const;
        JNIEnv *get_env() const;
        jclass get_jclass() const;
        jobject get_jobject() const;

        template<class ... Types>
        Object object(const char *method_name, Class &return_type, Types ... args) {
            auto signature = utils::generate_signature(return_type, args...);
            return do_object(method_name, return_type, signature.c_str(), utils::flatten(args)...);
        }

        template<class ... Types>
        jboolean boolean(const char *method_name, Types ... args) {
            auto signature = utils::generate_signature(jboolean(), args...);
            return do_boolean(method_name, signature.c_str(), utils::flatten(args)...);
        }

    private:
        Object do_object(const char *method_name, Class &return_type, const char *signature, ...);
        jboolean do_boolean(const char *method_name, const char *signature, ...);

        Class *const m_class;
        jobject m_jobject = nullptr;
    };
}
