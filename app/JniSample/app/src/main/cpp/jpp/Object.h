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

        std::string to_string();

        template<class ... Types>
        Object call_object(const char *method_name, Class &return_type, Types ... args) {
            auto signature = utils::generate_signature(return_type, args...);
            return run_object(return_type, method_name, signature.c_str(), utils::flatten(args)...);
        }

        template<class ... Types>
        void call_void(const char *method_name, Types ... args) {
            auto signature = utils::generate_signature((void*)0, args...);
            run_void(method_name, signature.c_str(), utils::flatten(args)...);
        }

        template<class Ret, class ... Types>
        Ret call(const char *method_name, Types ... args) {
            auto signature = utils::generate_signature(Ret(), args...);
            return run(Ret(), method_name, signature.c_str(), utils::flatten(args)...);
        }

    private:
        inline Object run_object(Class &return_type, const char *method_name, const char *signature, ...) {
            va_list vl;
            va_start(vl, signature);
            auto ret = vrun(return_type, method_name, signature, vl);
            va_end(vl);
            return ret;
        }

        inline void run_void(const char *method_name, const char *signature, ...) {
            va_list vl;
            va_start(vl, signature);
            vrun(method_name, signature, vl);
            va_end(vl);
        }

        template<class Ret>
        inline Ret run(Ret type, const char *method_name, const char *signature, ...) {
            va_list vl;
            va_start(vl, signature);
            auto ret = vrun(type, method_name, signature, vl);
            va_end(vl);
            return ret;
        }

        Object vrun(Class &return_type, const char *method_name, const char *signature, va_list vl);
        void vrun(const char *method_name, const char *signature, va_list vl);
        template<class Ret>
        Ret vrun(Ret, const char *method_name, const char *signature, va_list vl);


        Class *const m_class;
        jobject m_jobject = nullptr;
    };
}
