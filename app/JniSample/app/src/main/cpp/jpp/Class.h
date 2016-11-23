#pragma once

#include <jni.h>
#include <string>
#include "internal/utils.h"
#include "Object.h"

namespace jpp {
    class Class {
    public:
        Class(JNIEnv *env, const char *class_name);
        Class(JNIEnv *env, jclass _class);
        Class(const Class &other);
        ~Class();

        bool is_valid() const;
        const std::string &get_class_name() const;
        JNIEnv *get_env() const;
        jclass get_jclass() const;

        static Class resolve_class(JNIEnv *env, jobject object);
        static std::string resolve_class_name(JNIEnv *env, Object &class_object);

        template<class ... Types>
        Object create(Types ... args) {
            auto signature = utils::generate_signature((void *) 0, args...);
            return do_create(signature.c_str(), utils::flatten(args)...);
        }

        template<class ... Types>
        Object call_object(const char *method_name, Class &return_type, Types ... args) {
            auto signature = utils::generate_signature(return_type, args...);
            return run_object(return_type, method_name, signature.c_str(), utils::flatten(args)...);
        }

        template<class ... Types>
        void call_void(const char *method_name, Types ... args) {
            auto signature = utils::generate_signature((void *) 0, args...);
            run_void(method_name, signature.c_str(), utils::flatten(args)...);
        }

        template<class Ret, class ... Types>
        Ret call(const char *method_name, Types ... args) {
            auto signature = utils::generate_signature(Ret(), args...);
            return run(Ret(), method_name, signature.c_str(), utils::flatten(args)...);
        }

    private:
        Class(JNIEnv *env, jclass _class, const char *class_name);

        inline Object do_create(const char *signature,
                                 ...) {
            va_list vl;
            va_start(vl, signature);
            auto ret = do_create_v(signature, vl);
            va_end(vl);
            return ret;
        }

        inline Object run_object(Class &return_type, const char *method_name, const char *signature,
                                 ...) {
            va_list vl;
            va_start(vl, signature);
            auto ret = run_v(return_type, method_name, signature, vl);
            va_end(vl);
            return ret;
        }

        inline void run_void(const char *method_name, const char *signature, ...) {
            va_list vl;
            va_start(vl, signature);
            run_v(method_name, signature, vl);
            va_end(vl);
        }

        template<class Ret>
        inline Ret run(Ret type, const char *method_name, const char *signature, ...) {
            va_list vl;
            va_start(vl, signature);
            auto ret = run_v(type, method_name, signature, vl);
            va_end(vl);
            return ret;
        }

        Object do_create_v(const char *signature, va_list vl);
        Object run_v(Class &return_type, const char *method_name, const char *signature, va_list vl);
        void run_v(const char *method_name, const char *signature, va_list vl);
        template<class Ret>
        Ret run_v(Ret, const char *method_name, const char *signature, va_list vl);

        JNIEnv *const m_env;
        jclass m_jclass = nullptr;
        std::string m_class_name;
    };
}
